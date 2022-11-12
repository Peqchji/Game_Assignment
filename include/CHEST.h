#ifndef CHEST_H
#define CHEST_H

#include <MASTER.h>
class CHEST
{
    public:
        sf::Sprite ChestSprite;
        CHEST(float SpawnPos_x, float SpawnPos_y);
        void update(sf::Vector2f playerPosi);
        bool isPlayerOpenChest(sf::Vector2f playerPosi);
    private:
        sf::Texture Texture;
        sf::Vector2f TextureSize;
        
        sf::Clock AnimationCLK;
        sf::Time AnimationTimer;
        int currentAnimation;
        
        void setupChest(float spawn_x, float spawn_y);
};

#endif