#include <Portal.h>
Portal:: Portal()
{
    this->InTexture.loadFromFile("../content/map/PORTAL/Purple Portal Sprite Sheet.png");
    this->OutTexture.loadFromFile("../content/map/PORTAL/Green Portal Sprite Sheet.png");
    this->PortalIn.setTexture(InTexture);
    this->PortalOut.setTexture(OutTexture);
    this->TextureSize.x = InTexture.getSize().x / 8;
    this->TextureSize.y = InTexture.getSize().y / 3;

    this->PortalIn.setScale(1.5, 1);
    this->PortalOut.setScale(1.5, 1);

    this->PortalIn.setOrigin(sf::Vector2f(TextureSize.x/2.f, TextureSize.y/2.f));
    this->PortalOut.setOrigin(sf::Vector2f(TextureSize.x/2.f, TextureSize.y/2.f));
    currentAnimation = 0;

    this->AnimationCLK.reset(true);
}

void Portal::update(float dt)
{
    this->AnimationTimer = this->AnimationCLK.getElapsedTime();
    if(this->AnimationTimer.asMilliseconds() > 94)
    {
        this->PortalOut.setTextureRect(sf::IntRect( TextureSize.x * currentAnimation, 0, TextureSize.x, TextureSize.y));
        this->PortalIn.setTextureRect(sf::IntRect( TextureSize.x * currentAnimation, 0, TextureSize.x, TextureSize.y));
        currentAnimation = (currentAnimation + 1) % 8;
        this->AnimationCLK.reset(true);
    }
}

void Portal::setupPortal(float spawn_x, float spawn_y, float portal_x, float portal_y)
{
    this->PortalIn.setPosition(sf::Vector2f(::GridPixelSize * spawn_x + ::CellPixelSize * 16.5, ::GridPixelSize * spawn_y + ::CellPixelSize * 15.5));
    this->PortalOut.setPosition(sf::Vector2f(::GridPixelSize * portal_x + ::CellPixelSize * 16.5, ::GridPixelSize * portal_y + ::CellPixelSize * 15.5));
}

bool Portal::isPlayerNearPortalOut(sf::Vector2f playerPosi)
{
    sf::Vector2f diffPosi = playerPosi - PortalOut.getPosition();
    float distance = static_cast<float>(sqrt(pow(diffPosi.x, 2) + pow(diffPosi.y, 2)/pow(1.5, 2)));
    // สมการวงรี
    // a = 1
    // b = 1.5
    if(distance <= ::CellPixelSize && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        return true;
    }
    return false;
}

void Portal::ToggleCLK()
{
    AnimationCLK.toggle();
}