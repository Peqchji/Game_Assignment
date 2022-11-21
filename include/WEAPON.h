#ifndef WEAPON_H
#define WEAPON_H

#include "MASTER.h"
#include "BULLET.h"
class WEAPON
{
    public:
         struct GunAttribute
        {
            float Damage;
            float RoundPerSec;
            short EnergyCost;
            short CritChance;

            sf::Vector2f Muzzel;
            sf::Vector2f Holding;
            sf::Texture Texture;
            sf::SoundBuffer sound;

            GunAttribute(float _Damage, short _EnergyCost, short _CritChance, short _RoundPerSec, sf::Vector2f _MuzzelPosi, sf::Vector2f _HoldingPosi, std::string _GunTexture, std::string _sound)
            {
                Damage = _Damage;
                EnergyCost = _EnergyCost;
                CritChance =_CritChance;
                RoundPerSec = _RoundPerSec;
                Muzzel = _MuzzelPosi;
                Holding = _HoldingPosi;
                Texture.loadFromFile(_GunTexture);
                sound.loadFromFile(_sound);
            }
        };

        float Dealing_Damge;
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

        void init_Gun(std::string Type, float playerPosi_x, float playerPosi_y);
        void shotingOut(std::string Type, float dir_x, float dir_y, std::vector<BULLET*> &bullets);
        void update(float Posi_x, float Posi_y, float dir_x, float dir_y);
        
        std::map<std::string, struct GunAttribute> GunType;
        std::map<std::string, struct GunAttribute>::iterator it;
    private:

        sf::SoundBuffer shootingBuffer;
        sf::Sound shooting;
        void setGunType();
        int gatlingState = 0;
        int gatlingCounter;

};
#endif