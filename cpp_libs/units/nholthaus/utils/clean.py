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


def removePyCache():
    removeDir("__pycache__")


################################################################################


if __name__ == "__main__":
    print("Cleaning...")
    removePyCache()
    os.chdir("..")
    removeBuildDirs()
    print("Cleaning done.")
