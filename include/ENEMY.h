#ifndef ENEMY_H
#define ENEMY_H

#include "MASTER.h"
class ENEMY
{
    public:
        sf::Sprite EnemySprite;
        sf::Texture EnemyTexture;
        sf::Vector2f Position;
        float Damage;
        float Health;
        float Speed;
};

#endif