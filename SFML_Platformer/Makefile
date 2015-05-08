all: main.o BaseObject.o Player.o Tile.o Level.o Enemy.o
	g++ -std=c++11 -g -o game main.o BaseObject.o Player.o Tile.o Level.o Enemy.o -lsfml-graphics -lsfml-window -lsfml-system
main.o: main.cpp
	g++ -std=c++11 -g -c main.cpp 
BaseObject.o: BaseObject.cpp
	g++ -std=c++11 -g -c BaseObject.cpp
Player.o: Player.cpp
	g++ -std=c++11 -g -c Player.cpp
Tile.o: Tile.cpp
	g++ -std=c++11 -g -c Tile.cpp
Level.o: Level.cpp
	g++ -std=c++11 -g -c Level.cpp
Enemy.o: Enemy.cpp
	g++ -std=c++11 -g -c Enemy.cpp
