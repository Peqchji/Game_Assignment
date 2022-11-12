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
        void setupPortal(float spawn_x, float spawn_y, float portal_x, float portal_y);

        bool isPlayerNearPortalOut(sf::Vector2f playerPosi);
    private:
        sf::Texture InTexture;
        sf::Texture OutTexture;
        sf::Vector2f TextureSize;
        
        sf::Clock AnimationCLK;
        sf::Time AnimationTimer;
        int currentAnimation;


};

#endif