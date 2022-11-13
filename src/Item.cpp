#include <ITEM.h>
ITEM::ITEM(std::string Type,  float init_Posi_x, float init_Posi_y)
{
    std::map<std::string, struct PotionAttribute>::iterator it_potion;
    std::map<std::string, struct GunAttribute>::iterator it_gun;
    if(Type.compare("Potion") == 0)
    {
        setPotionAttribute();
        auto random_key = potionType.begin();
        std::advance(random_key, rand() % potionType.size());
        auto potion = random_key->first;
        it_potion = potionType.find(potion);
        this->texture.loadFromFile(it_potion->second.type);
    }
    else
    {
        setGunAttribute();
        auto random_key = gunType.begin();
        std::advance(random_key, rand() % gunType.size());
        auto gun = random_key->first;
        it_gun = gunType.find(gun);
        this->texture.loadFromFile(it_gun->second.type);
        this->ItemSprite.setScale(0.5, 0.5);
    }
    this->textureSize.x = this->texture.getSize().x;
    this->textureSize.y = this->texture.getSize().y;
    this->ItemSprite.setTexture(texture);
    this->ItemSprite.setOrigin(textureSize/2.f);
    this->ItemSprite.setPosition(sf::Vector2f(init_Posi_x, init_Posi_y));
}

void ITEM::setPotionAttribute()
{
    potionType =    {
                        {"HpPotion", PotionAttribute("../content/Potion/Health.png")},
                        {"EnergyPosion", PotionAttribute("../content/Potion/Energy.png")}
                    };
}
void ITEM::setGunAttribute()
{
    gunType =  {    
                    {"Pistol", GunAttribute("../content/Gun/Sprite/Pistol.png")},
                    {"Desert Eagle", GunAttribute("../content/Gun/Sprite/Desert_Eagle.png")},
                    {"AK-47", GunAttribute("../content/Gun/Sprite/AK-47.png")},
                    {"car-SMG", GunAttribute("../content/Gun/Sprite/car-SMG.png") },
                    {"NP-9", GunAttribute("../content/Gun/Sprite/NP9.png")},
                    {"Shotgun", GunAttribute("../content/Gun/Sprite/Shotgun.png")},
                    {"Tactical Shotgun", GunAttribute("../content/Gun/Sprite/Tactical_Shotgun.png")},
                    {"Gatling Gun", GunAttribute("../content/Gun/Sprite/Gatling_Gun.png")},
                    {"Sniper Rifle", GunAttribute("../content/Gun/Sprite/Sniper_Rifle.png")}
                };
}