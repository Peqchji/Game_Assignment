#include "WEAPON.h"
WEAPON::WEAPON()
{
    setGunType();
}
void WEAPON::init_Gun(float playerPosi_x, float playerPosi_y)
{
  std::map<std::string, struct GunAttribute>::iterator it;
  it = GunType.find("Shotgun");
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
   short Direction = (dir_x > 0? 1: -1);
    this->GunModel.setPosition(Posi_x, Posi_y - (dir_x > 0? 6:4));
    this->GunModel.setTextureRect(sf::IntRect(0, (dir_x > 0? 0: 1) * (GunTexture.getSize().y), GunTexture.getSize().x, Direction * GunTexture.getSize().y));
    rotate_Gun_By = ((static_cast<double>(atan(-dir_x/dir_y)) * 180)/3.141592654) + (dir_y > 0? 180:0) - 90;
    this->GunModel.setRotation(rotate_Gun_By);
    this->bulletGenPosi.x = GunModel.getPosition().x + (this->MuzzelPoint.x * dir_x * scaledown_sprite);
    this->bulletGenPosi.y = GunModel.getPosition().y + (this->MuzzelPoint.x * dir_y * scaledown_sprite);
}

void WEAPON::ShotingOut(std::string type, float dir_x, float dir_y, std::vector<BULLET*> &bulletADDRs)
{
  int j = 0;
  if (type == "Pistol" || type == "Desert Eagle" || type == "AK-47" || type == "Assault Rifle Elite")
  {
     bulletADDRs.push_back(new BULLET(this->bulletGenPosi.x, this->bulletGenPosi.y, dir_x, dir_y, 350.f));
  }
  else if(type == "Shotgun" || type == "Tactical Shotgun")
  {
    for(j = -2; j < 3; j++)
    {
      bulletADDRs.push_back(new BULLET(this->bulletGenPosi.x + (j * 3), this->bulletGenPosi.y - (j * 3), dir_x, dir_y, 350.f - abs(j) * 10));
    }
  }
}

void WEAPON::setGunType()
{
    GunType = 
  {
    {"Knife", GunAttribute(4, 0, 0, 2, sf::Vector2f( 7.f, -4.f), sf::Vector2f(4.f, 6.f), "../content/Knife.png")},
    {"Pistol", GunAttribute(4, 0, 0, 3, sf::Vector2f( 7.f, -4.f), sf::Vector2f(4.f, 6.f), "../content/Pistol.png")},
    //{"Desert Eagle", GunAttribute(4, 1, 10, 2.7, sf::Vector2f(12.f, 3.f), sf::Vector2f(6.f, 4.f))},
    //{"AK-47", GunAttribute(3, 1, 12, 6, sf::Vector2f(30.f, 4.f), sf::Vector2f(6.f, 9.f))},
    //{"Assault Rifle Elite", GunAttribute(2, 1, 5, 8, , )},
    {"Shotgun", GunAttribute(3, 3, 0, 1.2, sf::Vector2f( 25.f, -6.f), sf::Vector2f(8.f, 8.f), "../content/Shotgun.png")},
    /*{"Tactical Shotgun", GunAttribute(12, 3, 5, 2, , )},
    {"Gatling Gun", GunAttribute(2, 2, 0, 10, , )}*/
  };
}