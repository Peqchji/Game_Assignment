#ifndef PLAYER_H
#define PLAYER_H

#include "MASTER.h"
class PLAYER{
    public:
        struct PlayerClassAttibute
        {
            short Health;
            short Ammor;
            short Energy;
            short Crit_Chance;
            std::string Skill;

            PlayerClassAttibute(short _Health, short _Ammor,short _Energy, short _Crit_Chance, std::string _Skill)
            {
                Health = _Health;
                Ammor = _Ammor;
                Energy = _Energy;
                Crit_Chance = _Crit_Chance;
                Skill = _Skill;
            }
        };

        sf::Texture PlayerTexture;
        sf::Vector2f velocity;

        sf::RectangleShape collisionHitbox;
        sf::RectangleShape CharModel;
        
        sf::Vector2f textureSize;

        void setPlayer_attribute();
        void setPlayerSpawnPos(float SpawnPoint_x,float SpawnPoint_y);
        void setZeroVelocity();
        void movePlayer();
        void PlayerCollision(short currentRoom, std::vector<std::vector<sf::RectangleShape>> &Wall);

    private:
        std::map<std::string, struct PlayerClassAttibute> PlayerClass;
        void setPlayerClass();
};
#endif