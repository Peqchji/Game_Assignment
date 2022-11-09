#include "BULLET.h"
void BULLET::setBulletTexture()
{
    this->bulletTexture.loadFromFile("../content/Gun/Sprite/bullet.png");
}
BULLET::BULLET(float init_PosX, float init_PosY, float dir_x, float dir_y, float damage, float Speed)
{
    setBulletTexture();
    this->bulletShape.setTexture(bulletTexture);
    this->Spritesize.x = bulletTexture.getSize().x/4;
    this->Spritesize.y = bulletTexture.getSize().y/1;
    this->bulletShape.setTextureRect(sf::IntRect(0, 0, Spritesize.x, Spritesize.y));

    this->bulletShape.setOrigin(Spritesize.x/2.f, Spritesize.y/2.f);
    this->bulletShape.setPosition(sf::Vector2f(init_PosX, init_PosY));
    this->Direction.x = dir_x;
    this->Direction.y = dir_y;
    this->bulletDamage = damage;
    this->BulletSpeed = Speed;
    this->rotate_By = ((static_cast<double>(atan(-dir_x/dir_y))* 180)/3.141592654) + (dir_y > 0? 180:0);
    this->bulletShape.rotate(rotate_By - 90);
    bulletFrame = 0;
    this->CLK.restart();
    this->AnimationCLK.restart();
}

void BULLET::update(float deltaTime)
{
    this->AnimationTimer = this->AnimationCLK.getElapsedTime();
    if(bulletFrame < 4 && AnimationTimer.asMilliseconds() >= 63)
    {
        this->bulletShape.setTextureRect(sf::IntRect(bulletFrame * Spritesize.x, 0, Spritesize.x, Spritesize.y));
        this->AnimationCLK.restart();
        bulletFrame++;
    }
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

bool BULLET::bulletLifeTime()
{
    Timer = CLK.getElapsedTime();
    if(Timer.asSeconds() > 3)
    {
        return true;
    }
    return false;
}