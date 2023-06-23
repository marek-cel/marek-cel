#!/bin/bash

sudo systemd-resolve --flush-caches
sudo resolvectl flush-caches
sudo systemd-resolve --statistics
