all: game

game: game.cpp
	g++ -pedantic-errors -std=c++11 -lncurses game.cpp -o game
