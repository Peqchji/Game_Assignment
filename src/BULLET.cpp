#include "BULLET.h"
void BULLET::setBulletTexture()
{
    this->bulletTexture.loadFromFile("../content/bullet.png");
}
BULLET::BULLET(float init_PosX, float init_PosY, float dir_x, float dir_y, float Speed)
{
    setBulletTexture();
    this->bulletShape.setTexture(bulletTexture);
    this->bulletShape.setOrigin(1, 2);
    this->bulletShape.setPosition(sf::Vector2f(init_PosX, init_PosY));
    this->Direction.x = dir_x;
    this->Direction.y = dir_y;
    this->BulletSpeed = Speed;
}

void BULLET::update(float deltaTime)
{
    this->bulletShape.move(this->BulletSpeed * this->Direction.x * deltaTime, this->BulletSpeed * this->Direction.y * deltaTime);
}

bool BULLET::bulletCollision(std::vector<std::vector<sf::RectangleShape>> &WallHitbox, short currentRoom)
{
    for(auto &element: WallHitbox[currentRoom])
    {
         if((element.getGlobalBounds()).intersects(this->bulletShape.getGlobalBounds()))
         {
            return true;
         }
    }
    return false;
}