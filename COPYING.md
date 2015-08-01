Licenses of the files in this repository:

neo/ and base/renderprogs/
================================

The C++ Code in neo/ and the shaders in base/renderprogs/ are released under
GPLv3 with additional terms, see COPYING-GPL3-id.txt  
There are some exceptions for a few files based on code under different
licenses, see "CODE LICENSE EXCEPTIONS" at the end of this file.

base/
================================

Except for base/renderprogs/ (GPLv3, see above) and base/cegui/ (MIT-licensed),
everything in base/ is licensed very liberally, under WTFPLv2 and similar
Public Domain-like licenses.  
This allows you to use those assets in your own projects however you see fit.
If you use them, credit would be appreciated, but is not necessary.  
Much of this is taken from the d3-base-assets project,
see https://github.com/DanielGibson/d3-base-assets

See COPYING-base.txt for details of the authors and specific licenses.

libs/
================================

We bundle some third-party libraries in libs/.
Please see sub-directories under libs/ for bundled library license information.


Code in neo/ that's not licensed under modified GPLv3
======================================================

CODE LICENSE EXCEPTIONS - The parts that are not covered by the GPL:

EXCLUDED CODE:  The code described below and contained in the Doom 3 BFG Edition GPL Source Code release
is not part of the Program covered by the GPL and is expressly excluded from its terms. 
You are solely responsible for obtaining from the copyright holder a license for such code and complying with the applicable license terms.

Base64 implementation
---------------------------------------------------------------------------
neo/idlib/Base64.cpp

Copyright (c) 1996 Lars Wirzenius.  All rights reserved.

June 14 2003: TTimo <ttimo@idsoftware.com>
	modified + endian bug fixes
	http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=197039

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

MD4 Message-Digest Algorithm
-----------------------------------------------------------------------------
neo/idlib/hashing/MD4.cpp
Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
rights reserved.

License to copy and use this software is granted provided that it
is identified as the "RSA Data Security, Inc. MD4 Message-Digest
Algorithm" in all material mentioning or referencing this software
or this function.

License is also granted to make and use derivative works provided
that such works are identified as "derived from the RSA Data
Security, Inc. MD4 Message-Digest Algorithm" in all material
mentioning or referencing the derived work.

RSA Data Security, Inc. makes no representations concerning either
the merchantability of this software or the suitability of this
software for any particular purpose. It is provided "as is"
without express or implied warranty of any kind.

These notices must be retained in any copies of any part of this
documentation and/or software.

MD5 Message-Digest Algorithm
-----------------------------------------------------------------------------
neo/idlib/hashing/MD5.cpp
This code implements the MD5 message-digest algorithm.
The algorithm is due to Ron Rivest.  This code was
written by Colin Plumb in 1993, no copyright is claimed.
This code is in the public domain; do with it what you wish.

CRC32 Checksum
-----------------------------------------------------------------------------
neo/idlib/hashing/CRC32.cpp
Copyright (C) 1995-1998 Mark Adler

