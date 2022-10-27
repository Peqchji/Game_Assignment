#include "WEAPON.h"
WEAPON::WEAPON()
{
    setGunType();
}
void WEAPON::init_Gun(float playerPosi_x, float playerPosi_y)
{
  std::map<std::string, struct GunAttribute>::iterator it;
  it = GunType.find("Pistol");
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

    GunModel.setOrigin(this->HoldingPosi);
    GunModel.setScale(scaledown_sprite, scaledown_sprite);
    GunModel.setPosition(playerPosi_x, playerPosi_y);
  }
}
void WEAPON::update(float Posi_x, float Posi_y, float dir_x, float dir_y)
{
   std::map<std::string, struct GunAttribute>::iterator it;
   short Direction = (dir_x > 0? 1: -1);
    this->GunModel.setPosition(Posi_x - Direction, Posi_y - (dir_x > 0? 6:5));
    this->GunModel.setTextureRect(sf::IntRect(0, (dir_x > 0? 0: 1) * GunTexture.getSize().y, GunTexture.getSize().x, Direction * GunTexture.getSize().y));
    rotate_Gun_By = ((static_cast<double>(atan(-dir_x/dir_y)) * 180)/3.141592654) + (dir_y > 0? 180:0) - 90;
    this->GunModel.setRotation(rotate_Gun_By);
    this->bulletGenPosi.x = GunModel.getPosition().x + (MuzzelPoint.x * dir_x);
    this->bulletGenPosi.y = GunModel.getPosition().y + (MuzzelPoint.x * dir_y);
}

void WEAPON::setGunType()
{
    GunType = 
  {
      {"Pistol", GunAttribute(4, 0, 0, 3, sf::Vector2f(7.f,-4.f), sf::Vector2f(4.f, 6.f), "../content/Pistol.png")},
    //{"Desert Eagle", GunAttribute(4, 1, 10, 2.7, sf::Vector2f(12.f, 3.f), sf::Vector2f(6.f, 4.f))},
    //{"AK-47", GunAttribute(3, 1, 12, 6, sf::Vector2f(30.f, 4.f), sf::Vector2f(6.f, 9.f))},
    /*{"Assault Rifle Elite", GunAttribute(2, 1, 5, 8, , )},
    {"Shotgun", GunAttribute(15, 3, 0, 1.2, , )},
    {"Tactical Shotgun", GunAttribute(12, 3, 5, 2, , )},
    {"Gatling Gun", GunAttribute(2, 2, 0, 10, , )}*/
  };
}