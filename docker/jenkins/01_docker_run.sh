#!/bin/bash

################################################################################

docker run --restart always --name myjenkins -p 9000:8080 -p 50000:50000 -v /var/jenkins_home jenkins/jenkins:lts

################################################################################

read -p "Press any key to continue... " -n1 -s
