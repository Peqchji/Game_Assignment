#include "SFX.h"
SFXClass::SFXClass()
{
    this->bulletWallhitbuffer.loadFromFile("../content/Gun/SFX/concrete_impact_bullet2.wav");
    this->bulletWallhit.setBuffer(this->bulletWallhitbuffer);
    this->bulletWallhit.setVolume(10.f);

    this->Chestopenbuffer.loadFromFile("../content/map/ChestOpen.wav");
    this->Chestopen.setBuffer(this->Chestopenbuffer);
    this->Chestopen.setVolume(50.f);

    this->PortalActiveBuffer.loadFromFile("../content/map/PORTAL/SFX/churchbell_end.wav");
    this->PortalActive.setBuffer(this->PortalActiveBuffer);
    this->PortalActive.setVolume(30.f);

    this->PickupItemBuffer.loadFromFile("../content/Potion/pickUpItem.wav");
    this->PickupItem.setBuffer(this->PickupItemBuffer);
    this->PickupItem.setVolume(80.f);

    this->walking_CLK.reset(true);
    this->sheildBlockbuffer.loadFromFile("../content/Sprite/SFX/player/SheildBlock.wav");
	this->walkingbuffer.loadFromFile("../content/Sprite/SFX/player/Walking.wav");
	this->takeDamagebuffer.loadFromFile("../content/Sprite/SFX/player/Hitted.wav");
	this->castSkillBuffer.loadFromFile("../content/Sprite/SFX/player/Skillcast.wav");
	this->sheildBlock.setBuffer(this->sheildBlockbuffer);
    this->walking.setBuffer(this->walkingbuffer);
    this->takeDamage.setBuffer(this->takeDamagebuffer);
	this->castSkill.setBuffer(this->castSkillBuffer);

    this->EnemyDeathBuffer.loadFromFile("../content/Sprite/SFX/Enemy/alert_02.wav");
    this->EnemyDeath.setBuffer(this->EnemyDeathBuffer);
    this->EnemyDeath.setVolume(20.f);

    this->EnemyAlertBuffer.loadFromFile("../content/Sprite/SFX/Enemy/alert_02.wav");
    this->EnemyAlert.setBuffer(this->EnemyAlertBuffer);
    this->EnemyAlert.setVolume(20.f);

    this->EnemyPainBuffer.loadFromFile("../content/Sprite/SFX/Enemy/painshort_03.wav");
    this->EnemyPain.setBuffer(this->EnemyPainBuffer);
    this->EnemyPain.setVolume(20.f);
}