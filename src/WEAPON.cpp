#include "WEAPON.h"
WEAPON::WEAPON()
{
    setGunType();
}
void WEAPON::init_Gun(std::string &Type, float playerPosi_x, float playerPosi_y)
{
  std::map<std::string, struct GunAttribute>::iterator it;
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

    GunModel.setOrigin(this->HoldingPosi);
    GunModel.setScale(scaledown_sprite, scaledown_sprite);
    GunModel.setPosition(playerPosi_x, playerPosi_y);
  }
}
void WEAPON::update(float Posi_x, float Posi_y, float dir_x, float dir_y)
{
   short Direction = (dir_x > 0? 1: -1);
    this->GunModel.setPosition(Posi_x - Direction, Posi_y - (dir_x > 0? 6:5));
    this->GunModel.setTextureRect(sf::IntRect(0, (dir_x > 0? 0: 1) * GunTexture.getSize().y, GunTexture.getSize().x, Direction * GunTexture.getSize().y));
    rotate_Gun_By = ((static_cast<double>(atan(-dir_x/dir_y)) * 180)/3.141592654) + (dir_y > 0? 180:0) - 90;
    this->GunModel.setRotation(rotate_Gun_By);
    this->bulletGenPosi.x = GunModel.getPosition().x + (MuzzelPoint.x * dir_x * scaledown_sprite);
    this->bulletGenPosi.y = GunModel.getPosition().y + (MuzzelPoint.x * dir_y * scaledown_sprite);
}

void WEAPON::shotingOut(std::string &Type, float dir_x, float dir_y, std::vector<BULLET*> &bullets)
{
  bool NormalShot = (Type.compare("Pistol") == 0 || Type.compare("Desert Eagle") == 0 || Type.compare("AK-47") == 0);
  bool SplitShot = (Type.compare("Shotgun") == 0);
  if(NormalShot)
    bullets.push_back(new BULLET(this->bulletGenPosi.x, this->bulletGenPosi.y, dir_x, dir_y, 350.f));
  else if(SplitShot)
    for(int i = -2; i < 3; i++)
    {
      bullets.push_back(new BULLET(this->bulletGenPosi.x + i*3, this->bulletGenPosi.y - i*((dir_x < 0 && dir_y > 0) || (dir_y < 0 && dir_x > 0)? -3:3), dir_x, dir_y, 350.f - abs(i)*25));
    }
}

void WEAPON::setGunType()
{
    GunType = 
  {
    {"Pistol", GunAttribute(4, 0, 0, 3, sf::Vector2f(7.f, -4.f), sf::Vector2f(4.f, 6.f), "../content/Pistol.png")},
    {"Desert Eagle", GunAttribute(4, 1, 10, 2.7, sf::Vector2f(7.f, -1.f), sf::Vector2f(6.f, 4.f), "../content/Desert_Eagle.png")},
    {"AK-47", GunAttribute(3, 1, 12, 6, sf::Vector2f(25.f, -5.f), sf::Vector2f(6.f, 9.f), "../content/AK-47.png")},
    //{"Assault Rifle Elite", GunAttribute(2, 1, 5, 8, , )},
    {"Shotgun", GunAttribute(3, 3, 0, 1.2, sf::Vector2f(25.f, -6.f), sf::Vector2f(8.f, 8.f), "../content/Shotgun.png")},
    //{"Tactical Shotgun", GunAttribute(12, 3, 5, 2, , )},
    //{"Gatling Gun", GunAttribute(2, 2, 0, 10, , )}*/
  };
}