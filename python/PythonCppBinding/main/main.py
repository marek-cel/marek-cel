#!/usr/bin/env python3

import ctypes
import sys

def runCppLib():
    # Load the shared library
    if sys.platform.startswith("linux"):
        lib = ctypes.CDLL("./lib/libfoobar.so")
    elif sys.platform == "win32":
        lib = ctypes.CDLL("./bin/foobar.dll")
    else:
        raise OSError("Unsupported OS")

    # Define argument and return types for the C functions
    lib.FooBar_new.restype = ctypes.c_void_p
    lib.FooBar_greet.argtypes = [ctypes.c_void_p]
    lib.FooBar_delete.argtypes = [ctypes.c_void_p]

    # Create and use FooBar object
    foo = lib.FooBar_new()
    lib.FooBar_greet(foo)
    lib.FooBar_delete(foo)

if __name__ == "__main__":
    print("Hello, World!")
    runCppLib()
    print("Goodbye, World!")
