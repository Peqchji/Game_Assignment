#ifndef SFX_H
#define SFX_H
#include <MASTER.h>
class SFXClass{
    public:
        SFXClass();
        sf::Sound bulletWallhit;
        sf::Sound Chestopen;
        sf::Sound PortalActive;
        sf::Sound PickupItem;
    //player sfx
        sf::Sound sheildBlock;
        sf::Sound walking;
        sf::SoundBuffer walkingbuffer;
        sf::Sound takeDamage;
        sf::Sound castSkill;
    //Enemy sfx
        sf::Sound EnemyDeath;
        sf::Sound EnemyAlert;
        sf::Sound EnemyPain;

        sftools::Chronometer walking_CLK;
        sf::Time walking_Timer;
    private:
        sf::SoundBuffer bulletWallhitbuffer;
        sf::SoundBuffer Chestopenbuffer;
        sf::SoundBuffer PortalActiveBuffer;
        sf::SoundBuffer PickupItemBuffer;
    //player sfx
        sf::SoundBuffer sheildBlockbuffer;
        sf::SoundBuffer takeDamagebuffer;
        sf::SoundBuffer castSkillBuffer;
    //Enemy sfx
        sf::SoundBuffer EnemyDeathBuffer;
        sf::SoundBuffer EnemyAlertBuffer;
        sf::SoundBuffer EnemyPainBuffer;
};
#endif