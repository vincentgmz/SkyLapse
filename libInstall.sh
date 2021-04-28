#!/bin/bash

WORKING=`pwd`

mkdir -p lib
mkdir -p bin
unzip ncurses
cd ncurses
./configure --prefix $WORKING/lib --enable-widec --with-pthread
make -j
make -j install
