#!/bin/bash

tar xzf ncurses-6.1.tar.gz
cd ncurses-6.1
./configure --prefix ~/local &> trash.txt
make &> trash.txt
make install &> trash.txt
rm trash.txt
