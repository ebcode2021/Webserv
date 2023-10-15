#!/bin/bash
rm -rf /Users/eunson/Library/Caches
rm -rf /Users/eunson/Desktop/webserv/.caches
make -j5 re
./webserv test2.conf