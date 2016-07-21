#!/usr/bin/env python

# This is a script to fetch debug symbols for a binary from
# a symbol server with an HTTP endpoint, for use with
# minidump_stackwalk's '-e' option which runs an external
# command to fetch debug symbols needed to generate a stacktrace
# from a minidump.
#
# Given a binary name and build ID, it will fetch symbols
# from $SERVER_URL/$BINARY_NAME/$BUILD_ID/$BINARY_BASENAME.sym
# and cache them locally in a temporary directory to speed
# up future requests.

from __future__ import print_function
from distutils.dir_util import mkpath

import argparse
import json
import urllib2
import os
import tempfile
import time
import sys

# path to local symbol cache for faster retrieval in future
CACHE_ROOT = '%s/%s' % (tempfile.gettempdir(), 'symbol-cache')

# TODO - For Windows binaries, attempt to fetch from the Microsoft symbol server
# if symbols are not found in our own symbol server.
#
# The Microsoft symbol server only has .pdb files which need to be processed to
# generate .sym files that can be used by minidump_stackwalk
#
# Note for when we come to implement this, HTTP requests to the MSFT symbol
# server must have the user agent 'Microsoft-Symbol-Server' followed
# by a version number which, at the time of testing, has to be >= 6.3.
# Otherwise the server responds with a redirect to a non-existent URL.
#
# root URL for Microsoft's symbol server.
# See http://support.microsoft.com/kb/311503
# MSFT_SYMBOL_SERVER_URL = 'http://msdl.microsoft.com/download/symbols'
# MSFT_SYMBOL_STORE_USER_AGENT = "Microsoft-Symbol-Server/10.0.0.0"

# Length of time to remember failed cache lookups for in seconds
MAX_MISSING_CACHE_AGE = 300

def cache_entry_path(symfile_path):
    cache_path = '%s/%s' % (CACHE_ROOT, symfile_path)
    return cache_path

def lookup_in_cache(symfile_path):
    """ Looks up debug symbols in the local cache.
    Returns:
     - The string contents of the cached symbols if they exist
     - A number indicating the time in seconds since a lookup last failed
       if a previous failed lookup has been cached
     - None if no cached successful or failed lookup exists
    """
    cache_path = cache_entry_path(symfile_path)
    if os.path.exists(cache_path):
        cache_file = open(cache_path, 'r')
        data = cache_file.read()
        module_line = data.split('\n', 1)[0]

        if 'MODULE' in module_line:
            return data
        else:
            cache_age = time.time() - os.path.getmtime(cache_path)
            return cache_age
    else:
        return None

def update_cache(symfile_path, symbols):
    """ Save breakpad debug symbols to the local cache.
    If symbols is None, a dummy entry is created in the cache
    to record the last time when a lookup failed.
    """
    cache_path = cache_entry_path(symfile_path)
    mkpath(os.path.dirname(cache_path))
    if symbols:
        # save to local cache for future use
        cache_file = open(cache_path, 'w')
        cache_file.write(symbols)
        cache_file.close()
    else:
        # write a dummy file to indicate a failed cache lookup
        symbols_missing_file = open(cache_path, 'w')
        symbols_missing_file.write('No symbols found')
        symbols_missing_file.close()

def lookup_symbols(debug_file_name, symfile_path, symbol_servers):
    symbols_found = False
    for server in symbol_servers:
        symbol_url = '%s/%s' % (server, urllib2.quote(symfile_path))
        print('Symbols for %s not found in cache, fetching from %s' % (debug_file_name, symbol_url), file=sys.stderr)
        
        try:
            url_req = urllib2.Request(symbol_url)
            url_reply = urllib2.urlopen(url_req)
            data = url_reply.read()
            update_cache(symfile_path, data)
            symbols_found = True
            return data
        except urllib2.HTTPError as err:
            if err.code == 404:
                print('Not found: %s' % (symbol_url), file=sys.stderr)
            else:
                print('Error fetching %s: %s' % (symbol_url, err))

    if not symbols_found:
        # If none of the symbol servers had debug symbols for this binary,
        # cache the failed lookup to speed up processing of other reports
        # that reference the same report
        update_cache(symfile_path, None)

def main():
    parser = argparse.ArgumentParser(
"""Fetch symbol files for a binary from an HTTP symbol server and cache them locally.
""")
    parser.add_argument('-s', type=str,
      action='append',
      dest='symbol_servers',
      help='Add a symbol server to search for available symbols',
      required=True)
    parser.add_argument('debug_file_name', type=str, help='The file name (excluding the path) of the file (PDB on Windows, shared library or executable on other platforms) which the debug info was extracted from.', action='store')
    parser.add_argument('debug_id', type=str, help='The debug/build identifier for the version of the binary referenced in a minidump', action='store')
    parser.add_argument('-a', type=str, action='store', help='Path to a config file specifying alternative names',
      dest='alternate_name_map')
    opts = parser.parse_args()

    debug_file_names = []
    debug_file_names += [opts.debug_file_name]

    debug_id = opts.debug_id

    # If the user specified a config file with alternative names to try,
    # lookup the alternate debug file names for this binary
    if opts.alternate_name_map:
        alt_name_file = open(opts.alternate_name_map, 'r')
        alt_names = json.load(alt_name_file)
        if opts.debug_file_name in alt_names:
            debug_file_names += alt_names[opts.debug_file_name]

    # For each of the debug file names, fetch debug symbols from
    # the cache or try the symbol servers specified on the command line
    for debug_file_name in debug_file_names:
        if debug_file_name.endswith('.pdb'):
            symfile_name = debug_file_name[0:-4] + '.sym'
        else:
            symfile_name = debug_file_name + '.sym'

        symfile_path = '%s/%s/%s' % (debug_file_name, debug_id, symfile_name)

        # First try the cache
        cached_symbols = lookup_in_cache(symfile_path)

        if isinstance(cached_symbols, str):
            print(cached_symbols)
            sys.exit(0)
        elif isinstance(cached_symbols, int):
            if cache_age < MAX_MISSING_CACHE_AGE:
               print('Symbols for %s not found in cache but failed lookup cached %d seconds ago' % (debug_file_name, cache_age),
                     file=sys.stderr)
               continue
            
        # If that fails, query each symbol server in turn
        symbols = lookup_symbols(debug_file_name, symfile_path, opts.symbol_servers)
        if symbols:
            print(symbols, file=sys.stdout)
            sys.exit(0)

    # No debug symbols found for this (debug file name, build ID) combination
    # on any of the symbol servers
    sys.exit(1)

if __name__ == '__main__':
    main()

