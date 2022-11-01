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

        this->EnemyCollisionHitbox.setSize(sf::Vector2f(TextureSize.x - 7, (TextureSize.y - 6)/2.f));
        this->EnemyCollisionHitbox.setOrigin(sf::Vector2f((TextureSize.x - 7)/2.f, (TextureSize.y - 6)/4.f));
        this->EnemyCollisionHitbox.setPosition(init_Posi_x, init_Posi_y + 8);

        this->Animation_CLK.restart(); 
    }
}
void  ENEMY::setEnemyType()
{
    EnemyType = 
  {
    {"MiniDemon", EnemyAttribute(2.f, 15.f, 50.f, std::string("Normal") ,std::string("../content/Sprite/MiniDemon.png"))},
    {"Splinter", EnemyAttribute(2.f, 1.f, 100.f, std::string("Normal") ,std::string("../content/Sprite/Splinter.png"))}
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
    dir_normal.x = diff_Position.x / static_cast<float>(distance);
    dir_normal.y = diff_Position.y / static_cast<float>(distance);
    if(distance < ::CellPixelSize * detection_Dist)
        { return true; }
    return false;
}

void ENEMY::NormalInteract(float delta_Time, sf::Vector2f &Player,  std::vector<std::vector<sf::RectangleShape>> Wall)
{
    EnemyVelocity = dir_normal * Enemy_Speed * delta_Time;
    WallCollision(Wall);
    this->EnemyCollisionHitbox.move(EnemyVelocity.x, EnemyVelocity.y);
    this->EnemySprite.move(EnemyVelocity.x, EnemyVelocity.y);
}

void ENEMY::update(float dt, sf::Vector2f playerposi, std::vector<std::vector<sf::RectangleShape>> &WallHitbox)
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
        NormalInteract(dt, playerposi, WallHitbox);
    }
    else
        this->EnemySprite.setTextureRect(sf::IntRect(this->TextureSize.x * (EnemyAnimation + (dir_normal.x<0? 1:0)), 0, (dir_normal.x<0? -1:1) * this->TextureSize.x, this->TextureSize.y));

}

void ENEMY::WallCollision(std::vector<std::vector<sf::RectangleShape>> Wall)
{
    int i = 0;
    sf::FloatRect nextPos;
	sf::FloatRect WallBound;
	sf::FloatRect EnemyBound;

    while(i < Wall.size())
    {
        for(auto &element: Wall[i])
        {
            EnemyBound = this->EnemyCollisionHitbox.getGlobalBounds();
            nextPos = EnemyBound;
            nextPos.left += this->EnemyVelocity.x;
            nextPos.top += this->EnemyVelocity.y;
            WallBound = element.getGlobalBounds();
            if(WallBound.intersects(nextPos))
            {
                if(WallBound.intersects(nextPos))
                {
                    //Top and Bottom collision
                    if(EnemyBound.top != WallBound.top 
                    && (EnemyBound.top + EnemyBound.height) != WallBound.top + WallBound.height 
                    && EnemyBound.left < WallBound.left + WallBound.width 
                    && EnemyBound.left + EnemyBound.width > WallBound.left)
                    {
                        if(EnemyBound.left + EnemyBound.width*0.1 < WallBound.left
					    && EnemyBound.left < WallBound.left)
					    {
					    	this->EnemySprite.move(-this->EnemyVelocity.x + (EnemyBound.top > WallBound.top? 1:-1) * this->EnemyVelocity.y, 0);
          			    	this->EnemyCollisionHitbox.move(-this->EnemyVelocity.x + (EnemyBound.top > WallBound.top? 1:-1) * this->EnemyVelocity.y, 0);
					    }
					    else if(EnemyBound.left + EnemyBound.width*0.9 > WallBound.width + WallBound.width
					    && EnemyBound.left + EnemyBound.width > WallBound.left + WallBound.width)
					    {
					    	this->EnemySprite.move(-this->EnemyVelocity.x -  (EnemyBound.top > WallBound.top? 1:-1) * this->EnemyVelocity.y, 0);
          			    	this->EnemyCollisionHitbox.move(-this->EnemyVelocity.x -  (EnemyBound.top > WallBound.top? 1:-1) * this->EnemyVelocity.y, 0);
					    }

                        this->EnemySprite.move(0, -(this->EnemyVelocity.y));
                        this->EnemyCollisionHitbox.move(0, -(this->EnemyVelocity.y));
                    }

                    //Right collision
                    if(EnemyBound.left != WallBound.left 
                    && (EnemyBound.left + EnemyBound.width) != (WallBound.left + WallBound.width )
                    && (EnemyBound.top < WallBound.top + WallBound.height)
                    && EnemyBound.top + EnemyBound.height > WallBound.top)
                    {
                        if(EnemyBound.top + EnemyBound.height*0.1 < WallBound.top
					    && EnemyBound.top < WallBound.top)
					    {
					    	this->EnemySprite.move(0, (EnemyBound.left > WallBound.left? 1:-1)  * this->EnemyVelocity.x - this->EnemyVelocity.y);
          			    	this->EnemyCollisionHitbox.move(0, (EnemyBound.left > WallBound.left? 1:-1)  *this->EnemyVelocity.x - this->EnemyVelocity.y);
					    }
					    else if(EnemyBound.top + EnemyBound.height*0.9 > WallBound.top + WallBound.height
					    && EnemyBound.top + EnemyBound.height > WallBound.top + WallBound.height)
					    {
					    	this->EnemySprite.move(0, -(EnemyBound.left > WallBound.left? 1:-1) * this->EnemyVelocity.x - this->EnemyVelocity.y);
          			    	this->EnemyCollisionHitbox.move(0, -(EnemyBound.left > WallBound.left? 1:-1)  * this->EnemyVelocity.x - this->EnemyVelocity.y);
					    }
                        this->EnemySprite.move(-(this->EnemyVelocity.x), 0);
                        this->EnemyCollisionHitbox.move(-(this->EnemyVelocity.x), 0);
                    }
                }
            }
        }
        i++;
    }
}