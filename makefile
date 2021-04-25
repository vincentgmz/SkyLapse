all: bin/main

bin/main : bin/game.o bin/enemy.o
	g++ -o bin/main bin/game.o bin/enemy.o -lncurses -std=c++11 -pedantic-errors

bin/game.o: src/game.cpp src/game.h src/enemy.h
	g++ -c -o bin/game.o src/game.cpp

bin/enemy.o: src/enemy.cpp src/enemy.h
	g++ -c -o bin/enemy.o src/enemy.cpp

clean :
	rm -rf bin/*.o
