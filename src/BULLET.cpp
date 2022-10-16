#include "BULLET.h"
BULLET::BULLET(float init_PosX, float init_PosY, float dir_x, float dir_y, float Speed)
{
    this->bulletShape.setOrigin(1, 1);
    this->bulletShape.setPosition(init_PosX, init_PosY);
    this->Direction.x = dir_x;
    this->Direction.y = dir_y;
}

void BULLET::update()
{
    this->bulletShape.move(this->BulletSpeed * this->Direction);
}

void BULLET::render(sf::RenderTarget* target)
{
    target->draw(this->bulletShape);
}