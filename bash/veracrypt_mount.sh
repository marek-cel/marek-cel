#!/bin/bash

VOLUME=volume
PASSWORD=password

sudo veracrypt --mount --password=$PASSWORD $VOLUME
