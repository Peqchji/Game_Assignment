#ifndef MENU_H
#define MENU_H

#include <MASTER.h>
class MENU{
    public:
                sf::RenderTexture MenuBuffer;
                sf::Sprite MenuSprite;
                int ClassSEL = 0;
                std::string playerNameContrainer = "";

                MENU(sf::Font &fontV1, sf::Font &fontV2);
                void update(float &InitPosi_x, float &InitPosi_y, float &mousePosi_x, float &mousePosi_y, bool &Running, bool &StartGame, int &MenuState);
        private:
                sf::Font FontSmall;
                sf::Font FontLarge;
                sf::Text Leaderboard;
                sf::Text Exit;
                sf::Text Start;
                sf::Text Name;
                sf::Text GameName;
                sf::Text EnterName;


                sf::RectangleShape Input_1;
                sf::RectangleShape Input_2;
                sf::RectangleShape Input_3;

                sf::RectangleShape classSEL_1;
                sf::RectangleShape classSEL_2;
                sf::RectangleShape classSEL_3;
                sf::Text PlayerAttri_1;
                sf::Text PlayerAttri_2;
                sf::Text PlayerAttri_3;

                sf::Texture playerNameTexture;
                sf::Sprite playerNameBox;
                sf::Text playerName;


                sf::Text ChooseNplay;
                
                sf::Text goBack;
                sf::Sprite goBackBlock;
                sf::Sprite goBackSel;
                sf::RectangleShape goBackBox;

                sf::Sprite ChooseNplayBlock;
                sf::Texture ChooseNplayBlockTexture;
                sf::RectangleShape clickPlayBox;

                sf::Sprite ChooseNplaySelected;
                sf::Texture ChooseNplaySelTexture;


                sf::Sprite MenuBase;
                sf::Texture MenuBaseTexture;

                sf::RectangleShape knight;
                sf::RectangleShape rogue;
                sf::RectangleShape priest;

                sf::Texture knightTexture;
                sf::Texture rogueTexture;
                sf::Texture priestTexture;

                sf::Sprite ChestSprite;
                sf::Texture Chest;

                void setup_newMENU(float posi_x, float posi_y, float mousePosi_x, float mousePosi_y, int State);
                bool isSELECT(float Posi_x, float Posi_y, sf::RectangleShape  &Container);
                void file_LeaderBoardReader();

                int scoreInfo[5];
                sf::Text scoreInfoText[5];
                char playerNameInfo[5][16];
                bool firstTimeRead = true;
};

#endif