#ifndef ENEMY_H
#define ENEMY_H

#include "MASTER.h"
class ENEMY
{
    public:
        struct EnemyAttribute
        {
            float Damage;
            float Health;
            float Speed;
            int score;

            std::string Texture;
            std::string behaviour;

            EnemyAttribute(float _Damage, float _Health, float _Speed, int _score, std::string _behaviour, std::string _EnemyTexture)
            {
                Damage = _Damage;
                Health = _Health;
                Speed = _Speed;
                score = _score;
                behaviour = _behaviour;
                Texture = _EnemyTexture;
            }
        };
        sf::Vector2f Position;
        sf::Sprite EnemySprite;

        float Enemy_damage;
        float Enemy_Speed;
        float Enemy_Health;
        int Enemy_Score;
        ENEMY();
        ENEMY(float Hardness, float init_Posi_x, float init_Posi_y);

        void update(float &dt, short currentRoom, sf::Vector2f &playerposi, std::vector<std::vector<sf::RectangleShape>> &WallHitbox);
        bool getHitted(sf::Sprite &Bullet, int Amount_Bullet, float ReceivedDamage, float playerCrit, float gunCrit);
        bool Hitting(sf::RectangleShape &playerHitbox);

    private:
        std::map<std::string, struct EnemyAttribute> EnemyType;

        sftools::Chronometer Animation_CLK;
        sf::Time Animation_Timer;
        sftools::Chronometer ZigzagCLK;
        sf::Time ZigzagTimer;

        sftools::Chronometer AttackCLK;
        sf::Time AttackTimer;
        bool active;

        sf::Vector2f EnemyVelocity;


        std::string EntityType;
        std::string behaviour;

        sf::RectangleShape EnemyCollisionHitbox;
        sf::RectangleShape EnemyHitbox;
        sf::Texture EnemyTexture;
        sf::Vector2f TextureSize;

        sf::Vector2f diff_Position;
        sf::Vector2f dir_normal;

        short currentRoomID = 0;
        int EnemyAnimation;
        float HardnessMultiply;

        void setEnemyType();

        bool playerDetected(sf::Vector2f playerPosi);
        void NormalInteract(float delta_Time, sf::Vector2f &Player, std::vector<std::vector<sf::RectangleShape>> Wall);
        void ZigzagInteract(float delta_Time, sf::Vector2f &Player, std::vector<std::vector<sf::RectangleShape>> Wall);
        void WallCollision(std::vector<std::vector<sf::RectangleShape>> Wall);
        bool BulletCollision(sf::Sprite Bullet, int Amount_Bullet);
};

#endif