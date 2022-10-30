#include "ENEMY.h"
ENEMY::ENEMY(std::string Type,  float init_Posi_x, float init_Posi_y)
{
    setEnemyType();
    std::map<std::string, struct EnemyAttribute>::iterator it;
    auto random_key = EnemyType.begin();
    std::advance(random_key, rand() % EnemyType.size());
    EntityType = random_key->first;
    it = EnemyType.find(EntityType);
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
    {"MiniDemon", EnemyAttribute(2.f, 15.f, 50.f, std::string("Normal") ,std::string("../content/Sprite/MiniDemon.png"))},
    {"Splinter", EnemyAttribute(2.f, 1.f, 125.f, std::string("Normal") ,std::string("../content/Sprite/Splinter.png"))}
  };
}

bool ENEMY::playerDetected(sf::Vector2f playerPosi)
{
    double distance;
    double distance_REf;
    int detection_Dist = (EntityType.compare("Splinter") == 0? 10: 6);
    this->Position = this->EnemySprite.getPosition();
    this->diff_Position = playerPosi - this->Position - sf::Vector2f(0.f, 8.f);
    distance = sqrt(pow(diff_Position.x, 2) + pow(diff_Position.y, 2));
    dir_normal = diff_Position / static_cast<float>(distance);
    if(distance < ::CellPixelSize * detection_Dist)
        { return true; }
    return false;
}

void ENEMY::NormalInteract(float delta_Time, sf::Vector2f &Player)
{
    this->EnemySprite.move(dir_normal.x * Enemy_Speed * delta_Time, dir_normal.y * Enemy_Speed * delta_Time);
}

void ENEMY::update(float dt, sf::Vector2f playerposi)
{
    this->Animation_Timer = this->Animation_CLK.getElapsedTime();
    if(Animation_Timer.asMilliseconds() > 125)
    {
        EnemyAnimation = (EnemyAnimation + 1) % 4;
        this->Animation_CLK.restart();
    }
    if(playerDetected(playerposi))
    {
        this->EnemySprite.setTextureRect(sf::IntRect(this->TextureSize.x * (EnemyAnimation + 4 + (dir_normal.x<0? 1:0)), 0, (dir_normal.x<0? -1:1) * this->TextureSize.x, this->TextureSize.y));
        NormalInteract(dt, playerposi);
    }
    else
        this->EnemySprite.setTextureRect(sf::IntRect(this->TextureSize.x * (EnemyAnimation + (dir_normal.x<0? 1:0)), 0, (dir_normal.x<0? -1:1) * this->TextureSize.x, this->TextureSize.y));

}