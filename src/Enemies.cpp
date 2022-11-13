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
        Enemy_Score = it->second.score;
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
        
        this->EnemyHitbox.setSize(sf::Vector2f(TextureSize.x - 7, ((TextureSize.y)/2.f)));
		this->EnemyHitbox.setOrigin(sf::Vector2f((TextureSize.x - 7)/2.f, (TextureSize.y)/4.f));
        this->EnemyHitbox.setPosition(init_Posi_x, init_Posi_y + 5);
        this->EnemyHitbox.setFillColor(sf::Color::Transparent);
        this->EnemyHitbox.setOutlineColor(sf::Color::Red);
        this->EnemyHitbox.setOutlineThickness(1.f);

        this->Animation_CLK.restart(); 
        this->ZigzagCLK.restart();
    }
}

void ENEMY::update(float &dt, short currentRoom,sf::Vector2f &playerposi, std::vector<std::vector<sf::RectangleShape>> &WallHitbox)
{
    currentRoomID = currentRoom;
    this->Animation_Timer = this->Animation_CLK.getElapsedTime();
    if(Animation_Timer.asMilliseconds() > 125)
    {
        EnemyAnimation = (EnemyAnimation + 1) % 4;
        this->Animation_CLK.restart();
    }
    if(playerDetected(playerposi))
    {
        this->EnemySprite.setTextureRect(sf::IntRect(this->TextureSize.x * (EnemyAnimation + 4 + (dir_normal.x<0? 1:0)), 0, (dir_normal.x<0? -1:1) * this->TextureSize.x, this->TextureSize.y));
        if(EntityType.compare("toxicSlime") == 0)
        {
            ZigzagInteract(dt, playerposi, WallHitbox);
        }
        else
        {
           NormalInteract(dt, playerposi, WallHitbox);
        }
    }
    else
    {
        ZigzagCLK.restart();
        this->EnemySprite.setTextureRect(sf::IntRect(this->TextureSize.x * (EnemyAnimation + (dir_normal.x<0? 1:0)), 0, (dir_normal.x<0? -1:1) * this->TextureSize.x, this->TextureSize.y));
    }

}

bool ENEMY::getHitted(sf::Sprite &Bullet, int Amount_Bullet, float ReceivedDamage)
{
    bool isHit = false;
    if(BulletCollision(Bullet, Amount_Bullet))
    {
        Enemy_Health -= ReceivedDamage;
        isHit = true;
    }
    return isHit;
}

//Private
void  ENEMY::setEnemyType()
{
    EnemyType = 
  {
    {"MiniDemon", EnemyAttribute(2.f, 15.f, 64.f, 100, std::string("Normal") ,std::string("../content/Sprite/MiniDemon.png"))},
    {"Splinter", EnemyAttribute(2.f, 1.f, 114.f, 50, std::string("Normal") ,std::string("../content/Sprite/Splinter.png"))},
    {"toxicSlime", EnemyAttribute(3.f, 10.f, 74.f, 100, std::string("Normal") ,std::string("../content/Sprite/toxicSlime.png"))}
  };
}

bool ENEMY::playerDetected(sf::Vector2f playerPosi)
{
    double distance;
    double distance_REf;
    int detection_Dist;
    if(EntityType.compare("Splinter") == 0)
    {
        detection_Dist = 10;
    }
    else if(EntityType.compare("toxicSlime") == 0)
    {
        detection_Dist = 8;
    }
    else
    {
        detection_Dist = 6;
    }
    this->Position = this->EnemySprite.getPosition();
    this->diff_Position = playerPosi - this->Position - sf::Vector2f(0, 8.f);
    
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
    this->EnemyHitbox.move(EnemyVelocity.x, EnemyVelocity.y);
    this->EnemySprite.move(EnemyVelocity.x, EnemyVelocity.y);
}

void ENEMY::ZigzagInteract(float delta_Time, sf::Vector2f &Player,  std::vector<std::vector<sf::RectangleShape>> Wall)
{
    this->ZigzagTimer = this->ZigzagCLK.getElapsedTime();
    double radius = (sin(this->ZigzagTimer.asSeconds()* 3.00));
    this->EnemyVelocity.x = static_cast<float>((dir_normal.x + (dir_normal.y * radius)) * Enemy_Speed * delta_Time);
    this->EnemyVelocity.y = static_cast<float>((dir_normal.y + (dir_normal.x * radius)) * Enemy_Speed * delta_Time);
    WallCollision(Wall);
    this->EnemyCollisionHitbox.move(EnemyVelocity.x, EnemyVelocity.y);
    this->EnemyHitbox.move(EnemyVelocity.x, EnemyVelocity.y);
    this->EnemySprite.move(EnemyVelocity.x, EnemyVelocity.y);
}

void ENEMY::WallCollision(std::vector<std::vector<sf::RectangleShape>> Wall)
{
    sf::FloatRect nextPos;
	sf::FloatRect WallBound;
	sf::FloatRect EnemyBound;
    for(auto &element: Wall[currentRoomID])
    {
        EnemyBound = this->EnemyCollisionHitbox.getGlobalBounds();
        nextPos = EnemyBound;
        nextPos.left += this->EnemyVelocity.x;
        nextPos.top += this->EnemyVelocity.y;
        WallBound = element.getGlobalBounds();
        if(WallBound.intersects(nextPos))
        {
            EnemyBound = this->EnemyCollisionHitbox.getGlobalBounds();
            nextPos = EnemyBound;
            nextPos.left += this->EnemyVelocity.x;
            nextPos.top += this->EnemyVelocity.y;
            WallBound = element.getGlobalBounds();
            if(WallBound.intersects(nextPos))
            {
                //Top and Bottom collision
                if(EnemyBound.top != WallBound.top 
                && (EnemyBound.top + EnemyBound.height) != WallBound.top + WallBound.height 
                && EnemyBound.left < WallBound.left + WallBound.width 
                && EnemyBound.left + EnemyBound.width > WallBound.left)
                {
                    float slideDIR = (EnemyBound.top > WallBound.top? 1:-1) * this->EnemyVelocity.y;

                    if(EnemyBound.left + EnemyBound.width*0.1 < WallBound.left
				    && EnemyBound.left < WallBound.left)
				    {
				    	this->EnemySprite.move(-this->EnemyVelocity.x + slideDIR, 0);
      			    	this->EnemyCollisionHitbox.move(-this->EnemyVelocity.x + slideDIR, 0);
                        this->EnemyHitbox.move(-this->EnemyVelocity.x + slideDIR, 0);
				    }
				    else if(EnemyBound.left + EnemyBound.width*0.9 > WallBound.width + WallBound.width
				    && EnemyBound.left + EnemyBound.width > WallBound.left + WallBound.width)
				    {
				    	this->EnemySprite.move(-this->EnemyVelocity.x - slideDIR, 0);
      			    	this->EnemyCollisionHitbox.move(-this->EnemyVelocity.x - slideDIR, 0);
                        this->EnemyHitbox.move(-this->EnemyVelocity.x - slideDIR, 0);
				    }
                    this->EnemySprite.move(0, -(this->EnemyVelocity.y));
                    this->EnemyCollisionHitbox.move(0, -(this->EnemyVelocity.y));
                    this->EnemyHitbox.move(0, -(this->EnemyVelocity.y));
                }
                //Right collision
                if(EnemyBound.left != WallBound.left 
                && (EnemyBound.left + EnemyBound.width) != (WallBound.left + WallBound.width )
                && (EnemyBound.top < WallBound.top + WallBound.height)
                && EnemyBound.top + EnemyBound.height > WallBound.top)
                {
                    float slideDIR = (EnemyBound.left + EnemyBound.width*0.5 > WallBound.left + WallBound.width? 1:-1) * this->EnemyVelocity.x;

                    if(EnemyBound.top + EnemyBound.height*0.1 < WallBound.top
				    && EnemyBound.top < WallBound.top)
				    {
				    	this->EnemySprite.move(0, -this->EnemyVelocity.y + slideDIR);
      			    	this->EnemyCollisionHitbox.move(0, -this->EnemyVelocity.y + slideDIR);
                        this->EnemyHitbox.move(0, -this->EnemyVelocity.y + slideDIR);
				    }
				    else if(EnemyBound.top + EnemyBound.height*0.9 > WallBound.top + WallBound.height
				    && EnemyBound.top + EnemyBound.height > WallBound.top + WallBound.height)
				    {
				    	this->EnemySprite.move(0, -slideDIR - this->EnemyVelocity.y);
      			    	this->EnemyCollisionHitbox.move(0, -slideDIR - this->EnemyVelocity.y);
                        this->EnemyHitbox.move(0, -slideDIR - this->EnemyVelocity.y);
				    }
                    this->EnemySprite.move(-(this->EnemyVelocity.x), 0);
                    this->EnemyCollisionHitbox.move(-(this->EnemyVelocity.x), 0);
                    this->EnemyHitbox.move(-(this->EnemyVelocity.x), 0);
                }
            }
        }
    }
}

bool ENEMY::BulletCollision(sf::Sprite Bullet, int Amount_Bullet)
{
    int i = 0;
    while(i <  Amount_Bullet)
    {
        if((Bullet.getGlobalBounds()).intersects(this->EnemyHitbox.getGlobalBounds()))
        {
            return true;
        }
        ++i;
    }
    return false;
}