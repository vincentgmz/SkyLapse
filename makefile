all: bin/main

bin/main : bin/game.o bin/enemy.o bin/boss.o 
	g++ -I ./lib/include -I ./lib/include/ncursestw -L ./lib/lib \
	-o bin/main bin/game.o bin/enemy.o bin/boss.o -lncursestw -ldl -pthread\
		-std=c++11 -pedantic-errors

bin/game.o: src/game.cpp src/game.h src/enemy.h
	g++ -I ./lib/include -I ./lib/include/ncursestw -L ./lib/lib -c -o bin/game.o src/game.cpp -lncursestw -ldl -pthread

bin/enemy.o: src/enemy.cpp src/enemy.h
	g++ -I ./lib/include -I ./lib/include/ncursestw -L ./lib/lib -c -o bin/enemy.o src/enemy.cpp -lncursestw -ldl -pthread

bin/boss.o : src/boss.cpp
	g++ -I ./lib/include -I ./lib/include/ncursestw -L ./lib/lib  -c -o bin/boss.o src/boss.cpp -lncursestw -ldl -pthread

clean :
	rm -rf bin/*.o
