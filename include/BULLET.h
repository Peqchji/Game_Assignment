#include "MASTER.h"
class BULLET
{
    private:
        sf::CircleShape bulletShape;
        sf::Texture* bulletTexture;

        sf::Vector2f Direction;

        float BulletSpeed;
    public:
        BULLET(float init_PosX, float init_PosY, float dir_x, float dir_y, float Speed);
        ~BULLET();
        
        void update();
        void render(sf::RenderTarget* target);
};