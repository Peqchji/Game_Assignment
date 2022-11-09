#ifndef PORTAL_H
#define PORTAL_H
#include <MASTER.h>


class Portal
{
    public:
        sf::Sprite PortalIn;
        sf::Sprite PortalOut;

        Portal();
        void update(float dt);
    private:
        sf::Texture InTexture;
        sf::Texture OutTexture;
        sf::Vector2f TextureSize;


};

#endif