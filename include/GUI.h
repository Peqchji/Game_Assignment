#ifndef GUI_H
#define GUI_H

#include "MASTER.h"

class GUI{
    public:
        sf::RenderTexture GUI_buffer;
        sf::Sprite currentGUI;

        GUI();
        void update(int &currentTool, sf::RectangleShape &player, float &setupPosi_x, float &setupPosi_y, float currentHP, float currentEnergy, float MaxHP, float MaxEnergy, float currentSheild, float currentCooldown, float MaxCooldown);
    private:
        sf::Texture frontHP;
        sf::Texture selector;
        sf::Texture frontEnergy;
        sf::Texture sheild;
        sf::Texture base;
        sf::Texture coolDownTexture;

        sf::Sprite baseGUI;
        sf::Sprite HPbar; 
        sf::Sprite Energybar;
        sf::Sprite SheildSprite;
        sf::Sprite _selector;
        sf::RectangleShape playerModel;
        sf::Sprite CoolDownStat;

        sftools::Chronometer Sel_CLK;
        sf::Time Sel_Timer;
        int currentSelState = 0;
        int LastHold = 0;
        bool isHandChange = false;
        int currentGun;

        float MAX_HP;
        float MAX_Energy;
        float AmountSheild;
        std::string holding;

        std::vector<sf::Sprite> showSheild;
        std::map<std::string, sf::Texture> holdingTexture;
        
        void setup_newGUI(float posi_x, float posi_y);
        void moveSel();
};

#endif