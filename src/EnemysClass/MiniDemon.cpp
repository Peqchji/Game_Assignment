#include "ENEMY.h"
class MiniDemon: public ENEMY
{
    private:
        void init_Attribute();
        bool playerCheck(sf::Vector2f &playerPosi);
};
void MiniDemon::init_Attribute()
{
    this->Position = sf::Vector2f(0, 0);
    this->EnemyTexture.loadFromFile("");
    this->EnemySprite.setTexture(EnemyTexture);
    this->EnemySprite.setOrigin(EnemyTexture.getSize().x, EnemyTexture.getSize().y);
    Damage = 3;
    Health = 15;
    Speed = 40.f;
}

bool MiniDemon::playerCheck(sf::Vector2f &playerPosi)
{
    double distance;
    sf::Vector2f diff_Position;
    diff_Position =  playerPosi - Position;
    distance = sqrt(pow(diff_Position.x, 2) + pow(diff_Position.y, 2));
    if(distance <= ::CellPixelSize * 5)
        return true;

    return false;
}