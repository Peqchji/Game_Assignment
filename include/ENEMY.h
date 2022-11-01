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

            std::string Texture;
            std::string behaviour;

            EnemyAttribute(float _Damage, float _Health, float _Speed, std::string _behaviour, std::string _EnemyTexture)
            {
                Damage = _Damage;
                Health = _Health;
                Speed = _Speed;
                behaviour = _behaviour;
                Texture = _EnemyTexture;
            }
        };

        float Enemy_damage;
        float Enemy_Speed;
        float Enemy_Health;
        int EnemyAnimation;
        
        std::string EntityType;
        std::string behaviour;
        sf::Vector2f Position;
        sf::Sprite EnemySprite;
        sf::Texture EnemyTexture;
        sf::Vector2f TextureSize;

        sf::Vector2f diff_Position;
        sf::Vector2f dir_normal;

        ENEMY();
        ENEMY(std::string Type, float init_Posi_x, float init_Posi_y);

        void update(float dt, sf::Vector2f playerposi, std::vector<std::vector<sf::RectangleShape>> &WallHitbox);
        void getHitted();

    private:
        std::map<std::string, struct EnemyAttribute> EnemyType;
        sf::Clock Animation_CLK;
        sf::Time Animation_Timer;

        sf::Vector2f EnemyVelocity;
        sf::RectangleShape EnemyHitbox;
        sf::RectangleShape EnemyCollisionHitbox;

        void setEnemyType();

        bool playerDetected(sf::Vector2f playerPosi);
        void NormalInteract(float delta_Time, sf::Vector2f &Player, std::vector<std::vector<sf::RectangleShape>> Wall);
        
        void WallCollision(std::vector<std::vector<sf::RectangleShape>> Wall);

};

#endif