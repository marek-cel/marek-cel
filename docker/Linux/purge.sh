#!/bin/bash

docker kill $(docker ps -aq)
docker rm $(docker ps -aq)
docker rmi -f $(docker images -q)
docker system prune -a
