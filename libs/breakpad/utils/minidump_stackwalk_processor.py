"""
minidump_stackwalk_processor provides functions to parse
the output of Breakpad's minidump_stackwalk tool which produces
stack traces from minidumps.

To extract a stacktrace from a minidump, run minidump_stackwalk with the
'-m' argument and capture its stdout.

Parse the result to Stacktrace.parse() to create a Stacktrace object.
"""

from __future__ import print_function

import re

class Frame:
    """ Represents a single frame from a stack trace """
    def __init__(self, module, function, line, column, addr):
        self.module = module
        self.function = function
        self.line = line
        self.column = column
        self.addr = addr

class Module:
    """ Represents an executable or shared library loaded into the app that crashed """
    def __init__(self, filename, version, debug_filename, debug_id, base_addr, max_addr):
        self.filename = filename
        self.version = version
        self.debug_filename = debug_filename
        self.debug_id = debug_id
        self.base_addr = base_addr
        self.max_addr = max_addr

class CpuInfo:
    """ Stores the CPU type, model and core count of the system where a crash occurred """
    def __init__(self, type, model, core_count):
        self.type = type
        self.model = model
        self.core_count = core_count

class CrashInfo:
    """ Basic metadata about the type and location of a crash """
    def __init__(self, crash_type, crash_addr, crash_thread):
        self.type = crash_type
        self.addr = crash_addr
        self.thread_id = crash_thread

class OSVersion:
    """ OS platform and version of the system where a crash occurred """
    def __init__(self, platform, build_id):
        self.platform = platform
        self.build_id = build_id

class Stacktrace:
    """ Stacktrace containing data extracted from a minidump.

    This includes the list of modules that were loaded, the
    stack frames in each thread at the time of the crash, basic
    metadata about the crash (thread ID, exception type) and also
    details of the system where the crash occurred, including the OS version
    and CPU details.
    """
    def __init__(self, main_module, modules, threads, crash_info, cpu_info, os_version):
        self.main_module = main_module
        self.modules = modules
        self.threads = threads
        self.crash_info = crash_info
        self.cpu_info = cpu_info
        self.os_version = os_version

    @staticmethod
    def parse(stackwalk_output):
        os_version = None
        cpu_info = None
        crash_info = None
        main_module = None
        threads = {}
        modules = {}

        for line in stackwalk_output.splitlines():
            fields = line.split('|')
            entry_type = fields[0]

            if re.match('[0-9]+', entry_type):
                thread_id = int(entry_type)
                if not (thread_id in threads):
                    threads[thread_id] = []

                frame_index, module, function, line, column, addr = fields[1:]
                threads[thread_id] += [Frame(module, function, line, column, addr)]

            elif entry_type == 'OS':
                platform, platform_build = fields[1:]
                os_version = OSVersion(platform, platform_build)
            elif entry_type == 'CPU':
                cpu_type, cpu_model, cores = fields[1:]
                cpu_info = CpuInfo(cpu_type, cpu_model, int(cores))
            elif entry_type == 'Crash':
                crash_type, crash_addr, crash_thread = fields[1:]
                if crash_type != 'No crash':
                    crash_info = CrashInfo(crash_type, crash_addr, int(crash_thread))
            elif entry_type == 'Module':
                filename, version, debug_filename, debug_id, base_addr, max_addr, is_main = fields[1:]
                is_main = bool(int(is_main))

                modules[filename] = Module(filename, version, debug_filename, debug_id, base_addr, max_addr)
                if is_main:
                    main_module = filename

        stacktrace = Stacktrace(main_module, modules, threads, crash_info, cpu_info, os_version)
        return stacktrace

