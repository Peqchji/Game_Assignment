#include "WEAPON.h"
WEAPON::WEAPON()
{
    setGunType();
}
void WEAPON::init_Gun(std::string Type, float playerPosi_x, float playerPosi_y)
{
  it = GunType.find(Type);
  if (it != GunType.end())
  {
    Dealing_Damge = it->second.Damage;
    FireRate = 1000/(it->second.RoundPerSec);
    Cost = it->second.EnergyCost;
    Crit = it->second.CritChance;
    this->GunTexture = it->second.Texture;
    this->GunModel.setTexture(GunTexture);
    this->MuzzelPoint = it->second.Muzzel;
    this->HoldingPosi = it->second.Holding * scaledown_sprite;

    this->GunModel.setScale(scaledown_sprite, scaledown_sprite);
    //this->GunModel.setOrigin(this->HoldingPosi*scaledown_sprite);
    this->GunModel.setPosition(playerPosi_x, playerPosi_y);
  }
}
void WEAPON::update(float Posi_x, float Posi_y, float dir_x, float dir_y)
{
  short Direction = (dir_x > 0? 1: -1);
  this->GunModel.setTextureRect(sf::IntRect(0, (dir_x > 0? 0: 1) * GunTexture.getSize().y, GunTexture.getSize().x, Direction * GunTexture.getSize().y));
  this->GunModel.setOrigin(this->HoldingPosi.x, (dir_x > 0? this->HoldingPosi.y: (this->GunTexture.getSize().y - this->HoldingPosi.y)));
  this->GunModel.setPosition(Posi_x - Direction, Posi_y - 5);
  rotate_Gun_By = ((static_cast<double>(atan(-dir_x/dir_y)) * 180)/3.14159265) + (dir_y > 0? 180:0) - 90;
  this->GunModel.setRotation(rotate_Gun_By);
  this->bulletGenPosi.x = GunModel.getPosition().x + ((MuzzelPoint.x) * dir_x * scaledown_sprite);
  this->bulletGenPosi.y = GunModel.getPosition().y + ((MuzzelPoint.x) * dir_y * scaledown_sprite) ;

}

void WEAPON::shotingOut(std::string Type, float dir_x, float dir_y, std::vector<BULLET*> &bullets)
{
  bool NormalShot = (Type.compare("Pistol") == 0 || Type.compare("Desert Eagle") == 0 || Type.compare("AK-47") == 0 || Type.compare("car-SMG") == 0 || Type.compare("Sniper Rifle") == 0 || Type.compare("NP-9") == 0);
  bool SplitShot = (Type.compare("Shotgun") == 0) || (Type.compare("Tactical Shotgun") == 0);
  bool gatlingShot = (Type.compare("Gatling Gun") == 0);
  bool snipershot = (Type.compare("Sniper Rifle") == 0);
  float speed = 250.f + (snipershot? 150: 0);
  if(NormalShot)
    bullets.push_back(new BULLET(this->bulletGenPosi.x, this->bulletGenPosi.y, dir_x, dir_y, this->Dealing_Damge, speed));
  else if(SplitShot)
    for(int i = -2; i < 3; i++)
    {
      double radius = 5 * i * 3.14159265/180;
      bullets.push_back(new BULLET(this->bulletGenPosi.x , this->bulletGenPosi.y, (dir_x * cos(radius) - dir_y * sin(radius)), sin(radius) * dir_x + cos(radius)*dir_y, this->Dealing_Damge, speed));
    }
  else if(gatlingShot)
  {
    gatlingCounter = gatlingState - 1;
    bullets.push_back(new BULLET(this->bulletGenPosi.x - gatlingCounter * 2, this->bulletGenPosi.y + gatlingCounter * ((dir_x < 0 && dir_y > 0) || (dir_y < 0 && dir_x > 0)? -2:2) + (dir_x>0?1:0), dir_x, dir_y, this->Dealing_Damge, speed));
    gatlingState = (gatlingState + 1)%3;
  }
}

void WEAPON::setGunType()
{
  GunType = 
  {
    {"Pistol", GunAttribute(4, 0, 0, 3, sf::Vector2f(7.f, -2.f), sf::Vector2f(4.f, 6.f), "../content/Gun/Sprite/Pistol.png")},
    {"Desert Eagle", GunAttribute(4, 1, 10, 2.7, sf::Vector2f(9.f, -2.f), sf::Vector2f(4.f, 6.f), "../content/Gun/Sprite/Desert_Eagle.png")},
    {"AK-47", GunAttribute(3, 1, 12, 6, sf::Vector2f(25.f, -5.f), sf::Vector2f(6.f, 9.f), "../content/Gun/Sprite/AK-47.png")},
    {"car-SMG", GunAttribute(2, 1, 5, 8, sf::Vector2f(19.f, -2.f), sf::Vector2f(10.f, 7.f), "../content/Gun/Sprite/car-SMG.png" )},
    {"NP-9", GunAttribute(2, 1, 5, 8, sf::Vector2f(15.f, -3.f), sf::Vector2f(8.f, 7.f), "../content/Gun/Sprite/NP9.png" )},
    {"Shotgun", GunAttribute(3, 3, 0, 1.2, sf::Vector2f(25.f, -5.f), sf::Vector2f(8.f, 8.f), "../content/Gun/Sprite/Shotgun.png")},
    {"Tactical Shotgun", GunAttribute(2, 2.5, 5, 2, sf::Vector2f(23.f, -3.f), sf::Vector2f(6.f, 8.f), "../content/Gun/Sprite/Tactical_Shotgun.png")},
    {"Gatling Gun", GunAttribute(2, 1, 0, 10, sf::Vector2f(29.f, 0.f), sf::Vector2f(8.f, 5.f), "../content/Gun/Sprite/Gatling_Gun.png")},
    {"Sniper Rifle", GunAttribute(16, 4, 45, 1.2, sf::Vector2f(35.f, -2.f), sf::Vector2f(15.f, 9.f), "../content/Gun/Sprite/Sniper_Rifle.png")}
  };
}