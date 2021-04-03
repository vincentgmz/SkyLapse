all: game

game: src/game.cpp
	g++ -pedantic-errors -std=c++11 -lncurses -o bin/game src/game.cpp
