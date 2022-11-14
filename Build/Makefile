all: compile link

compile:
	g++ -I ../include/ -c ../src/main.cpp ../src/PLAYER.cpp ../src/WORLD.cpp ../src/BULLET.cpp ../src/WEAPON.cpp ../src/GAMELOGIC.cpp ../src/Enemies.cpp ../src/GUI.cpp ../src/Portal.cpp ../src/Chest.cpp ../src/Item.cpp
link:
	g++ main.o PLAYER.o WORLD.o BULLET.o WEAPON.o GAMELOGIC.o Enemies.o GUI.o Portal.o Chest.o Item.o -o "Let's Me Out The Dungeon.exe" -L ../lib/ -lsfml-graphics -lsfml-window -lsfml-system