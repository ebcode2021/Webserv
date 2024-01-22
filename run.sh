#!/bin/bash
make -j5 re
./webserv test2.conf
make fclean