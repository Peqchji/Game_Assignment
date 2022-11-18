#ifndef GUI_H
#define GUI_H

#include "MASTER.h"

class GUI{
    public:
        sf::RenderTexture GUI_buffer;
        sf::Sprite currentGUI;

        GUI(sf::Font &fontV1, sf::Font &fontV2);
        void update(int &currentTool, sf::Texture &Gun_no1, sf::Texture &Gun_no2, sf::RectangleShape &player, float score, float &setupPosi_x, float &setupPosi_y, float currentHP, float currentEnergy, float MaxHP, float MaxEnergy, float currentSheild, std::string &SkillName, float currentCooldown, float MaxCooldown);
        void isPauseButtonPressed(float &mouse_x, float &mouse_y, bool &Toggle);
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
        sf::Sprite Gun_1;
        sf::Sprite Gun_2;

        sf::Sprite PauseButtonSprite;
        sf::Texture PauseButton;

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

        sf::Text SkillText;
        sf::Text HealthText;
        sf::Text EnergyText;
        sf::Text ScoreText;

        sf::Font font1;
        sf::Font font2;
        
        void setup_newGUI(float posi_x, float posi_y);
        void moveSel();

};

#endif