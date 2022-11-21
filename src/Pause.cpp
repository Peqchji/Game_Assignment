#include "PAUSE.h"
PAUSE::PAUSE(sf::Font &fontV1, sf::Font &fontV2)
{
    this->PauseBuffer.create(::ScreenWidth, ::ScreenHeight);
    this->FontLarge = fontV2;
    this->FontSmall = fontV1;
    this->InputSelTexture.loadFromFile("../content/GUI/InputSelected.png");

    this->Resume.setFont(this->FontLarge);
    this->Resume.setString("Resume");
    this->Resume.setCharacterSize(30.f);
    this->Resume.setFillColor(sf::Color::White);
    this->Resume.setOrigin(sf::Vector2f((Resume.getLocalBounds().left + Resume.getLocalBounds().width)/2.f, (Resume.getLocalBounds().top + Resume.getLocalBounds().height)/2.f));
    this->Resume.setPosition(520.f, 293.f);
    this->Resume.setOutlineColor(sf::Color::Black);
    this->Resume.setOutlineThickness(2.f);

    this->Exit.setFont(this->FontLarge);
    this->Exit.setString("Exit to Results");
    this->Exit.setCharacterSize(24.f);
    this->Exit.setFillColor(sf::Color::White);
    this->Exit.setOrigin(sf::Vector2f((Exit.getLocalBounds().left + Exit.getLocalBounds().width)/2.f, (Exit.getLocalBounds().top + Exit.getLocalBounds().height)/2.f));
    this->Exit.setPosition(520.f, 367.f);
    this->Exit.setOutlineColor(sf::Color::Black);
    this->Exit.setOutlineThickness(2.f);

    this->PauseText.setFont(this->FontLarge);
    this->PauseText.setString("==Pause==");
    this->PauseText.setCharacterSize(36.f);
    this->PauseText.setFillColor(sf::Color::White);
    this->PauseText.setOrigin(sf::Vector2f((PauseText.getLocalBounds().left + PauseText.getLocalBounds().width)/2.f, (PauseText.getLocalBounds().top + PauseText.getLocalBounds().height)/2.f));
    this->PauseText.setPosition(520.f, 219.f);
    this->PauseText.setOutlineColor(sf::Color::Black);
    this->PauseText.setOutlineThickness(2.f);
    

    this->Input_1.setSize((sf::Vector2f(192.f, 59.f)));
    this->Input_1.setOrigin((sf::Vector2f(192.f/2, 59.f/2)));
    this->Input_1.setFillColor(sf::Color::Transparent);
    this->Input_1.setPosition(520.f, 293.f);

    this->Input_2.setSize((sf::Vector2f(192.f, 59.f)));
    this->Input_2.setOrigin((sf::Vector2f(192.f/2, 59.f/2)));
    this->Input_2.setFillColor(sf::Color::Transparent);
    this->Input_2.setPosition(520.f, 367.f);

    this->InputSelected.setTexture(this->InputSelTexture);
    this->InputSelected.setOrigin(sf::Vector2f(this->InputSelTexture.getSize().x/2.f, this->InputSelTexture.getSize().y/2.f));
    this->InputSelected.setScale(192.f/46, 59.f/13);
    
    this->PauseBaseTexture.loadFromFile("../content/GUI/Pause.png");
    this->PauseBase.setTexture(this->PauseBaseTexture);
    this->PauseBase.setScale(sf::Vector2f(301.f/43, 304.f/44));
    this->PauseBase.setOrigin(sf::Vector2f(PauseBaseTexture.getSize().x/2.f, PauseBaseTexture.getSize().y/2.f));
    this->PauseBase.setPosition(::ScreenWidth/2.f , ::ScreenHeight/2.f);

    this->InputBlockTexture.loadFromFile("../content/GUI/InputBlock.png");
    for(int i = 0; i < 2; i++)
    {
        this->InputBlock[i].setTexture(this->InputBlockTexture);
        this->InputBlock[i].setPosition(sf::Vector2f(520.f, 293.f + (i * 74)));
        this->InputBlock[i].setOrigin(sf::Vector2f(this->InputSelTexture.getSize().x/2.f, this->InputSelTexture.getSize().y/2.f));
        this->InputBlock[i].setScale(192.f/46, 59.f/13);
    }
}
void PAUSE::update(float &InitPosi_x, float &InitPosi_y, float &mousePosi_x, float &mousePosi_y, bool &Toggle, int &RunningMode)
{
    if(isResumeSEL(mousePosi_x, mousePosi_y, Input_1) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        Toggle = true;
    }
    if(isResumeSEL(mousePosi_x, mousePosi_y, Input_2) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        RunningMode = 3;
    }
    setup_newPAUSE(InitPosi_x, InitPosi_y, mousePosi_x, mousePosi_y);
}
void PAUSE::setup_newPAUSE(float posi_x, float posi_y, float mouse_x, float mouse_y)
{
    this->PauseBuffer.clear(sf::Color{0, 0, 0, 127});
    this->PauseBuffer.draw(this->PauseBase);
    if(isResumeSEL(mouse_x, mouse_y, Input_1))
    {
        this->InputSelected.setPosition(sf::Vector2f(520.f, 293.f));
        this->PauseBuffer.draw(this->InputSelected);
    }
    else
    {
        this->PauseBuffer.draw(this->InputBlock[0]);
    }
    if(isResumeSEL(mouse_x, mouse_y, Input_2))
    {
        this->InputSelected.setPosition(sf::Vector2f(520.f, 366.f));
        this->PauseBuffer.draw(this->InputSelected);
    }
    else
    {
        this->PauseBuffer.draw(this->InputBlock[1]);
    }

    this->PauseBuffer.draw(this->Exit);
    this->PauseBuffer.draw(this->PauseText);
    this->PauseBuffer.draw(this->Resume);
    this->PauseBuffer.display();

    this->PauseSprite.setTexture(this->PauseBuffer.getTexture());
    this->PauseSprite.setOrigin(sf::Vector2f(::ScreenWidth/ 2.f, ::ScreenHeight/ 2.f));
    this->PauseSprite.setScale((1.f/ScaleUp), 1.f/ScaleUp);
    this->PauseSprite.setPosition(posi_x, posi_y);
}

bool PAUSE::isResumeSEL(float Posi_x, float Posi_y, sf::RectangleShape  &Container)
{
    bool results = false;
    if(Container.getGlobalBounds().contains(sf::Vector2f(Posi_x, Posi_y)))
    {
        results = true;
    }

    return results;
}

