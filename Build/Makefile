all: compile link

compile:
	g++  -I ../include/ -c ../src/*.cpp
link:
	g++ *.o -o "Let's Me Out The Dungeon.exe" -L ../lib/ -lsfml-graphics -lsfml-window -lsfml-system
