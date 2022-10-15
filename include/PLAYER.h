#include "MASTER.h"
class PLAYER{
    public:
        sf::Texture PlayerTexture;
        sf::Vector2f velocity;

        sf::RectangleShape Hitbox;
        sf::RectangleShape CharModel;
        
        sf::Vector2f textureSize;

        void setPlayer_attribute();
        void setPlayerSpawnPos(float SpawnPoint_x,float SpawnPoint_y);
        void setZeroVelocity();
        void movePlayer();
};