#include "PLAYER.h"
void PLAYER::setPlayer_attribute()
{
   //Assign Hitbox size
   this->collisionHitbox.setSize(sf::Vector2f(::CellPixelSize - 7, (::CellPixelSize - 6)/2) );
   this->CharModel.setSize(sf::Vector2f(::CellPixelSize, ::CellPixelSize));

   this->CharModel.setOrigin(sf::Vector2f(::CellPixelSize/2.f, ::CellPixelSize/2.f));
   this->collisionHitbox.setOrigin(sf::Vector2f((::CellPixelSize - 6)/2.f, (::CellPixelSize - 6)/4.f));

   // Virsual the Hitbox
   this->collisionHitbox.setFillColor(sf::Color::Transparent);
   this->collisionHitbox.setOutlineColor(sf::Color::Red);
   this->collisionHitbox.setOutlineThickness(1.f);

  this->CharModel.setFillColor(sf::Color::White);
   //Load Texture
   this->PlayerTexture.loadFromFile("../content/Sprite/doc.png");
   this->CharModel.setTexture(&PlayerTexture);
   this->textureSize.x = (this->PlayerTexture.getSize().x);
   this->textureSize.y = (this->PlayerTexture.getSize().y);
   this->textureSize.x /= 8;
   this->textureSize.y /= 1;
}

void PLAYER::setPlayerSpawnPos(float SpawnPoint_x,float SpawnPoint_y)
{
   this->collisionHitbox.setPosition(SpawnPoint_x, SpawnPoint_y);
   this->CharModel.setPosition(SpawnPoint_x, SpawnPoint_y - 8);
}

void PLAYER::movePlayer()
 {
   this->collisionHitbox.move(this->velocity.x, this->velocity.y);
   this->CharModel.move(this->velocity.x, this->velocity.y);
 }

void PLAYER::setZeroVelocity()
 {
   this->velocity.x = 0;
   this->velocity.y = 0;
 }

//private//
void PLAYER::setPlayerClass()
{
  PlayerClass = 
  {
    {"Knight", PlayerClassAttibute(6, 5, 180, 5, "Dual Wielding")},
    {"Priest", PlayerClassAttibute(12, 3, 200, 1, "Heal")},
    {"Rogue" , PlayerClassAttibute(5, 3, 180, 10, "FatalShot")}
  };
}