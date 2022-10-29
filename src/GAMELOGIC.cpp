#include "GAMELOGIC.h"
void GAMELOGIC::RandomRoomType(int AMOUNT_Room)
{
    int i;
    int room_id;
    int Amount_ChestRoom = (AMOUNT_Room + 1) / 3;
    int chestroomCreated = 0;

    roomType.clear();
    roomType.push_back(std::string("SpawnRoom"));
    for(i = 1; i < AMOUNT_Room; i++)
    {
        roomType.push_back(std::string(""));
    }
    printf("%d %d\n", Amount_ChestRoom, roomType.size());
    while(chestroomCreated != Amount_ChestRoom)
    {
        room_id = (rand()%(AMOUNT_Room - 1)) + 1;
        if(roomType[room_id].compare("") == 0 && roomType[room_id].compare("ChestRoom") != 0)
        {
            std::replace(roomType.begin() + room_id, roomType.end(), roomType[room_id], std::string("ChestRoom"));
            chestroomCreated += 1;
        }
    }

    for(i = 1; i < AMOUNT_Room; i++)
    {
        if(roomType[i].compare("") == 0)
        {
            replace(roomType.begin(), roomType.end(), roomType[i], std::string("EnemyRoom"));
        }
    }

    roomType.push_back(std::string("PortalRoom"));
}

void GAMELOGIC::SpawnEnemies(int AMOUNT_Room, std::vector<ENEMY*> &Enemies, float SpawnPosi_x, float SpawnPosi_y)
{
    Enemies.push_back(new ENEMY("MiniDemon", SpawnPosi_x, SpawnPosi_y) );
}