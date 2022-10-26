#include "MASTER.h"
#include "BULLET.h"
class WEAPON
{
    public:
         struct GunAttribute
        {
            short Damage;
            float RoundPerSec;
            short EnergyCost;
            short CritChance;

            sf::Vector2f Muzzel;
            sf::Vector2f Holding;
            sf::Texture Texture;

            GunAttribute(short _Damage, short _EnergyCost, short _CritChance, short _RoundPerSec, sf::Vector2f _MuzzelPosi, sf::Vector2f _HoldingPosi, std::string _GunTexture)
            {
                Damage = _Damage;
                EnergyCost = _EnergyCost;
                CritChance =_CritChance;
                RoundPerSec = _RoundPerSec;
                Muzzel = _MuzzelPosi;
                Holding = _HoldingPosi;
                Texture.loadFromFile(_GunTexture);
            }
        };

        short Dealing_Damge;
        float FireRate;
        short Cost;
        short Crit;
        double rotate_Gun_By;

        float scaledown_sprite = 0.5;
        sf::Sprite GunModel;
        sf::Vector2f MuzzelPoint;
        sf::Vector2f bulletGenPosi;
        sf::Vector2f HoldingPosi;
        sf::Texture GunTexture;

        WEAPON();

        void init_Gun(float playerPosi_x, float playerPosi_y);
        void update(float Posi_x, float Posi_y, float dir_x, float dir_y);
        void ShotingOut(std::string type, float dir_x, float dir_y, std::vector<BULLET*> &bulletADDRs);
        
    private:
        std::map<std::string, struct GunAttribute> GunType;
        void setGunType();
        void shakeGun();
};