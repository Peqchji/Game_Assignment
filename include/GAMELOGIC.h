#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <MASTER.h>
#include <ENEMY.h>
#include <Portal.h>
#include <CHEST.h>
class GAMELOGIC
{
    public:
        std::vector<std::string> roomType;
        void RandomRoomType(int AMOUNT_Room);
        void SpawnEnemies(int AMOUNT_Room, std::vector<ENEMY*> &Enemies,  float &HardMultiplier, float SpawnPosi_x, float SpawnPosi_y);
        void SpawnChest(std::vector<CHEST*> &Chest, short SpawnGrid_x, short SpawnGrid_y);
        

};

#endif