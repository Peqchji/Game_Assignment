#ifndef MENU_H
#define MENU_H

#include<MASTER.h>
class MENU{
    public:
                sf::RenderTexture MenuBuffer;
                sf::Sprite MenuSprite;

                MENU(sf::Font &fontV1, sf::Font &fontV2);
                void update(float &InitPosi_x, float &InitPosi_y, float &mousePosi_x, float &mousePosi_y, bool &Toggle, bool &Running);
        private:
                sf::Font FontSmall;
                sf::Font FontLarge;
                sf::Text Leaderboard;
                sf::Text Exit;
                sf::Text Start;

                sf::Sprite PauseBase;
                sf::Texture PauseBaseTexture;

                sf::RectangleShape Input_1;
                sf::RectangleShape Input_2;
                sf::RectangleShape Input_3;
                

                sf::Sprite InputSelected;
                sf::Texture InputSelTexture;

                sf::Sprite InputBlock[3];
                sf::Texture InputBlockTexture;


                void setup_newPAUSE(float posi_x, float posi_y, float mouse_x, float mouse_y);
                bool isResumeSEL(float Posi_x, float Posi_y, sf::RectangleShape  &Container);
};

#endif