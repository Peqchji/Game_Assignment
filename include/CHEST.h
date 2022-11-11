#ifndef CHEST_H
#define CHEST_H

#include <MASTER.h>
class CHEST
{
    public:
        sf::Sprite ChestSprite;
        CHEST();
        void update(float dt);
        void setupChest(float spawn_x, float spawn_y, float portal_x, float portal_y);
        bool isPlayerNearChest(sf::Vector2f playerPosi);
    private:
        sf::Texture Texture;
        sf::Vector2f TextureSize;
        
        sf::Clock AnimationCLK;
        sf::Time AnimationTimer;
        int currentAnimation;
};

#endif