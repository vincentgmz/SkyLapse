#!/bin/bash

WORKING=`pwd`

mkdir -p lib
mkdir -p bin
unzip ncurses
cd ncurses
./configure --prefix $WORKING/lib --enable-widec --with-pthread &> trash.txt
make -j &> trash.txt
make -j install &> trash.txt
rm trash.txt
