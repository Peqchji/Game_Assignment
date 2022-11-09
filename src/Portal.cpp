#include <Portal.h>
Portal::Portal()
{
    this->InTexture.loadFromFile("../content/map/PORTAL/Purple Portal Sprite Sheet.png");
    this->OutTexture.loadFromFile("../content/map/PORTAL/Green Portal Sprite Sheet.png");
    this->PortalIn.setTexture(InTexture);
    this->PortalOut.setTexture(OutTexture);
}

void Portal::update(float dt)
{

}