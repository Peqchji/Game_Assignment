#ifndef ITEM_H
#define ITEM_H

#include <MASTER.h>
class ITEM{
    public:
        sf::Sprite ItemSprite;
        ITEM(std::string Type, float init_Posi_x, float init_Posi_y);
        bool isItemPickedUp();
    private:
        struct PotionAttribute
        {
            std::string type;
            PotionAttribute(std::string _type)
            {
                type = _type;
            }
        };
        struct GunAttribute
        {
            std::string type;
            GunAttribute(std::string _type)
            {
                type = _type;
            }
        };
        std::map<std::string, struct PotionAttribute> potionType;
        std::map<std::string, struct GunAttribute> gunType;

        sf::Texture texture;
        sf::Vector2f textureSize;
        void setPotionAttribute();
        void setGunAttribute();
};
#endif