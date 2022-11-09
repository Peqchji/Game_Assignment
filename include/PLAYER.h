#ifndef PLAYER_H
#define PLAYER_H

#include "MASTER.h"
class PLAYER{
    public:
        struct PlayerClassAttibute
        {
            float Health;
            float Ammor;
            float Energy;
            float Crit_Chance;
            std::string Skill;
            std::string texture;

            PlayerClassAttibute(float _Health, float _Ammor, float _Energy, float _Crit_Chance, std::string _texture, std::string _Skill)
            {
                Health = _Health;
                Ammor = _Ammor;
                Energy = _Energy;
                Crit_Chance = _Crit_Chance;
                Skill = _Skill;
                texture = _texture; 
            }
        };

        float player_Health;
        float current_Health;

        float player_Ammor;
        float current_Ammor;

        float player_Energy;
        float current_Energy;
        
        float player_Crit_Chance;
        float current_Crit_Chance;
        std::string player_Skill;

        sf::Vector2f velocity;

        sf::RectangleShape collisionHitbox;
        sf::RectangleShape CharModel;
        sf::RectangleShape Hitbox;
        

        void setPlayer_attribute(std::string Type);
        void setPlayerSpawnPos(float SpawnPoint_x,float SpawnPoint_y);
        void setZeroVelocity();
        void update(float dir_x);
        void PlayerCollision(short currentRoom, std::vector<std::vector<sf::RectangleShape>> &Wall);

    private:
        std::map<std::string, struct PlayerClassAttibute> PlayerClass;
        sf::Clock Animation_CLK;
        sf::Time Animation_Timer;
        sf::Texture PlayerTexture;
        int currentAnimation;
        sf::Vector2f textureSize;
        void setPlayerClass();
};
#endif