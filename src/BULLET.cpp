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
    
    this->bulletHitbox.setSize(sf::Vector2f(Spritesize.x/4.f, Spritesize.y/3.f));
    this->bulletHitbox.setOrigin(sf::Vector2f(Spritesize.x/8.f, Spritesize.y/6.f));
    this->bulletHitbox.setOutlineThickness(1.f);
    this->bulletHitbox.setFillColor(sf::Color::Transparent);
    this->bulletHitbox.setOutlineColor(sf::Color::Red);

    this->bulletShape.setOrigin(sf::Vector2f(0, Spritesize.y/2.f));
    this->bulletShape.setPosition(sf::Vector2f(init_PosX, init_PosY));
    this->Direction.x = dir_x;
    this->Direction.y = dir_y;
    this->bulletDamage = damage;
    this->BulletSpeed = Speed;
    this->rotate_By = ((static_cast<double>(atan(-dir_x/dir_y))* 180)/3.141592654) + (dir_y > 0? 180:0) - 90;
    this->bulletShape.rotate(rotate_By);
    this->bulletHitbox.rotate(rotate_By);
    bulletFrame = 0;
    this->CLK.reset(true);
    this->AnimationCLK.reset(true);
}

void BULLET::update(float deltaTime)
{
    this->AnimationTimer = this->AnimationCLK.getElapsedTime();
    if(bulletFrame < 4 && AnimationTimer.asMilliseconds() >= 63)
    {
        this->bulletShape.setTextureRect(sf::IntRect(bulletFrame * Spritesize.x, 0, Spritesize.x, Spritesize.y));
        this->AnimationCLK.reset(true);
        bulletFrame++;
    }
    this->bulletShape.move(this->BulletSpeed * this->Direction.x * deltaTime, this->BulletSpeed * this->Direction.y * deltaTime);
    this->bulletHitbox.setPosition(sf::Vector2f(bulletShape.getPosition().x + Spritesize.x/2.f * this->Direction.x, bulletShape.getPosition().y + Spritesize.x/2.f * this->Direction.y)) ;
}

bool BULLET::bulletCollision(std::vector<std::vector<sf::RectangleShape>> &WallHitbox)
{
    short i = 0;
    while(i < WallHitbox.size())
    {
        for(auto &element: WallHitbox[i])
        {
            if((element.getGlobalBounds()).intersects(this->bulletHitbox.getGlobalBounds()))
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

void BULLET::ToggleCLK()
{
    CLK.toggle();
    AnimationCLK.toggle();
}