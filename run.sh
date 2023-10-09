#!/bin/bash
# rm -rf /Users/minsukan/Library/Caches
#rm -rf /Users/eunson/Library/Caches
rm -rf /Users/eunbison/Desktop/42seoul/webserv/.caches
make -j5 re
./webserv test.conf