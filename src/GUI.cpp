#include "GUI.h"
GUI::GUI()
{
    this->GUI_buffer.create(::ScreenWidth/ScaleUp, ::ScreenHeight/ScaleUp);

    this->base.loadFromFile("../content/GUI/InGameGUI_Base.png");
    this->frontHP.loadFromFile("../content/GUI/HPstat.png");
    this->frontEnergy.loadFromFile("../content/GUI/Energystat.png");
    this->selector.loadFromFile("../content/GUI/Selector.png");

    this->baseGUI.setTexture(this->base);
    this->baseGUI.setScale(sf::Vector2f(1.f/ScaleUp, 1.f/ScaleUp));

    this->HPbar.setTexture(this->frontHP);
    this->HPbar.scale(sf::Vector2f((204.f/50)/ScaleUp, (13.f/3)/ScaleUp));

    this->Energybar.setTexture(this->frontEnergy);
    this->Energybar.scale(sf::Vector2f((204.f/50)/ScaleUp, (13.f/3)/ScaleUp));

    this->_selector.setTexture(this->selector);
    this->_selector.scale(sf::Vector2f((25.f/6)/ScaleUp, (21.f/5)/ScaleUp));

    this->HPbar.setPosition(110.f/ScaleUp, 5.f/ScaleUp);
    this->Energybar.setPosition(110.f/ScaleUp, 32.f/ScaleUp);
    this->_selector.setPosition(891.f/ScaleUp, 471.f/ScaleUp);


}

void GUI::update(float &setupPosi_x, float &setupPosi_y, float currentHP, float currentEnergy, float MaxHP, float MaxEnergy, float currentCrit)
{

    setup_newGUI(setupPosi_x, setupPosi_y);
}

void GUI::setup_newGUI(float posi_x, float posi_y)
{
    this->GUI_buffer.clear(sf::Color::Transparent);

    this->GUI_buffer.draw(this->baseGUI);
    this->GUI_buffer.draw(this->HPbar);
    this->GUI_buffer.draw(this->Energybar);
    this->GUI_buffer.draw(this->_selector);


    this->GUI_buffer.display();

    this->currentGUI.setTexture(this->GUI_buffer.getTexture());
    this->currentGUI.setOrigin(sf::Vector2f(::ScreenWidth/(ScaleUp * 2.f), ::ScreenHeight/(ScaleUp * 2.f)));
    this->currentGUI.setPosition(posi_x, posi_y);
}