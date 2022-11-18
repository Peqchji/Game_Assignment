#include <CHEST.h>

CHEST::CHEST(float SpawnPos_x, float SpawnPos_y)
{
    this->Texture.loadFromFile("../content/map/Chest.png");
    this->ChestSprite.setTexture(Texture);

    this->TextureSize.x = this->Texture.getSize().x /3.f;
    this->TextureSize.y = this->Texture.getSize().y;
    this->ChestSprite.setOrigin(sf::Vector2f(TextureSize.x/2.f, TextureSize.y/2.f));
    this->ChestSprite.setTextureRect(sf::IntRect(0, 0, TextureSize.x, TextureSize.y));
    currentAnimation = 0;

    SpawnItem = false;
    this->AnimationCLK.reset(true);
    setupChest(SpawnPos_x, SpawnPos_y);
}

void CHEST::update(sf::Vector2f playerPosi)
{
    AnimationTimer = AnimationCLK.getElapsedTime();
    if(isPlayerOpenChest(playerPosi) && currentAnimation == 0 )
    {
        AnimationCLK.reset(true);
        currentAnimation = 1;
    }
    else if(currentAnimation == 1 && AnimationTimer.asMilliseconds() >= 250)
    {
        currentAnimation = 2;
        SpawnItem = true;
    }
    this->ChestSprite.setTextureRect(sf::IntRect(TextureSize.x * currentAnimation, 0, TextureSize.x, TextureSize.y));
}

void CHEST::setupChest(float spawn_x, float spawn_y)
{
    this->ChestSprite.setPosition(spawn_x, spawn_y);
}

bool CHEST::isPlayerOpenChest(sf::Vector2f playerPosi)
{
    sf::Vector2f diffPosi = playerPosi - this->ChestSprite.getPosition();
    float distance = static_cast<float>(sqrt(pow(diffPosi.x, 2) + pow(diffPosi.y, 2)));
    // สมการวงรี
    // a = 1
    // b = 1.5
    if(distance <= ::CellPixelSize && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        return true;
    }
    return false;
}

void CHEST::ToggleCLK()
{
    AnimationCLK.toggle();
}