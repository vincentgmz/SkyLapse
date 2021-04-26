#!/bin/bash

mkdir -p bin
mkdir ~/repos
cd ~/repos
git clone https://github.com/mirror/ncurses.git
cd ncurses
./configure --prefix ~/local --enable-widec --with-pthread &> trash.txt
make -j &> trash.txt
make -j install &> trash.txt
rm trash.txt
