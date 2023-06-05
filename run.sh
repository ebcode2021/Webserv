#!/bin/bash
rm -rf /Users/minsukan/Library/Caches
rm -rf /Users/eunson/Library/Caches
make -j15 re
./webserv test.conf