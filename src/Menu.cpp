#include "MENU.h"

MENU::MENU(sf::Font &fontV1, sf::Font &fontV2)
{
    this->MenuBuffer.create(::ScreenWidth, ::ScreenHeight);

    this->FontSmall = fontV1;
    this->FontLarge = fontV2;

    this->GameName.setFont(FontLarge);
    this->GameName.setCharacterSize(72.f);
    this->GameName.setFillColor(sf::Color{170, 170, 170, 255});
    this->GameName.setString("Let's Me Out: The Dungeon");
    this->GameName.setOrigin(sf::Vector2f(GameName.getLocalBounds().left + GameName.getLocalBounds().width/2.f, (GameName.getLocalBounds().top + GameName.getLocalBounds().height)/2.f));
    this->GameName.setPosition(::ScreenWidth/2.f, (GameName.getLocalBounds().top + GameName.getLocalBounds().height));
    this->GameName.setOutlineColor(sf::Color::Black);
    this->GameName.setOutlineThickness(4.f);


    this->Name.setFont(FontSmall);
    this->Name.setCharacterSize(36.f);
    this->Name.setFillColor(sf::Color::White);
    this->Name.setString("65010134 Jirapat Treesuwan");
    this->Name.setOrigin(sf::Vector2f(Name.getLocalBounds().left, (Name.getLocalBounds().top + Name.getLocalBounds().height)/2.f));
    this->Name.setPosition(792.f, ::ScreenHeight - (Name.getLocalBounds().top + Name.getLocalBounds().height));
    this->Name.setOutlineColor(sf::Color::Black);
    this->Name.setOutlineThickness(4.f);

    this->Leaderboard.setFont(FontLarge);
    this->Leaderboard.setCharacterSize(54.f);
    this->Leaderboard.setFillColor(sf::Color::White);
    this->Leaderboard.setString("LEADERBOARD");
    this->Leaderboard.setOrigin(sf::Vector2f(Leaderboard.getLocalBounds().left, (Leaderboard.getLocalBounds().top + Leaderboard.getLocalBounds().height)/2.f));
    this->Leaderboard.setPosition(50.f, 395.f);
    this->Leaderboard.setOutlineThickness(6.f);
    this->Input_2.setSize(sf::Vector2f((Leaderboard.getLocalBounds().left + Leaderboard.getLocalBounds().width), (Leaderboard.getLocalBounds().top + Leaderboard.getLocalBounds().height)));
    this->Input_2.setPosition(50.f, 395.f);
    this->Input_2.setOrigin(sf::Vector2f(Leaderboard.getLocalBounds().left, (Leaderboard.getLocalBounds().top + Leaderboard.getLocalBounds().height)/2.f));

    this->Exit.setFont(FontLarge);
    this->Exit.setCharacterSize(54.f);
    this->Exit.setFillColor(sf::Color::White);
    this->Exit.setString("EXIT");
    this->Exit.setOrigin(sf::Vector2f(Exit.getLocalBounds().left, (Exit.getLocalBounds().top + Exit.getLocalBounds().height)/2.f));
    this->Exit.setPosition(50.f, 491.f);
    this->Exit.setOutlineThickness(6.f);
    this->Input_3.setSize(sf::Vector2f((Exit.getLocalBounds().left + Exit.getLocalBounds().width), (Exit.getLocalBounds().top + Exit.getLocalBounds().height)));
    this->Input_3.setPosition(50.f, 491.f);
    this->Input_3.setOrigin(sf::Vector2f(Exit.getLocalBounds().left, (Exit.getLocalBounds().top + Exit.getLocalBounds().height)/2.f));

    this->Start.setFont(FontLarge);
    this->Start.setCharacterSize(54.f);
    this->Start.setFillColor(sf::Color::White);
    this->Start.setString("START");
    this->Start.setOrigin(sf::Vector2f((Start.getLocalBounds().left), (Start.getLocalBounds().top + Start.getLocalBounds().height)/2.f));
    this->Start.setPosition(50.f, 299.f);
    this->Start.setOutlineThickness(6.f);
    this->Input_1.setSize(sf::Vector2f((Start.getLocalBounds().left + Start.getLocalBounds().width), (Start.getLocalBounds().top + Start.getLocalBounds().height)));
    this->Input_1.setPosition(50.f, 299.f);
    this->Input_1.setOrigin(sf::Vector2f((Start.getLocalBounds().left), (Start.getLocalBounds().top + Start.getLocalBounds().height)/2.f));

    this->MenuBaseTexture.loadFromFile("../content/Menu.png");
    this->MenuBase.setTexture(MenuBaseTexture);
    this->MenuBase.setOrigin(sf::Vector2f(MenuBaseTexture.getSize().x/2.f, MenuBaseTexture.getSize().y/2.f));
    this->MenuBase.setPosition(::ScreenWidth/2.f, 384.f);
    this->MenuBase.setScale(1046.f/176, 500.f/84);
}

void MENU::update(float &InitPosi_x, float &InitPosi_y, float &mousePosi_x, float &mousePosi_y, bool &Running, bool &StartGame, int &MenuState)
{
    this->Leaderboard.setOutlineColor(sf::Color::Black);
    this->Exit.setOutlineColor(sf::Color::Black);
    this->Start.setOutlineColor(sf::Color::Black);
    if(isSELECT(mousePosi_x, mousePosi_y, Input_1))
    {
        this->Start.setOutlineColor(sf::Color::Yellow);
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            printf("Start");
            Running = false;
            StartGame = true;
        }
    }
    if(isSELECT(mousePosi_x, mousePosi_y, Input_2))
    {
        this->Leaderboard.setOutlineColor(sf::Color::Yellow);
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            printf("Leader");
            MenuState = 1;
        }
    }
    if(isSELECT(mousePosi_x, mousePosi_y, Input_3))
    {
        this->Exit.setOutlineColor(sf::Color::Yellow);
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            MenuState = 2;
        }
    }
    setup_newMENU(InitPosi_x, InitPosi_y);
}
void MENU::setup_newMENU(float posi_x, float posi_y)
{
    this->MenuBuffer.clear(sf::Color::Blue);
    this->MenuBuffer.draw(this->MenuBase);
    
    this->MenuBuffer.draw(this->Start);
    this->MenuBuffer.draw(this->Leaderboard);
    this->MenuBuffer.draw(this->Exit);
    this->MenuBuffer.draw(this->Name);
    this->MenuBuffer.draw(this->GameName);


    this->MenuBuffer.display();
    
    this->MenuSprite.setTexture(this->MenuBuffer.getTexture());
    this->MenuSprite.setPosition(posi_x, posi_y);
}

bool MENU::isSELECT(float Posi_x, float Posi_y, sf::RectangleShape  &Container)
{
    if(Container.getGlobalBounds().contains(sf::Vector2f(Posi_x, Posi_y)))
    {
        return true;
    }
    return false;
}