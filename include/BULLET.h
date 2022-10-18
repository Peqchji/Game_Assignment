#include "MASTER.h"
class BULLET
{
    private:
        sf::Texture bulletTexture;
        
    public:
        sf::Sprite bulletShape;
        sf::Vector2f Direction;
        float BulletSpeed;
        BULLET();
        BULLET(float init_PosX, float init_PosY, float dir_x, float dir_y, float Speed);

        bool bulletCollision(std::vector<std::vector<sf::RectangleShape>> &WallHitbox, short currentRoom);
        void setBulletTexture();
        void update(float deltaTime);
        void render(sf::RenderWindow &target);
};