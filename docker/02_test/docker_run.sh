#!/bin/bash

################################################################################

# docker run -p 8080:80 -v $(pwd)/src:/var/www/html/ --name test_02 -it test_02:v1 bash
docker run -p 8080:80 -v $(pwd)/src:/var/www/html/ --name test_02 test_02:v1

################################################################################

read -p "Press any key to continue... " -n1 -s
