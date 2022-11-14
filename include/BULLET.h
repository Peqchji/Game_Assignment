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

        int bulletFrame;
        sftools::Chronometer AnimationCLK;
        sf::Time AnimationTimer;
        sf::Vector2f Spritesize;

    public:
        float bulletDamage;
        sf::Sprite bulletShape;
        sf::RectangleShape bulletHitbox;
         sftools::Chronometer CLK;
         sf::Time Timer;
        BULLET();
        BULLET(float init_PosX, float init_PosY, float dir_x, float dir_y, float damage, float Speed);

        bool bulletCollision(std::vector<std::vector<sf::RectangleShape>> &WallHitbox);
        bool bulletLifeTime();
        void setBulletTexture();
        void update(float deltaTime);
};
#endif