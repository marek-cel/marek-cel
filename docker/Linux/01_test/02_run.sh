#!/bin/bash

################################################################################

# docker run -p 8080:80 --name test_01 -it test_01:v1 bash
docker run -p 8080:80 --name test_01 test_01:v1

################################################################################

read -p "Press any key to continue... " -n1 -s