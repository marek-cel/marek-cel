#!/usr/bin/env python3

################################################################################

import subprocess

################################################################################

if __name__ == "__main__":
    dockerfile = 'Dockerfile'
    docker_cmd = [
        'docker', 'build',
        '-f',  dockerfile,
        '-t', 'cpp-docker-build-env:1',
        '.'
    ]
    print(" ".join(docker_cmd))
    subprocess.call(docker_cmd)
