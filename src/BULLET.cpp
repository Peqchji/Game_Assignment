#include "BULLET.h"

BULLET::BULLET(float dir_x, float dir_y, float Speed)
{
    this->bulletShape.setTexture(*bulletTexture);
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