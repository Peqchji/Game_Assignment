#include "GUI.h"
GUI::GUI()
{
    this->GUI_buffer.create(::ScreenWidth/ScaleUp, ::ScreenHeight/ScaleUp);

    this->base.loadFromFile("../content/GUI/InGameGUI_Base.png");
    this->frontHP.loadFromFile("../content/GUI/HPstat.png");
    this->frontEnergy.loadFromFile("../content/GUI/Energystat.png");
    this->selector.loadFromFile("../content/GUI/Selector.png");
    this->sheild.loadFromFile("../content/GUI/Sheild.png");
    this->coolDownTexture.loadFromFile("../content/GUI/CoolDownStat.png");

    this->baseGUI.setTexture(this->base);
    this->baseGUI.setScale(sf::Vector2f(1.f/ScaleUp, 1.f/ScaleUp));

    this->HPbar.setTexture(this->frontHP);

    this->Energybar.setTexture(this->frontEnergy);

    this->_selector.setTexture(this->selector);
    this->_selector.scale(sf::Vector2f((25.f/6)/ScaleUp, (21.f/5)/ScaleUp));

    this->SheildSprite.setTexture(this->sheild);
    this->SheildSprite.setScale(sf::Vector2f(1.5f, 1.f));

    this->CoolDownStat.setTexture(coolDownTexture);

    this->CoolDownStat.setPosition(31.f/ScaleUp, 518.f/ScaleUp);
    this->HPbar.setPosition(110.f/ScaleUp, 5.f/ScaleUp);
    this->Energybar.setPosition(110.f/ScaleUp, 32.f/ScaleUp);
    this->_selector.setPosition(891.f/ScaleUp, 471.f/ScaleUp);

    Sel_CLK.reset(true);
}

void GUI::update(int &currentTool, sf::RectangleShape &player, float &setupPosi_x, float &setupPosi_y, float currentHP, float currentEnergy, float MaxHP, float MaxEnergy, float currentSheild, float currentCooldown, float MaxCooldown)
{
    AmountSheild = currentSheild;
    playerModel = player;
    currentGun = currentTool;
    float progess_bar_x = (204.f/50)/ScaleUp;
    float progess_bar_y = (13.f/3)/ScaleUp;
    float cooldown_bar_x = (166.f/40)/ScaleUp;
    float cooldown_bar_y = (41.f/10)/ScaleUp;
    
    //moveSel();
    this->HPbar.setScale(currentHP/MaxHP * progess_bar_x, progess_bar_y);
    this->Energybar.setScale(currentEnergy/MaxEnergy * progess_bar_x, progess_bar_y);
    this->CoolDownStat.setScale(currentCooldown/MaxCooldown * cooldown_bar_x, cooldown_bar_y);

    if(AmountSheild > 0)
    {
        showSheild.clear();
        for(int i = 0; i < AmountSheild; i++)
        { 
             this->SheildSprite.setPosition(sf::Vector2f((15 + i * sheild.getSize().x * 4 * 1.5f)/ScaleUp, 99/ScaleUp));
            showSheild.push_back(this->SheildSprite);
        }
    }
    this->playerModel.setPosition(sf::Vector2f(108/(2.f*ScaleUp), 96/(2.f*ScaleUp)));

    setup_newGUI(setupPosi_x, setupPosi_y);
}

void GUI::setup_newGUI(float posi_x, float posi_y)
{
    this->GUI_buffer.clear(sf::Color::Transparent);

    this->GUI_buffer.draw(this->baseGUI);
    this->GUI_buffer.draw(this->HPbar);
    this->GUI_buffer.draw(this->Energybar);
    this->GUI_buffer.draw(this->_selector);
     if(AmountSheild > 0)
    {
        for(int i = 0; i < AmountSheild; i++)
        { 
             this->GUI_buffer.draw(showSheild[i]);
        }
    }
    this->GUI_buffer.draw(this->CoolDownStat);
    this->GUI_buffer.draw(this->playerModel);


    this->GUI_buffer.display();

    this->currentGUI.setTexture(this->GUI_buffer.getTexture());
    this->currentGUI.setOrigin(sf::Vector2f(::ScreenWidth/(ScaleUp * 2.f), ::ScreenHeight/(ScaleUp * 2.f)));
    this->currentGUI.setPosition(posi_x, posi_y);
}

void GUI::moveSel()
{
    Sel_Timer = Sel_CLK.getElapsedTime();
    if(LastHold != currentGun)
    {
        isHandChange = true;
    }
    if(Sel_Timer.asMilliseconds() >= 250 && currentSelState < 3)
    {
        currentSelState++;
    }
    LastHold = currentGun;
}