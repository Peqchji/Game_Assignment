#include "ENEMY.h"
ENEMY::ENEMY(std::string Type,  float init_Posi_x, float init_Posi_y)
{
    setEnemyType();
    std::map<std::string, struct EnemyAttribute>::iterator it;
    it = EnemyType.find(Type);
    if (it != EnemyType.end())
    {
        Enemy_damage = it->second.Damage;
        Enemy_Health = it->second.Health;
        Enemy_Speed = it->second.Speed;
        this->EnemySprite.setPosition(init_Posi_x, init_Posi_y);
        this->EnemyTexture.loadFromFile(it->second.Texture);
        this->EnemySprite.setTexture(this->EnemyTexture);
        this->TextureSize.x = this->EnemyTexture.getSize().x/8;
        this->TextureSize.y = this->EnemyTexture.getSize().y;
        this->EnemySprite.setOrigin(sf::Vector2f(this->TextureSize.x/2.f,  this->TextureSize.y/2.f));
        EnemyAnimation = 0;
        this->Animation_CLK.restart(); 
    }
}
void  ENEMY::setEnemyType()
{
    EnemyType = 
  {
     {"MiniDemon", EnemyAttribute(3.f, 15.f, 40.f, std::string("Normal") ,std::string("../content/Sprite/MiniDemon.png"))}
  };
}

bool ENEMY::playerCheck(sf::Vector2f &playerPosi)
{
    double distance;
    diff_Position =  playerPosi - Position;
    distance = sqrt(pow(diff_Position.x, 2) + pow(diff_Position.y, 2));
    dir_normal = diff_Position / static_cast<float>(distance);
    if(distance <= ::CellPixelSize * 5)
        { return true; }
    return false;
}

void ENEMY::NormalInteract(float delta_Time, sf::Vector2f &Player)
{
    if(playerCheck(Player))
    {
        this->EnemySprite.move(dir_normal.x * Enemy_Speed * delta_Time, dir_normal.y * Enemy_Speed * delta_Time);
    }
}

void ENEMY::update()
{
    this->Animation_Timer = this->Animation_CLK.getElapsedTime();
    if(Animation_Timer.asMilliseconds() > 125)
    {
        EnemyAnimation = (EnemyAnimation + 1) % 5;
        this->Animation_CLK.restart();
    }
    this->EnemySprite.setTextureRect(sf::IntRect(this->TextureSize.x * (EnemyAnimation), 0, this->TextureSize.x, this->TextureSize.y));
}