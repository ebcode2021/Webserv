#!/bin/bash

make -j15 re
mkdir /Users/eunson/Desktop/webserv/resources/html/test
./webserv test.conf