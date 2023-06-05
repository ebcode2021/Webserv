#!/bin/bash
rm -rf /Users/minsukan/Library/Caches
make -j15 re
./webserv test.conf