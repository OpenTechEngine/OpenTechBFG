#!/usr/bin/env python

"""Utility for producing a stack trace from a minidump.

This runs the minidump_stackwalk tool to extract a stacktrace
from a minidump and symbolize it.

The output of minidump_stackwalk is then parsed and the details
of the system where the crash occurred and stack trace of the
crashing thread are output.
"""

from __future__ import print_function

import argparse
import os
import subprocess
import sys

import minidump_stackwalk_processor

def print_pretty_trace(trace, thread_id):
    print('\nStacktrace for thread %s:' % (thread_id))
    for frame in trace.threads[thread_id]:
        if frame.function:
            print('  %s' % frame.function)
        else:
            print('  [Unknown in %s]' % frame.module)

def run_stackwalk(minidump_tool, dump_file, symbol_fetch_command, verbose = False, raw = False, all_threads = False):
    stderr_output = subprocess.PIPE
    if verbose:
        stderr_output = sys.stderr

    proc = subprocess.Popen([minidump_tool, '-m', dump_file, '-e', symbol_fetch_command],
      stdout=subprocess.PIPE, stderr=stderr_output)
    stdout, stderr = proc.communicate()

    if raw:
        for line in stdout.splitlines():
            print(line)
        return

    trace = minidump_stackwalk_processor.Stacktrace.parse(stdout)
    main_module = trace.modules[trace.main_module]
    version = main_module.version or 'Unknown version'

    print('App: %s (%s)' % (main_module.filename, version))

    if trace.crash_info:
        print('Crash: %s in thread %s' % (trace.crash_info.type, trace.crash_info.thread_id))

    print('OS: %s %s' % (trace.os_version.platform, trace.os_version.build_id))

    if trace.crash_info and (not all_threads):
        print_pretty_trace(trace, trace.crash_info.thread_id)
    else:
        for key in trace.threads.keys():
            print_pretty_trace(trace, key)

def main():
    parser = argparse.ArgumentParser(description="Produce a stack trace from a minidump")
    parser.add_argument('dump_file', action='store', type=str, help='Path to minidump file')
    parser.add_argument('-v', action='store_true', dest='verbose', help='Display verbose output from minidump_stackwalk')
    parser.add_argument('--raw', action='store_true', dest='raw', help='Display raw output from minidump_stackwalk')
    parser.add_argument('-a', action='store_true', dest='all_threads', help='Display stacktrace for all threads')
    args = parser.parse_args()
    
    minidump_tool = os.environ.get('MINIDUMP_STACKWALK_PATH')
    if not minidump_tool:
        print("""MINIDUMP_STACKWALK_PATH not set. This should be set to the path of the
              minidump_stackwalk tool.""")
        sys.exit(1)

    sym_url = os.environ.get('MINIDUMP_STACKWALK_SYMBOL_URL')
    if not sym_url:
        print("""MINIDUMP_STACKWALK_SYMBOL_URL not set. This should be set to the URL
              where debug symbols are hosted.""")
        sys.exit(1)

    alt_names_config_file = '%s/alternate-debug-file-names.json' % (os.path.dirname(os.path.abspath(__file__)))

    sym_fetch_tool = os.path.abspath(os.path.dirname(__file__) + '/fetch-symbols.py')
    sym_fetch_command = '%s -a %s -s \"%s\"' % (sym_fetch_tool, alt_names_config_file, sym_url)

    run_stackwalk(minidump_tool, args.dump_file, sym_fetch_command,
      verbose=args.verbose,
      raw=args.raw,
      all_threads=args.all_threads)

if __name__ == '__main__':
    main()
