#!/bin/bash

#docker rmi $(docker images -q)
docker rmi -f $(docker images -q)
