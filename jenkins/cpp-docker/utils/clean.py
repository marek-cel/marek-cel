#!/usr/bin/env python3

################################################################################

import os
import shutil

################################################################################


def removeDir(dir_path):
    if os.path.exists(dir_path):
        shutil.rmtree(dir_path)


def removeFile(file_path):
    if os.path.exists(file_path):
        os.remove(file_path)


################################################################################


def removeBuildDirs():
    removeDir("bin")
    removeDir("build")
    removeDir("lib")


def removeCoverageReport():
    removeFile("coverage_full.info")
    removeFile("coverage.info")
    removeDir("coverage-report")
    removeFile("coverage_summary.txt")


def removeCheckOutputs():
    removeFile("out_cloc.txt")
    removeFile("out_cppcheck.txt")
    removeFile("out_cpplint.txt")


def removeDocumentation():
    removeDir("docs")


def removePyCache():
    removeDir("__pycache__")


################################################################################


if __name__ == "__main__":
    print("Cleaning...")
    os.chdir("..")
    removeBuildDirs()
    removeCoverageReport()
    removePyCache()
    print("Cleaning done.")
