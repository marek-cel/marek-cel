#!/usr/bin/env python3

import os
import platform
import subprocess
import sys
import clean

build_dir = "build"

if __name__ == "__main__":
    clean.removeBuildDirs()
    os.chdir("..")
    cmake_cmd = [
        'cmake', '.',
        '-DCMAKE_BUILD_TYPE=Release',
        '-DCMAKE_INSTALL_PREFIX=/usr/local',
        '-DBUILD_TESTING=ON',
        '-DTESTS_COVERAGE=ON',
        '-B', build_dir
    ]
    result = subprocess.run(cmake_cmd)
    if result.returncode == 0:
        subprocess.run(
            "cmake --build " + build_dir + " --config Release -j 4 --target all tests-mcsim-app tests-mcsim-sdk --",
            shell=True
        )
