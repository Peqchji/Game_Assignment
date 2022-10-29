#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <MASTER.h>
#include <ENEMY.h>

class GAMELOGIC
{
    public:
        std::vector<std::string> roomType;
        void RandomRoomType(int AMOUNT_Room);
        void SpawnEnemies(int AMOUNT_Room, std::vector<ENEMY*> &Enemies,  float SpawnPosi_x, float SpawnPosi_y);
};

#endif