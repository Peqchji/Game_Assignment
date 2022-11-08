#ifndef BULLET_H
#define BULLET_H
#include "MASTER.h"
class BULLET
{
    private:
        sf::Texture bulletTexture;
        sf::Vector2f Direction;
        float BulletSpeed;
        double rotate_By;
        short AimDirRotate;

    public:
        float bulletDamage;
        sf::Sprite bulletShape;
        BULLET();
        BULLET(float init_PosX, float init_PosY, float dir_x, float dir_y, float damage, float Speed);

        bool bulletCollision(std::vector<std::vector<sf::RectangleShape>> &WallHitbox);
        bool bulletLifeTime();
        void setBulletTexture();
        void update(float deltaTime);

        sf::Clock CLK;
        sf::Time Timer;
};
#endif