all: compile link

compile:
	g++ -I ../include/ -c ../src/main.cpp ../src/PLAYER.cpp ../src/WORLD.cpp
link:
	g++ main.o PLAYER.o WORLD.o -o "Let's Me Out The Dungeon.exe" -L ../lib/ -lsfml-graphics -lsfml-window -lsfml-system