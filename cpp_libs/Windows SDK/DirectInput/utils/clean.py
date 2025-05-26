#!/usr/bin/env python3

import misc


def removeBuildDirs():
    misc.removeDir("../bin")
    misc.removeDir("../build")
    misc.removeDir("../lib")


def removeCoverageReport():
    misc.removeFile("../coverage_full.info")
    misc.removeFile("../coverage.info")
    misc.removeFile("../coverage_summary.txt")
    misc.removeDir("../coverage-report")


def removeCheckOutputs():
    misc.removeFile("../out_cloc.txt")
    misc.removeFile("../out_cppcheck.txt")
    misc.removeFile("../out_cpplint.txt")
    misc.removeFile("../out_pep.txt")


def removeDocumentation():
    misc.removeDir("../docs/doxygen")


def removePyCache():
    misc.removeDir("__pycache__")


def removeTempDir():
    misc.removeDir("../temp")


def cleanAll():
    removePyCache()
    removeBuildDirs()
    removeCoverageReport()
    removeCheckOutputs()
    removeDocumentation()
    removeTempDir()


if __name__ == "__main__":
    misc.printGreen("Cleaning...")
    cleanAll()
    misc.printGreen("Cleaning done.")
