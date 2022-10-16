#include "BULLET.h"
BULLET::BULLET()
{
    //this->bulletTexture.loadFromFile("../content/bullet.png");
}
BULLET::BULLET(float init_PosX, float init_PosY, float dir_x, float dir_y, float Speed)
{
    //this->bulletShape.setTexture(bulletTexture);
    this->bulletShape.setRadius(2.f);
    this->bulletShape.setOrigin(2, 2);
    this->bulletShape.setPosition(init_PosX, init_PosY);
    this->bulletShape.setFillColor(sf::Color::Red);
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