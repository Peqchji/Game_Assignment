#include "GUI.h"
GUI::GUI(sf::Font &fontV1, sf::Font &fontV2)
{
    this->GUI_buffer.create(::ScreenWidth, ::ScreenHeight);

    this->base.loadFromFile("../content/GUI/InGameGUI_Base.png");
    this->frontHP.loadFromFile("../content/GUI/HPstat.png");
    this->frontEnergy.loadFromFile("../content/GUI/Energystat.png");
    this->selector.loadFromFile("../content/GUI/Selector.png");
    this->sheild.loadFromFile("../content/GUI/Sheild.png");
    this->coolDownTexture.loadFromFile("../content/GUI/CoolDownStat.png");
    this->PauseButton.loadFromFile("../content/GUI/PauseButton_GUI.png");

    this->font1 = fontV1;
    this->font2 = fontV2;
    this->ScoreText.setFont(font1);
    this->ScoreText.setCharacterSize(48.f);
    this->ScoreText.setFillColor(sf::Color::White);
    this->ScoreText.setPosition(141.f, 53.f);

    this->HealthText.setFont(font1);
    this->HealthText.setCharacterSize(30.f);
    this->HealthText.setFillColor(sf::Color::Black);
    this->HealthText.setPosition(199.f,  2.f);

    this->EnergyText.setFont(font1);
    this->EnergyText.setCharacterSize(30.f);
    this->EnergyText.setFillColor(sf::Color::Black);
    this->EnergyText.setPosition(199.f,  28.f);

    this->SkillText.setFont(font1);
    this->SkillText.setCharacterSize(30.f);
    this->SkillText.setFillColor(sf::Color::Yellow);
    this->SkillText.setPosition(117.f, 530.f);

    this->PauseButtonSprite.setTexture(this->PauseButton);
    this->PauseButtonSprite.setOrigin(this->PauseButtonSprite.getLocalBounds().left + this->PauseButtonSprite.getLocalBounds().width, 0);
    this->PauseButtonSprite.setPosition(sf::Vector2f(520, 0));
    this->PauseButtonSprite.setScale(1.5, 1.5);

    this->baseGUI.setTexture(this->base);
    this->baseGUI.setScale(sf::Vector2f(1.f, 1.f));

    this->HPbar.setTexture(this->frontHP);

    this->Energybar.setTexture(this->frontEnergy);

    this->_selector.setTexture(this->selector);
    this->_selector.scale(sf::Vector2f((25.f/6), (21.f/5)));

    this->SheildSprite.setTexture(this->sheild);
    this->SheildSprite.setScale(sf::Vector2f(1.5f*ScaleUp, 1.f*ScaleUp));

    this->CoolDownStat.setTexture(coolDownTexture);

    this->CoolDownStat.setPosition(31.f, 518.f);
    this->HPbar.setPosition(114.f, 4.f);
    this->Energybar.setPosition(114.f, 30.f);
    this->_selector.setPosition(891.f, 471.f);

}

void GUI::update(int &currentTool, sf::Texture &Gun_no1, sf::Texture &Gun_no2, sf::RectangleShape &player, float score, float &setupPosi_x, float &setupPosi_y, float currentHP, float currentEnergy, float MaxHP, float MaxEnergy, float currentSheild, std::string &SkillName,float currentCooldown, float MaxCooldown)
{
    std::stringstream SkillStream;

    std::stringstream HealthStream;
    std::stringstream EnergyStream;
    std::stringstream ScoreStream;
    AmountSheild = currentSheild;
    playerModel = player;
    playerModel.setScale(3.f, 3.f);
    currentGun = currentTool;

    float scoreBuffer = score/1000000;
    ScoreStream.clear();
    if(score >= 1000000)
    {
        ScoreStream << std::fixed << std::setprecision(3) << scoreBuffer << "M";
    }
    else
        ScoreStream << score;
    this->ScoreText.setString(ScoreStream.str());
    this->ScoreText.setOrigin(0, (ScoreText.getLocalBounds().top + ScoreText.getLocalBounds().height)/2.f);
    
    
    HealthStream << std::fixed << std::setprecision(0) << currentHP << "/" << MaxHP;
    this->HealthText.setString( HealthStream.str());
    this->HealthText.setOrigin(sf::Vector2f((HealthText.getLocalBounds().left + HealthText.getLocalBounds().width)/2.f, (HealthText.getLocalBounds().top + HealthText.getLocalBounds().height)/2.f));

    EnergyStream << std::fixed << std::setprecision(0) << currentEnergy << "/" << MaxEnergy;
    this->EnergyText.setString( EnergyStream.str());
    this->EnergyText.setOrigin(sf::Vector2f((EnergyText.getLocalBounds().left + EnergyText.getLocalBounds().width)/2.f, (EnergyText.getLocalBounds().top + EnergyText.getLocalBounds().height)/2.f));
    if(MaxCooldown - currentCooldown > 0)
    {
        SkillStream << std::fixed << std::setprecision(1) << "CoolDown : " << (MaxCooldown-currentCooldown)/1000 << "s";
    }
    else if(SkillName.compare("Heal") == 0)
    {
        SkillStream << "Press \'E\' to cast \n \t\"" << SkillName << "\"";
    }
    else
     {
        SkillStream << "Press \'E\' to cast \n \"" << SkillName << "\"";
    }
    this->SkillText.setString( SkillStream.str());
    this->SkillText.setOrigin(sf::Vector2f((SkillText.getLocalBounds().left + SkillText.getLocalBounds().width)/2.f, (SkillText.getLocalBounds().top + SkillText.getLocalBounds().height)/2.f));

    this->Gun_1.setTexture(Gun_no1);
    this->Gun_2.setTexture(Gun_no2);
    this->Gun_1.setOrigin(Gun_no1.getSize().x/2.f, Gun_no1.getSize().y/2.f);
    this->Gun_2.setOrigin(Gun_no2.getSize().x/2.f, Gun_no2.getSize().y/2.f) ;

    this->Gun_1.setPosition(sf::Vector2f(903.f, 533.f));
    this->Gun_2.setPosition(sf::Vector2f(984.f, 533.f));
    this->Gun_1.setTextureRect(sf::IntRect(0, 0, Gun_no1.getSize().x, Gun_no1.getSize().y));
    this->Gun_2.setTextureRect(sf::IntRect(0, 0, Gun_no2.getSize().x, Gun_no2.getSize().y));
    this->Gun_1.setScale(0.8 * ScaleUp, 0.8 * ScaleUp);
    this->Gun_2.setScale(0.8 * ScaleUp, 0.8 * ScaleUp);
    
    float progess_bar_x = (204.f/50);
    float progess_bar_y = (13.f/3);
    float cooldown_bar_x = (166.f/40);
    float cooldown_bar_y = (41.f/10);
    
    moveSel();
    this->HPbar.setScale(currentHP/MaxHP * progess_bar_x, progess_bar_y);
    this->Energybar.setScale(currentEnergy/MaxEnergy * progess_bar_x, progess_bar_y);
    if(currentCooldown > MaxCooldown)
    {
        this->CoolDownStat.setScale(cooldown_bar_x, cooldown_bar_y);
    }
    else
    {
        this->CoolDownStat.setScale(currentCooldown/MaxCooldown * cooldown_bar_x, cooldown_bar_y);
    }

    if(AmountSheild > 0)
    {
        showSheild.clear();
        for(int i = 0; i < AmountSheild; i++)
        { 
             this->SheildSprite.setPosition(sf::Vector2f((15 + i * sheild.getSize().x * 4 * 1.5f), 99));
            showSheild.push_back(this->SheildSprite);
        }
    }
    this->playerModel.setPosition(sf::Vector2f(108/(2.f), 96/(2.f)));

    setup_newGUI(setupPosi_x, setupPosi_y);
}

void GUI::setup_newGUI(float posi_x, float posi_y)
{
    this->GUI_buffer.clear(sf::Color::Transparent);

    this->GUI_buffer.draw(this->baseGUI);
    this->GUI_buffer.draw(this->Gun_1);
    this->GUI_buffer.draw(this->Gun_2);

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

    this->GUI_buffer.draw(this->HealthText);
    this->GUI_buffer.draw(this->EnergyText);
    this->GUI_buffer.draw(this->ScoreText);
    this->GUI_buffer.draw(this->SkillText);

    this->GUI_buffer.draw(this->PauseButtonSprite);

    this->GUI_buffer.display();

    this->currentGUI.setTexture(this->GUI_buffer.getTexture());
    this->currentGUI.setOrigin(sf::Vector2f(::ScreenWidth/ 2.f, ::ScreenHeight/ 2.f));
    this->currentGUI.setScale((1.f/ScaleUp), 1.f/ScaleUp);
    this->currentGUI.setPosition(posi_x, posi_y);
}

void GUI::moveSel()
{
 if(currentGun == 0)
 {
    this->_selector.setPosition(891.f, 471.f);
 }
 else
 {
    this->_selector.setPosition((972.f) , 471.f);
 }
}

void GUI::isPauseButtonPressed(float &mouse_x, float &mouse_y, bool &Toggle)
{
    if(this->PauseButtonSprite.getGlobalBounds().contains(sf::Vector2f(mouse_x, mouse_y)) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        Toggle = true;
    }
}