#ifndef CAL_RESULTS_H
#define CAL_RESULTS_H

#include<MASTER.h>

class RESULTS{
    public:
        sf::RenderTexture CAL_SCOREbuffer;
        sf::Sprite currentCAL_SCORE;

        int currentAnimation = 0;
        void sorting(std::string &Name, unsigned int &playerScore);
        void update(float &InitPosi_x, float &InitPosi_y, float &mousePosi_x, float &mousePosi_y, bool &Toggle, bool &Running, int currentScore);
        
        RESULTS(sf::Font &fontV1, sf::Font &fontV2);
    private:
        sf::Font FontSmall;
        sf::Font FontLarge;

        sf::Texture InputBlockTexture;
        sf::Sprite InputBlock;
        sf::RectangleShape clickPlayBox;
        sf::Texture InputSelTexture;
        sf::Sprite InputSelected;
        sf::Text Inputplay;

        sf::Clock AnimationCLK;
        sf::Time AnimationTimer;

        std::vector<std::pair<std::string, unsigned int>> PlayerInfo;
        int scoreInfo[5];
        char playerNameInfo[5][16];
        sf::Text scoreInfoText[5];

        sf::Text GAMEOVER;
        sf::Text yourScore;

        void file_LeaderBoardReader();
        void setup_newProgessScene(float posi_x, float posi_y, float mouse_x, float mouse_y);
        bool isSELECT(float Posi_x, float Posi_y, sf::RectangleShape  &Container);
};

#endif