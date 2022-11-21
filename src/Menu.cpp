#include "MENU.h"

MENU::MENU(sf::Font &fontV1, sf::Font &fontV2)
{
    this->MenuBuffer.create(::ScreenWidth, ::ScreenHeight);

    this->FontSmall = fontV1;
    this->FontLarge = fontV2;

    this->Chest.loadFromFile("../content/Icon.png");
    this->ChestSprite.setTexture(this->Chest);
    this->ChestSprite.setScale(16.f, 16.f);
    this->ChestSprite.setOrigin(this->Chest.getSize().x/2.f, this->Chest.getSize().y/2.f);
    this->ChestSprite.setPosition(804.f, 391.f);

    this->knightTexture.loadFromFile("../content/Knight.png");
    this->priestTexture.loadFromFile("../content/Priest.png");
    this->rogueTexture.loadFromFile("../content/Rogue.png");

    this->knight.setSize(sf::Vector2f(::CellPixelSize, ::CellPixelSize));
    this->priest.setSize(sf::Vector2f(::CellPixelSize, ::CellPixelSize));
    this->rogue.setSize(sf::Vector2f(::CellPixelSize, ::CellPixelSize));
    this->knight.setOrigin(::CellPixelSize/2.f, ::CellPixelSize/2.f);
    this->priest.setOrigin(::CellPixelSize/2.f, ::CellPixelSize/2.f);
    this->rogue.setOrigin(::CellPixelSize/2.f, ::CellPixelSize/2.f);
    this->knight.setTexture(&this->knightTexture);
    this->priest.setTexture(&this->priestTexture);
    this->rogue.setTexture(&this->rogueTexture);
    this->knight.setScale(16.f, 16.f);
    this->priest.setScale(16.f, 16.f);
    this->rogue.setScale(16.f, 16.f);

    this->knight.setPosition(62.f, 428.f);
    this->priest.setPosition(996.f, 47.f);
    this->rogue.setPosition(804.f, 257.f);
    
    this->priest.rotate(180.f);

    this->GameName.setFont(FontLarge);
    this->GameName.setCharacterSize(72.f);
    this->GameName.setFillColor(sf::Color{190, 190, 190, 255});
    this->GameName.setString("Let's Me Out: The Dungeon");
    this->GameName.setOrigin(sf::Vector2f(GameName.getLocalBounds().left + GameName.getLocalBounds().width/2.f, (GameName.getLocalBounds().top + GameName.getLocalBounds().height)/2.f));
    this->GameName.setPosition(::ScreenWidth/2.f, (GameName.getLocalBounds().top + GameName.getLocalBounds().height));
    this->GameName.setOutlineColor(sf::Color::Black);
    this->GameName.setOutlineThickness(7.f);


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
    this->MenuBase.setPosition(::ScreenWidth/2.f, 374.f);
    this->MenuBase.setScale(1046.f/176, 500.f/84);

    this->classSEL_1.setSize(sf::Vector2f(::CellPixelSize * 8.f + 5.f, ::CellPixelSize * 8.f + 5.f));
    this->classSEL_2.setSize(sf::Vector2f(::CellPixelSize * 8.f + 5.f, ::CellPixelSize * 8.f + 5.f));
    this->classSEL_3.setSize(sf::Vector2f(::CellPixelSize * 8.f + 5.f, ::CellPixelSize * 8.f + 5.f));
    this->classSEL_1.setOrigin(sf::Vector2f(::CellPixelSize * 4.f + 5.f, ::CellPixelSize * 4.f + 5.f));
    this->classSEL_2.setOrigin(sf::Vector2f(::CellPixelSize * 4.f + 5.f, ::CellPixelSize * 4.f + 5.f));
    this->classSEL_3.setOrigin(sf::Vector2f(::CellPixelSize * 4.f + 5.f, ::CellPixelSize * 4.f + 5.f));
    this->classSEL_1.setPosition(::ScreenWidth/2.f - 300, ::ScreenHeight/3.f);
    this->classSEL_2.setPosition(::ScreenWidth/2.f, ::ScreenHeight/3.f);
    this->classSEL_3.setPosition(::ScreenWidth/2.f + 300, ::ScreenHeight/3.f);
    this->classSEL_1.setOutlineThickness(4.f);
    this->classSEL_2.setOutlineThickness(4.f);
    this->classSEL_3.setOutlineThickness(4.f);
    this->classSEL_1.setFillColor(sf::Color{0, 0, 0, 127});
    this->classSEL_2.setFillColor(sf::Color{0, 0, 0, 127});
    this->classSEL_3.setFillColor(sf::Color{0, 0, 0, 127});

    this->PlayerAttri_1.setFont(FontSmall);
    this->PlayerAttri_1.setCharacterSize(36.f);
    this->PlayerAttri_1.setFillColor(sf::Color::White);
    this->PlayerAttri_1.setString("Healths: 6\nSheild : 5\nEnergy : 180\nCritChance : 10%\nSpeed  : 70\nSkill  : Dual Weilding\n(Increase FireRate by 2)\n45sec Cooldown");
    this->PlayerAttri_1.setOrigin(sf::Vector2f(PlayerAttri_1.getLocalBounds().left + PlayerAttri_1.getLocalBounds().width/2.f, (PlayerAttri_1.getLocalBounds().top + PlayerAttri_1.getLocalBounds().height)/2.f));
    this->PlayerAttri_1.setPosition(::ScreenWidth/2.f - 300 + ::CellPixelSize * 2.f + 5.f, ::ScreenHeight/3.f + 170);
    this->PlayerAttri_1.setOutlineColor(sf::Color::Black);
    this->PlayerAttri_1.setOutlineThickness(4.f);
    
    this->PlayerAttri_2.setFont(FontSmall);
    this->PlayerAttri_2.setCharacterSize(36.f);
    this->PlayerAttri_2.setFillColor(sf::Color::White);
    this->PlayerAttri_2.setString("Healths: 5\nSheild : 3\nEnergy : 180\nCritChance : 20%\nSpeed  : 80\nSkill  : Fatal Shot\n(100% CritChance for 5 sec)\n30sec Cooldown");
    this->PlayerAttri_2.setOrigin(sf::Vector2f(PlayerAttri_2.getLocalBounds().left + PlayerAttri_2.getLocalBounds().width/2.f, (PlayerAttri_2.getLocalBounds().top + PlayerAttri_2.getLocalBounds().height)/2.f));
    this->PlayerAttri_2.setPosition(::ScreenWidth/2.f + ::CellPixelSize * 2.f + 5.f, ::ScreenHeight/3.f + 170);
    this->PlayerAttri_2.setOutlineColor(sf::Color::Black);
    this->PlayerAttri_2.setOutlineThickness(4.f);

    this->PlayerAttri_3.setFont(FontSmall);
    this->PlayerAttri_3.setCharacterSize(36.f);
    this->PlayerAttri_3.setFillColor(sf::Color::White);
    this->PlayerAttri_3.setString("Healths: 12\nSheild : 3\nEnergy : 200\nCritChance : 2%\nSpeed  : 60\nSkill  : Heal\n(Recover 1 Health for 4 sec)\n90sec Cooldown");
    this->PlayerAttri_3.setOrigin(sf::Vector2f(PlayerAttri_3.getLocalBounds().left + PlayerAttri_3.getLocalBounds().width/2.f, (PlayerAttri_3.getLocalBounds().top + PlayerAttri_3.getLocalBounds().height)/2.f));
    this->PlayerAttri_3.setPosition(::ScreenWidth/2.f + 300 + ::CellPixelSize * 2.f + 5.f, ::ScreenHeight/3.f + 170);
    this->PlayerAttri_3.setOutlineColor(sf::Color::Black);
    this->PlayerAttri_3.setOutlineThickness(4.f);

    this->ChooseNplaySelTexture.loadFromFile("../content/GUI/InputSelected.png");
    this->ChooseNplaySelected.setTexture(this->ChooseNplaySelTexture);
    this->ChooseNplaySelected.setOrigin(sf::Vector2f(this->ChooseNplaySelTexture.getSize().x/2.f, this->ChooseNplaySelTexture.getSize().y/2.f));
    this->ChooseNplaySelected.setScale(192.f/46, 59.f/13);
    this->ChooseNplaySelected.setPosition(::ScreenWidth/2.f, ::ScreenHeight - 50.f);

    this->ChooseNplayBlockTexture.loadFromFile("../content/GUI/InputBlock.png");
    this->ChooseNplayBlock.setTexture(this->ChooseNplayBlockTexture);
    this->ChooseNplayBlock.setOrigin(sf::Vector2f(this->ChooseNplayBlockTexture.getSize().x/2.f, this->ChooseNplayBlockTexture.getSize().y/2.f));
    this->ChooseNplayBlock.setScale(192.f/46, 59.f/13);
    this->ChooseNplayBlock.setPosition(::ScreenWidth/2.f, ::ScreenHeight - 50.f);

    this->clickPlayBox.setSize((sf::Vector2f(this->ChooseNplayBlockTexture.getSize().x * 192.f/46, 59.f/13 * this->ChooseNplayBlockTexture.getSize().y)));
    this->clickPlayBox.setOrigin((sf::Vector2f(this->ChooseNplayBlockTexture.getSize().x * 192.f/92.f, 59.f * this->ChooseNplayBlockTexture.getSize().y/26.f)));
    this->clickPlayBox.setFillColor(sf::Color::Transparent);
    this->clickPlayBox.setPosition(::ScreenWidth/2.f, ::ScreenHeight - 50.f);

    this->ChooseNplay.setFont(FontSmall);
    this->ChooseNplay.setCharacterSize(36.f);
    this->ChooseNplay.setFillColor(sf::Color::White);
    this->ChooseNplay.setString("Click to play");
    this->ChooseNplay.setOrigin(sf::Vector2f(ChooseNplay.getLocalBounds().left + ChooseNplay.getLocalBounds().width/2.f, (ChooseNplay.getLocalBounds().top + ChooseNplay.getLocalBounds().height)/2.f));
    this->ChooseNplay.setPosition(::ScreenWidth/2.f, ::ScreenHeight - 60.f);
    this->ChooseNplay.setOutlineColor(sf::Color::Black);
    this->ChooseNplay.setOutlineThickness(4.f);

    this->goBackBox.setSize((sf::Vector2f(this->ChooseNplayBlockTexture.getSize().x * 192.f/92, 59.f/26 * this->ChooseNplayBlockTexture.getSize().y)));
    this->goBackBox.setOrigin((sf::Vector2f(this->ChooseNplayBlockTexture.getSize().x * 192.f/184.f, 59.f * this->ChooseNplayBlockTexture.getSize().y/52.f)));
    this->goBackBox.setFillColor(sf::Color::Transparent);
    this->goBackBox.setPosition(50.f, 25.f);

    this->goBackSel.setTexture(this->ChooseNplaySelTexture);
    this->goBackSel.setOrigin(sf::Vector2f(this->ChooseNplaySelTexture.getSize().x/2.f, this->ChooseNplaySelTexture.getSize().y/2.f));
    this->goBackSel.setScale(192.f/92, 59.f/26);
    this->goBackSel.setPosition(50.f, 25.f);

    this->goBackBlock.setTexture(this->ChooseNplayBlockTexture);
    this->goBackBlock.setOrigin(sf::Vector2f(this->ChooseNplayBlockTexture.getSize().x/2.f, this->ChooseNplayBlockTexture.getSize().y/2.f));
    this->goBackBlock.setScale(192.f/92, 59.f/26);
    this->goBackBlock.setPosition(50.f, 25.f);

    this->goBack.setFont(FontSmall);
    this->goBack.setCharacterSize(36.f);
    this->goBack.setFillColor(sf::Color::White);
    this->goBack.setString("Back");
    this->goBack.setOrigin(sf::Vector2f(goBack.getLocalBounds().left + goBack.getLocalBounds().width/2.f, (goBack.getLocalBounds().top + goBack.getLocalBounds().height)/2.f));
    this->goBack.setPosition(50.f, 15.f);
    this->goBack.setOutlineColor(sf::Color::Black);
    this->goBack.setOutlineThickness(4.f);

    this->playerNameTexture.loadFromFile("../content/GUI/CoolDownbar.png");
    this->playerNameBox.setTexture(this->playerNameTexture);
    this->playerNameBox.setOrigin(playerNameTexture.getSize().x/2.f, playerNameTexture.getSize().y/2.f);
    this->playerNameBox.setScale(4.f, 4.f);
    this->playerNameBox.setPosition(::ScreenWidth/2.f, 40.f);

    this->playerName.setFont(FontSmall);
    this->playerName.setCharacterSize(36.f);
    this->playerName.setFillColor(sf::Color::White);
    this->playerName.setPosition(::ScreenWidth/2.f + 3.f, 30.f);
    this->playerName.setOutlineColor(sf::Color::Black);
    this->playerName.setOutlineThickness(4.f);

    this->EnterName.setFont(FontSmall);
    this->EnterName.setCharacterSize(36.f);
    this->EnterName.setFillColor(sf::Color::White);
    this->EnterName.setPosition(::ScreenWidth/2.f + 1.f, 30.f);
    this->EnterName.setString("Enter Your Name");
    this->EnterName.setOrigin(sf::Vector2f((EnterName.getLocalBounds().left + EnterName.getLocalBounds().width), EnterName.getLocalBounds().top + EnterName.getLocalBounds().height)/2.f);
    this->EnterName.setOutlineColor(sf::Color::Black);
    this->EnterName.setOutlineThickness(4.f);

    for(int i = 0; i < 5; i++)
    {
        this->scoreInfoText[i].setFont(FontLarge);
        this->scoreInfoText[i].setCharacterSize(36.f);
        this->scoreInfoText[i].setFillColor(sf::Color::White);
        this->scoreInfoText[i].setPosition(::ScreenWidth/3.f , 180.f + i * 75);
        this->scoreInfoText[i].setOutlineColor(sf::Color::Black);
        this->scoreInfoText[i].setOutlineThickness(4.f);
        this->scoreInfoText[i].setOrigin(0, (scoreInfoText[i].getLocalBounds().top + scoreInfoText[i].getLocalBounds().height)/2.f);
    }

}

void MENU::update(float &InitPosi_x, float &InitPosi_y, float &mousePosi_x, float &mousePosi_y, bool &Running, bool &StartGame, int &MenuState)
{
    if(MenuState == 0)
    {
        firstTimeRead = true;
        this->Leaderboard.setOutlineColor(sf::Color::Black);
        this->Exit.setOutlineColor(sf::Color::Black);
        this->Start.setOutlineColor(sf::Color::Black);
        this->knight.setScale(16.f, 16.f);
        this->priest.setScale(16.f, 16.f);
        this->rogue.setScale(16.f, 16.f);

        this->knight.setPosition(62.f, 428.f);
        this->priest.setPosition(996.f, 47.f);
        this->rogue.setPosition(804.f, 257.f);

        this->priest.setRotation(180.f);
        if(isSELECT(mousePosi_x, mousePosi_y, Input_1))
        {
            this->Start.setOutlineColor(sf::Color::Yellow);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                MenuState = 1;
            }
        }
        if(isSELECT(mousePosi_x, mousePosi_y, Input_2))
        {
            this->Leaderboard.setOutlineColor(sf::Color::Yellow);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                MenuState = 2;
            }
        }
        if(isSELECT(mousePosi_x, mousePosi_y, Input_3))
        {
            this->Exit.setOutlineColor(sf::Color::Yellow);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                MenuState = 3;
            }
        }
    }
    else if (MenuState == 1)
    {
        this->playerName.setString(playerNameContrainer);
        this->classSEL_1.setOutlineColor(sf::Color::White);
        this->classSEL_2.setOutlineColor(sf::Color::White);
        this->classSEL_3.setOutlineColor(sf::Color::White);

        this->knight.setScale(8.f, 8.f);
        this->priest.setScale(8.f, 8.f);
        this->priest.setRotation(0.f);
        this->rogue.setScale(8.f, 8.f);

        this->playerName.setOrigin(sf::Vector2f((playerName.getLocalBounds().left + playerName.getLocalBounds().width), playerName.getLocalBounds().top + playerName.getLocalBounds().height)/2.f);

        this->knight.setPosition(::ScreenWidth/2.f - 300, ::ScreenHeight/3.f);
        this->rogue.setPosition(::ScreenWidth/2.f, ::ScreenHeight/3.f);
        this->priest.setPosition(::ScreenWidth/2.f + 300, ::ScreenHeight/3.f);

        if(isSELECT(mousePosi_x, mousePosi_y, classSEL_1) || ClassSEL == 0)
        {
            this->classSEL_1.setOutlineColor(sf::Color::Yellow);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && ClassSEL != 0)
            {
               ClassSEL = 0;
            }
        }
        if(isSELECT(mousePosi_x, mousePosi_y, classSEL_2) || ClassSEL == 1)
        {
            this->classSEL_2.setOutlineColor(sf::Color::Yellow);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && ClassSEL != 1)
            {
               ClassSEL = 1;
            }
        }
        if(isSELECT(mousePosi_x, mousePosi_y, classSEL_3) || ClassSEL == 2)
        {
            this->classSEL_3.setOutlineColor(sf::Color::Yellow);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && ClassSEL != 2)
            {
               ClassSEL = 2;
            }
        }
        if(isSELECT(mousePosi_x, mousePosi_y, clickPlayBox) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && playerNameContrainer.length() > 0)
        {
            Running = false;
            StartGame = true;
        }
        if(isSELECT(mousePosi_x, mousePosi_y, goBackBox) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            MenuState = 0;
        }
    }
    else if (MenuState == 2)
    {
        if(firstTimeRead)
        {
            firstTimeRead = false;
            file_LeaderBoardReader();
            for(int i = 0; i < 5; i++)
            {
                std::stringstream scoreStream;
                scoreStream << i+1 << " ) "<< playerNameInfo[i] << "\t" << scoreInfo[i];
                this->scoreInfoText[i].setString(scoreStream.str());
            }
        }
        if(isSELECT(mousePosi_x, mousePosi_y, goBackBox) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            MenuState = 0;
        }

    }
    setup_newMENU(InitPosi_x, InitPosi_y, mousePosi_x, mousePosi_y, MenuState);
}
void MENU::setup_newMENU(float posi_x, float posi_y, float mousePosi_x, float mousePosi_y, int State)
{
    this->MenuBuffer.clear(sf::Color::Blue);
    this->MenuBuffer.draw(this->MenuBase);
    if(State == 0)
    {
        this->MenuBuffer.draw(this->knight);
        this->MenuBuffer.draw(this->rogue);
        this->MenuBuffer.draw(this->ChestSprite);
        this->MenuBuffer.draw(this->priest);

        this->MenuBuffer.draw(this->Start);
        this->MenuBuffer.draw(this->Leaderboard);
        this->MenuBuffer.draw(this->Exit);
        this->MenuBuffer.draw(this->Name);
        this->MenuBuffer.draw(this->GameName);
    }
    if(State == 1)
    {
        this->MenuBuffer.draw(this->classSEL_1);
        this->MenuBuffer.draw(this->classSEL_2);
        this->MenuBuffer.draw(this->classSEL_3);

        this->MenuBuffer.draw(this->knight);
        this->MenuBuffer.draw(this->rogue);
        this->MenuBuffer.draw(this->priest);

        this->MenuBuffer.draw(this->PlayerAttri_1);
        this->MenuBuffer.draw(this->PlayerAttri_2);
        this->MenuBuffer.draw(this->PlayerAttri_3);

        if(isSELECT(mousePosi_x, mousePosi_y, clickPlayBox))
        {
            this->MenuBuffer.draw(this->ChooseNplaySelected);
        }
        else
        {
            this->MenuBuffer.draw(this->ChooseNplayBlock);
        }
        if(isSELECT(mousePosi_x, mousePosi_y, goBackBox))
        {
             this->MenuBuffer.draw(this->goBackSel);
        }
        else
        {
            this->MenuBuffer.draw(this->goBackBlock);
        }
        this->MenuBuffer.draw(this->ChooseNplay);
        this->MenuBuffer.draw(this->goBack);
        this->MenuBuffer.draw(this->playerNameBox);
        if(this->playerNameContrainer.length() == 0)
        {
            this->MenuBuffer.draw(this->EnterName);
        }
        else
        {
            this->MenuBuffer.draw(this->playerName);
        }
    }
    if(State == 2)
    {

        if(isSELECT(mousePosi_x, mousePosi_y, goBackBox))
        {
             this->MenuBuffer.draw(this->goBackSel);
        }
        else
        {
            this->MenuBuffer.draw(this->goBackBlock);
        }
        for(int i = 0; i < 5; i++)
        {
            this->MenuBuffer.draw(this->scoreInfoText[i]);
        }
        this->MenuBuffer.draw(this->goBack);
    }
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

void MENU::file_LeaderBoardReader()
{
    FILE *fptr;
    int i = 0;
    if (!(fptr = fopen("LeaderBoard.txt", "r"))){
        fptr = fopen("LeaderBoard.txt", "w+");
        fprintf(fptr,"0~Unknow1\n0~Unknow2\n0~Unknow3\n0~Unknow4\n0~Unknow5");
        fclose(fptr);
    }
    fptr = fopen("LeaderBoard.txt","r");
    for(i = 0; i < 5; i++){
        fscanf(fptr,"%d~%[^\n]s", &scoreInfo[i], &playerNameInfo[i]);
    }
    fclose(fptr);

    
}