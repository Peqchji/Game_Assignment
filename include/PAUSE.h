#ifndef PAUSE_H
#define PAUSE_H

#include "MASTER.h"
class PAUSE{
        public:
                sf::RenderTexture PauseBuffer;
                sf::Sprite PauseSprite;

                PAUSE(sf::Font &fontV1, sf::Font &fontV2);
                void update(float &InitPosi_x, float &InitPosi_y, float &mousePosi_x, float &mousePosi_y, bool &Toggle, int &RunningMode);
        private:
                sf::Font FontSmall;
                sf::Font FontLarge;
                sf::Text Resume;
                sf::Text Exit;
                sf::Text PauseText;

                sf::Sprite PauseBase;
                sf::Texture PauseBaseTexture;

                sf::RectangleShape Input_1;
                sf::RectangleShape Input_2;

                sf::Sprite InputSelected;
                sf::Texture InputSelTexture;

                sf::Sprite InputBlock[2];
                sf::Texture InputBlockTexture;

                void setup_newPAUSE(float posi_x, float posi_y, float mouse_x, float mouse_y);
                bool isResumeSEL(float Posi_x, float Posi_y, sf::RectangleShape  &Container);
};
#endif