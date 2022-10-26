#include "MASTER.h"
class BULLET
{
    private:
        sf::Texture bulletTexture;
        sf::Vector2f Direction;
        float BulletSpeed;
        double rotate_By;
    public:
        sf::Sprite bulletShape;
        BULLET(float init_PosX, float init_PosY, float dir_x, float dir_y, float Speed);

        bool bulletCollision(std::vector<std::vector<sf::RectangleShape>> &WallHitbox);
        void setBulletTexture();
        void update(float deltaTime);
};