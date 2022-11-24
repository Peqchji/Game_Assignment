#include "GAMELOGIC.h"
void GAMELOGIC::RandomRoomType(short AMOUNT_Room)
{
    int i;
    int room_id;
    int chestroomCreated = 0;
    short Amount_ChestRoom = (AMOUNT_Room + 1) / 3;

    roomType.clear();
    roomType.push_back(std::string("SpawnRoom"));
    for(i = 1; i < AMOUNT_Room; i++)
    {
        roomType.push_back(std::string(""));
    }
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

void GAMELOGIC::SpawnEnemies(int AMOUNT_Room, std::vector<ENEMY*> &Enemies,  float &HardMultiplier, float SpawnGrid_x, float SpawnGrid_y)
{
    int i;
    float init_Posi_x;
    float init_Posi_y;
    int amountEnemy = AMOUNT_Room * 1.5 + rand()%3;
    for(i = 0; i < amountEnemy; i++)
    {
        init_Posi_x = (SpawnGrid_x * ::GridPixelSize) + (::CellPixelSize * (10 + rand()%14));
        init_Posi_y = (SpawnGrid_y * ::GridPixelSize) + (::CellPixelSize * (10 + rand()%14));
        Enemies.push_back(new ENEMY(HardMultiplier, init_Posi_x, init_Posi_y) );
    }
}

void GAMELOGIC::SpawnChest(std::vector<CHEST*> &Chest, short SpawnGrid_x, short SpawnGrid_y)
{
    float init_Posi_x;
    float init_Posi_y;
    init_Posi_x = static_cast<float>(SpawnGrid_x * ::GridPixelSize) + (::CellPixelSize * 16.5);
    init_Posi_y = static_cast<float>(SpawnGrid_y * ::GridPixelSize) + (::CellPixelSize * 16.5);
    Chest.push_back(new CHEST(init_Posi_x, init_Posi_y) );
}
