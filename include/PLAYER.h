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
            float SkillCooldown;
            float duration;
            float Speed;
            std::string Skill;
            std::string texture;

            PlayerClassAttibute(float _Speed, float _Health, float _Ammor, float _Energy, float _Crit_Chance, float _skillcooldown, float _duration, std::string _texture, std::string _Skill)
            {
                Health = _Health;
                Speed = _Speed;
                Ammor = _Ammor;
                Energy = _Energy;
                Crit_Chance = _Crit_Chance;
                Skill = _Skill;
                SkillCooldown = _skillcooldown;
                duration = _duration;
                texture = _texture; 
            }
        };
        float Cooldown;
        float skillDuration;

        float player_Speed;
        float current_Speed;

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
        void Skillcast(float &multiFireRate);
        sf::Time Cooldown_Skill;

    private:
        std::map<std::string, struct PlayerClassAttibute> PlayerClass;
        std::map<std::string, struct PlayerClassAttibute>::iterator it;

        sftools::Chronometer Animation_CLK;
        sf::Time Animation_Timer;

        sftools::Chronometer Duration_CLK;
        sf::Time Duration_Skill;

        sftools::Chronometer Skill_CLK;

        sf::Texture PlayerTexture;
        int currentAnimation;
        sf::Vector2f textureSize;

        bool skillActivate;
        int healing = 0;

        void setPlayerClass();
};
#endif