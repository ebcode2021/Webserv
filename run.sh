#!/bin/bash
rm -rf /Users/minsukan/Library/Caches
rm -rf /Users/eunson/Library/Caches
make -j15 re
mkdir /Users/eunson/Desktop/webserv/resources/html/test
./webserv test.conf