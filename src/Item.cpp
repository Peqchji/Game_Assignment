#include <ITEM.h>
ITEM::ITEM(std::string Type,  float init_Posi_x, float init_Posi_y)
{

    if(Type.compare("Potion") == 0 || Type.compare("EnergyPotion") == 0 || Type.compare("HpPotion") == 0)
    {
        setPotionAttribute();
        if(Type.compare("Potion") == 0)
        {
            auto random_key = potionType.begin();
            std::advance(random_key, rand() % potionType.size());
            auto potion = random_key->first;
            it_potion = potionType.find(potion);
        }
        else
        {
            it_potion = potionType.find(Type);
        }
        this->texture.loadFromFile(it_potion->second.type);
        itemType = "Potion";
    }
    else
    {
        setGunAttribute();
        if(Type.compare("Gun") == 0)
        {
            auto random_key = gunType.begin();
            std::advance(random_key, rand() % gunType.size());
            auto gun = random_key->first;
            it_gun = gunType.find(gun);
        }
        else
        {
            it_gun = gunType.find(Type);
        }
        this->texture.loadFromFile(it_gun->second.type);
        this->ItemSprite.setScale(0.7, 0.7);
        itemType = "Gun";
    }
    this->textureSize.x = this->texture.getSize().x;
    this->textureSize.y = this->texture.getSize().y;
    this->ItemSprite.setTexture(texture);
    this->ItemSprite.setOrigin(textureSize/2.f);
    this->ItemSprite.setPosition(sf::Vector2f(init_Posi_x, init_Posi_y));
    this->pickupDelay.reset(true);
}
bool ITEM::isItemPickedUp(sf::RectangleShape &playerHitbox, float &currentPlayerHealth, float &currentPlayerEnergy, std::string &GunHolding)
{
    pickupDelayTimer = pickupDelay.getElapsedTime();
    if(playerHitbox.getGlobalBounds().intersects(ItemSprite.getGlobalBounds()) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && pickupDelayTimer.asMilliseconds() > 500)
    {
        if(itemType.compare("Potion") == 0)
        {
            if(it_potion->first.compare("HpPotion") == 0)
            {
                currentPlayerHealth += 4;
            }
            else
            {
                currentPlayerEnergy += 50;
            }
        }
        else
        {
            GunHolding = it_gun->first;
        }
        this->pickupDelay.reset(true);
        return true;
    }
    return false;
}
void ITEM::setPotionAttribute()
{
    potionType =    {
                        {"HpPotion", PotionAttribute("../content/Potion/Health.png")},
                        {"EnergyPotion", PotionAttribute("../content/Potion/Energy.png")}
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