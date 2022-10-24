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
    this->rotate_By = ((static_cast<double>(atan(-dir_x/dir_y))* 180)/3.141592654) + (dir_y > 0? 180:0);
    this->bulletShape.rotate(rotate_By);
}

void BULLET::update(float deltaTime)
{
    this->bulletShape.move(this->BulletSpeed * this->Direction.x * deltaTime, this->BulletSpeed * this->Direction.y * deltaTime);
}

bool BULLET::bulletCollision(std::vector<std::vector<sf::RectangleShape>> &WallHitbox)
{
    short i = 0;
    while(i < WallHitbox.size())
    {
        for(auto &element: WallHitbox[i])
        {
            if((element.getGlobalBounds()).intersects(this->bulletShape.getGlobalBounds()))
            {
                return true;
            }
        }
        ++i;
    }
    return false;
}