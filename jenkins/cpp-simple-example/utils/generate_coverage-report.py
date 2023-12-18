#!/usr/bin/env python3

################################################################################

import os
import subprocess
import clean

################################################################################

build_dir = "./build"
base_dir  = "./src"

coverage_file = ""

################################################################################


def executeAllSteps():
    print("Generating coverage report...")
    captureCoverage()
    generateCoverageSummary()
    generateCoverageReport()
    print("Generating coverage report done.")


def captureCoverage():
    cmd = [
        "lcov", "--capture",
        "--base-directory", base_dir,
        "--no-external",
        "--directory", build_dir,
        "--output-file", "coverage.info"
    ]
    subprocess.run(cmd)


def generateCoverageSummary():
    subprocess.run("lcov --summary coverage.info > coverage_summary.txt", shell=True)


def generateCoverageReport():
    cmd = ["genhtml", "coverage.info",
        "--legend",
        "--function-coverage",
        "--output-directory", "coverage-report"
    ]
    subprocess.run(cmd)


################################################################################


if __name__ == "__main__":
    clean.removeCoverageReport()
    os.chdir("..")
    executeAllSteps()
