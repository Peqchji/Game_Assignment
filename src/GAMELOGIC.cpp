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
            std::replace(roomType.begin() + i, roomType.end(), roomType[i], std::string("EnemyRoom"));
        }
    }

    roomType.push_back(std::string("PortalRoom"));
}

void GAMELOGIC::SpawnEnemies(int AMOUNT_Room, std::vector<ENEMY*> &Enemies, float SpawnGrid_x, float SpawnGrid_y)
{
    int i;
    float init_Posi_x;
    float init_Posi_y;
    int amountEnemy = AMOUNT_Room + rand()%3;
    for(i = 0; i < amountEnemy; i++)
    {
        init_Posi_x = (SpawnGrid_x * ::GridPixelSize) + (::CellPixelSize * (10 + rand()%14));
        init_Posi_y = (SpawnGrid_y * ::GridPixelSize) + (::CellPixelSize * (10 + rand()%14));
        Enemies.push_back(new ENEMY("MiniDemon", init_Posi_x, init_Posi_y) );
    }
}

void GAMELOGIC::SpawnPortal(float grid_x, float grid_y)
{
    float init_x = (grid_x + 0.5) * ::GridPixelSize;
    float init_y = (grid_y + 0.5) * ::GridPixelSize;
}