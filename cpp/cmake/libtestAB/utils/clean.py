#!/usr/bin/env python3

import misc


def removeBuildDirs():
    misc.removeDir("../bin")
    misc.removeDir("../build")
    misc.removeDir("../lib")


def removePyCache():
    misc.removeDir("__pycache__")


def cleanAll():
    removePyCache()
    removeBuildDirs()


if __name__ == "__main__":
    misc.printGreen("Cleaning...")
    cleanAll()
    misc.printGreen("Cleaning done.")
