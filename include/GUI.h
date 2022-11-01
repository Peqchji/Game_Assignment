#ifndef GUI_H
#define GUI_H

#include "MASTER.h"

class GUI{
    public:
        sf::RenderTexture GUI_buffer;
        sf::Sprite currentGUI;

        GUI();
        void update(float &setupPosi_x, float &setupPosi_y, float currentHP, float currentEnergy, float MaxHP, float MaxEnergy, float currentCrit);
    private:
        sf::Texture frontHP;
        sf::Texture selector;
        sf::Texture frontEnergy;
        sf::Texture base;

        sf::Sprite baseGUI;
        sf::Sprite HPbar; 
        sf::Sprite Energybar;
        sf::Sprite _selector;

        void setup_newGUI(float posi_x, float posi_y);
        float MAX_HP;
        float MAX_Energy;
        std::string holding;

        std::map<std::string, sf::Texture> holdingTexture;
};

#endif