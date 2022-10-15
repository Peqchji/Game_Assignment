#include "MASTER.h"
class BULLET
{
    private:
        sf::Sprite bulletShape;
        sf::Texture* bulletTexture;

        sf::Vector2f Direction;
        float BulletSpeed;
    public:
        BULLET(sf::Texture &Texture, float dir_x, float dir_y, float Speed);
        virtual ~BULLET();

        void update();
        void render(sf::RenderTarget* target);
};