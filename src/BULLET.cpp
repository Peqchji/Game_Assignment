#include "BULLET.h"

BULLET::BULLET(sf::Texture &Texture, float dir_x, float dir_y, float Speed)
{
    this->bulletShape.setTexture(Texture);
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