#include "PLAYER.h"
void PLAYER::setPlayer_attribute(std::string Type)
{
   setPlayerClass();
    auto random_key = PlayerClass.begin();
    std::advance(random_key, rand() % PlayerClass.size());
    it = PlayerClass.find(random_key->first);
    if (it != PlayerClass.end())
	{
		this->collisionHitbox.setSize(sf::Vector2f(::CellPixelSize - 7, (::CellPixelSize)/2) );
   		this->CharModel.setSize(sf::Vector2f(::CellPixelSize, ::CellPixelSize));
		this->Hitbox.setSize(sf::Vector2f(::CellPixelSize - 7, ::CellPixelSize/2.f));

   		this->CharModel.setOrigin(sf::Vector2f(::CellPixelSize/2.f, ::CellPixelSize/2.f));
   		this->collisionHitbox.setOrigin(sf::Vector2f((::CellPixelSize - 7)/2.f, (::CellPixelSize)/4.f));
		this->Hitbox.setOrigin(sf::Vector2f((::CellPixelSize - 7)/2.f, ::CellPixelSize/4.f));

   		// Virsual the Hitbox
   		/*this->Hitbox.setFillColor(sf::Color::Transparent);
   		this->Hitbox.setOutlineColor(sf::Color::Red);
   		this->Hitbox.setOutlineThickness(1.f);*/

   		//Load Texture
   		this->PlayerTexture.loadFromFile(it->second.texture);
   		this->CharModel.setTexture(&PlayerTexture);
   		this->textureSize.x = (this->PlayerTexture.getSize().x)/8.f;
   		this->textureSize.y = (this->PlayerTexture.getSize().y);

		player_Health = it->second.Health;
		current_Health = player_Health;

		player_Ammor = it->second.Ammor;
		current_Ammor = player_Ammor;

		player_Energy = it->second.Energy;
		current_Energy = player_Energy;

		skillDuration = it->second.duration;
		Cooldown = it->second.SkillCooldown;

		player_Crit_Chance = it->second.Crit_Chance;
		current_Crit_Chance = player_Crit_Chance;
		this->player_Skill = it->second.Skill;

   		currentAnimation = 0;
   		this->Animation_CLK.reset(true);
		this->Skill_CLK.reset(true);
		this->Skill_CLK.add(sf::milliseconds(sf::Int32(it->second.SkillCooldown)));

		skillActivate = false;
	}
}

void PLAYER::setPlayerSpawnPos(float SpawnPoint_x,float SpawnPoint_y)
{
   this->collisionHitbox.setPosition(SpawnPoint_x, SpawnPoint_y);
   this->CharModel.setPosition(SpawnPoint_x, SpawnPoint_y - 8);
   this->Hitbox.setPosition(SpawnPoint_x, SpawnPoint_y - 5);
}

void PLAYER::update(float dir_x)
 {
	if(current_Energy > player_Energy)
	{
		current_Energy = player_Energy;
	}
	if(current_Health > player_Health)
	{
		current_Health = player_Health;
	}
	if(current_Health < 0)
	{
		current_Health = 0;
	}
	if(current_Ammor < 0)
	{
		current_Ammor = 0;
	}
   this->Animation_Timer = Animation_CLK.getElapsedTime();
   if(this->Animation_Timer.asMilliseconds() > 125)
   {
		currentAnimation = (currentAnimation + 1) % 4;
		this->Animation_CLK.reset(true);
   }
   
   if(this->velocity.x != 0 || this->velocity.y != 0)
   {
		this->CharModel.setTextureRect(sf::IntRect(this->textureSize.x * (currentAnimation + (dir_x < 0? 5:4)), 0, (dir_x < 0? -1:1) * this->textureSize.x, this->textureSize.y));
   }
   else
   {
		this->CharModel.setTextureRect(sf::IntRect(this->textureSize.x * (currentAnimation + (dir_x < 0? 1:0)), 0, (dir_x < 0? -1:1) * this->textureSize.x, this->textureSize.y));
   }
   this->collisionHitbox.move(this->velocity.x, this->velocity.y);
   this->CharModel.move(this->velocity.x, this->velocity.y);
   this->Hitbox.move(this->velocity.x, this->velocity.y);
 }

void PLAYER::setZeroVelocity()
 {
   this->velocity.x = 0;
   this->velocity.y = 0;
 }
void PLAYER::PlayerCollision(short currentRoom, std::vector<std::vector<sf::RectangleShape>> &Wall)
{
	sf::FloatRect nextPos;
	sf::FloatRect WallBound;
	sf::FloatRect PlayerBound;
	for(auto &element: Wall[currentRoom])
	{
		PlayerBound = this->collisionHitbox.getGlobalBounds();
		nextPos = PlayerBound;
		nextPos.left += this->velocity.x;
		nextPos.top += this->velocity.y;
		WallBound = element.getGlobalBounds();
		if(WallBound.intersects(nextPos))
		{
			if(WallBound.intersects(nextPos))
			{
				//Top Bottom collision
				if(PlayerBound.top != WallBound.top
				&& (PlayerBound.top + PlayerBound.height) != WallBound.top + WallBound.height
				&& PlayerBound.left < WallBound.left + WallBound.width
				&& PlayerBound.left + PlayerBound.width > WallBound.left)
				{
					if(PlayerBound.left + PlayerBound.width*0.1 < WallBound.left
					&& PlayerBound.left < WallBound.left)
					{
						this->CharModel.move(-this->velocity.x + (PlayerBound.top > WallBound.top? 1:-1) * this->velocity.y, 0);
          				this->collisionHitbox.move(-this->velocity.x + (PlayerBound.top > WallBound.top? 1:-1) * this->velocity.y, 0);
						this->Hitbox.move(-this->velocity.x + (PlayerBound.top > WallBound.top? 1:-1) * this->velocity.y, 0);
					}
					else if(PlayerBound.left + PlayerBound.width*0.9 > WallBound.width + WallBound.width
					&& PlayerBound.left + PlayerBound.width > WallBound.left + WallBound.width)
					{
						this->CharModel.move(-this->velocity.x -  (PlayerBound.top > WallBound.top? 1:-1) * this->velocity.y, 0);
          				this->collisionHitbox.move(-this->velocity.x -  (PlayerBound.top > WallBound.top? 1:-1) * this->velocity.y, 0);
						this->Hitbox.move(-this->velocity.x -  (PlayerBound.top > WallBound.top? 1:-1) * this->velocity.y, 0);
					}

					this->CharModel.move(0, -this->velocity.y);
          			this->collisionHitbox.move(0, -this->velocity.y);
					this->Hitbox.move(0, -this->velocity.y);
				}
			
				//Left Right collision
				if(PlayerBound.left != WallBound.left 
				&& (PlayerBound.left + PlayerBound.width) != WallBound.left + WallBound.width 
				&& PlayerBound.top < WallBound.top + WallBound.height
				&& PlayerBound.top + PlayerBound.height > WallBound.top)
				{
					if(PlayerBound.top + PlayerBound.height*0.1 < WallBound.top
					&& PlayerBound.top < WallBound.top)
					{
						this->CharModel.move(0, (PlayerBound.left > WallBound.left? 1:-1)  * this->velocity.x - this->velocity.y);
          				this->collisionHitbox.move(0, (PlayerBound.left > WallBound.left? 1:-1)  *this->velocity.x - this->velocity.y);
						this->Hitbox.move(0, (PlayerBound.left > WallBound.left? 1:-1)  *this->velocity.x - this->velocity.y);
					}
					else if(PlayerBound.top + PlayerBound.height*0.9 > WallBound.top + WallBound.height
					&& PlayerBound.top + PlayerBound.height > WallBound.top + WallBound.height)
					{
						this->CharModel.move(0, -(PlayerBound.left > WallBound.left? 1:-1) * this->velocity.x - this->velocity.y);
          				this->collisionHitbox.move(0, -(PlayerBound.left > WallBound.left? 1:-1)  * this->velocity.x - this->velocity.y);
						this->Hitbox.move(0, -(PlayerBound.left > WallBound.left? 1:-1)  * this->velocity.x - this->velocity.y);
					}
					this->CharModel.move(-this->velocity.x, 0);
          			this->collisionHitbox.move(-this->velocity.x, 0);
					this->Hitbox.move(-this->velocity.x, 0);
				}
			}
		}
	}
}

//private//
void PLAYER::setPlayerClass()
{
  PlayerClass = 
  {
    {"Knight", PlayerClassAttibute(6, 5, 180, 5, 45000,  5000, std::string("../content/Sprite/Knight.png"), std::string("Dual Wielding"))},
    {"Priest", PlayerClassAttibute(12, 3, 200, 1, 90000, 4000, std::string("../content/Sprite/Priest.png"), std::string("Heal"))},
    {"Rogue" , PlayerClassAttibute(5, 3, 180, 10, 30000, 5000, std::string("../content/Sprite/Rogue.png"), std::string("FatalShot"))}
  };
}

void PLAYER::Skillcast(float &multiFireRate)
{
	this->Cooldown_Skill = this->Skill_CLK.getElapsedTime();
	if(this->Cooldown_Skill.asMilliseconds() >= Cooldown)
	{
		this->Cooldown_Skill = sf::milliseconds(it->second.SkillCooldown);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && this->Cooldown_Skill.asMilliseconds() >= Cooldown)
	{
		this->Duration_CLK.reset(true);
		skillActivate = true;
	}
	this->Duration_Skill = this->Duration_CLK.getElapsedTime();
	if(skillActivate && Duration_Skill.asMilliseconds() <= skillDuration)
	{
		this->Skill_CLK.reset(true);
		if(it->second.Skill.compare("Dual Wielding") == 0)
		{
			multiFireRate = 2.f;
		}
		else if((it->second.Skill.compare("Heal") == 0) && Duration_Skill.asMilliseconds()%1000 ==  0)
		{
			current_Health += 1;
		}
		else
		{
			current_Crit_Chance = 100.f;
		}
	}
	else
	{
		skillActivate = false;
		multiFireRate = 1.f;
		current_Crit_Chance = player_Crit_Chance;
	}
}