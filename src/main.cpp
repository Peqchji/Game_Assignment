#include "MASTER.h"
#include "PLAYER.h"
#include "WORLD.h"
#include "GAMELOGIC.h"
#include "WEAPON.h"
#include "GUI.h"
#include "ITEM.h"
#include "PAUSE.h"
#include "MENU.h"
#include "CAL_Results.h"
#include "SFX.h"

int Gameplay(std::string &PlayerType, sf::RenderWindow &window, sf::View &view, sf::Font &font1,  sf::Font &font2, unsigned int &score);

int main()
{   
    std::string playerClass("Rogue");
    sf::SoundBuffer backGroundMusicBuffer;
    sf::Sound backGroundMusic;
    backGroundMusicBuffer.loadFromFile("../content/backGroundMusic.wav");
    backGroundMusic.setBuffer(backGroundMusicBuffer);
    backGroundMusic.setLoop(true);
    backGroundMusic.setVolume(30);
    backGroundMusic.play();


    int gameState = 0;
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    sf::Image icon;
    icon.loadFromFile("Icon.png");
    sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHeight), "Let's Me Out: The Dungeon", sf::Style::Titlebar | sf::Style::Close);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()); 
    window.setFramerateLimit(setFPS);

    sf::View view;
    view.setSize(ScreenWidth/ScaleUp, ScreenHeight/ScaleUp);

    sf::Font font_V1;
    font_V1.loadFromFile("../content/GUI/MinimalPixelFont.ttf");
    sf::Font font_V2;
    font_V2.loadFromFile("../content/GUI/MinimalPixel v2.ttf");
    unsigned int score =  0;

    while(window.isOpen())
    {
        Gameplay(playerClass, window, view, font_V1, font_V2, score);
        break;
    }
    return 0;
}

int Gameplay(std::string &PlayerType, sf::RenderWindow &window, sf::View &view, sf::Font &font1,  sf::Font &font2, unsigned int &score)
{
    int x, y, i;
    short RoomIn_A_Map = 5;
    short RoomCleared = 0;
    bool IsOpen = true;
    bool InGame = false;
    bool InResults = false;
    bool InMenu = true;
    int MenuSel = 0;

    bool init_gameplay = true;
    //std::string player_class = PlayerType;

    enum {RUNNING, PAUSING, GAMEOVER};
    int mode = 0;


    int current_PlayerPosi_RoomID;
    int room_id;

    bool EnableEnemiesCLK = false;
    WORLD world;
    GAMELOGIC gameLogic;
    PAUSE pause(font1, font2);

    PLAYER player;
    std::vector<ENEMY*> Enemies;
    float HardnessMultiplier = 0;

    std::vector<CHEST*> Chests;
    std::vector<BULLET*> bullets;
    std::vector<ITEM*> items;
    Portal portal;
    WEAPON weapon[2];

    SFXClass sfx;

    GUI gui(font1, font2);
    
    //Timer
    sftools::Chronometer Timer_FireRate;
    Timer_FireRate.reset(true);
    sf::Time bullet_Timer;

    //MIDDLE of WINDOW
    sf::Vector2f MiddleOfWin(ScreenWidth/2.f, ScreenHeight/2.f);

    //#player position
    sf::Vector2f playerPosi;

    // Setup View
    sf::Event ev;

    // mouse position and aiming
    sf::Mouse mouse;
    sf::Vector2f mousePosi;
    sf::Vector2f AimDir;
    sf::Vector2f AimDir_Normal; 

    std::string gunType = "Pistol";
    std::string lastGun;
    int currentGun = 0;
    bool pickedUp = false;
    float increaseFireRate = 1;

    //Clock
    float dt;
    sftools::Chronometer dt_clock;

    bool toggleCLK = false;


    MENU menu(font1, font2);
    RESULTS cal_score(font1, font2);
    //##GAME LOOP##
    while (IsOpen)
    {
        //event
        //////////////////////////////////DEBUGGING TOOL//////////////////////////////////
        while(window.pollEvent(ev))
        {
            switch(ev.type)
            {
                case sf::Event::Closed:
                    IsOpen = false;
                    break;
                /*case sf::Event::LostFocus:
                    break;*/
                case sf::Event::KeyPressed:
                    if(ev.key.code == sf::Keyboard::Escape && mode != GAMEOVER && !InMenu)
                    {
                        toggleCLK = true; 
                    }
                    if(ev.key.code == sf::Keyboard::R && mode == RUNNING)
                    {
                        currentGun = (currentGun+1) % 2;
                    }
                    if (ev.key.code == sf::Keyboard::Backspace && menu.playerNameContrainer.length() > 0 && MenuSel == 1)
                    {
						menu.playerNameContrainer.pop_back();
					}
					if (ev.key.code == sf::Keyboard::Enter || ev.key.code == sf::Keyboard::Space && MenuSel == 1) {
						break;
					}
                    break;
                case sf::Event::TextEntered:
				    if (MenuSel == 1 && ev.text.unicode < 122 && ev.text.unicode > 33 && menu.playerNameContrainer.length() <= 15)
                    {
						menu.playerNameContrainer.push_back(ev.text.unicode);
				    }
                    break;
            }
        }
        if(toggleCLK)
        {
            if(mode == PAUSING)
            {
                mode = RUNNING;
                EnableEnemiesCLK = true;
            }
            else if(mode == GAMEOVER)
            {
                EnableEnemiesCLK = true;
            }
            else
            {
                mode = PAUSING;
                EnableEnemiesCLK = true;
            }
            player.ToggleCLK();
            Timer_FireRate.toggle();
            if(bullets.size() > 0)
            {
                for(int i = 0; i <bullets.size(); i++)
                {
                    bullets[i]->ToggleCLK();
                }
            }
            if(Chests.size() > 0)
            {
                for(int i = 0; i <  Chests.size(); i++)
                {
                    Chests[i]->ToggleCLK();
                }
            }
            portal.ToggleCLK();
            toggleCLK = false;
        }
        toggleCLK = false;

        if(InMenu)
        {
            enum{MAINMENU, SELECTCLASS, LEADERBOARD, EXITGAME};
            //view.setCenter(::ScreenWidth/2.f, ::ScreenHeight/2.f);

            float init_x = 0;
            float init_y = 0;
            window.setView(window.getDefaultView());
            mousePosi = window.mapPixelToCoords(mouse.getPosition(window));
            menu.update(init_x, init_y, mousePosi.x, mousePosi.y, InMenu, InGame, MenuSel);
            
            window.clear(sf::Color::Transparent);
            //window.setView(view);
            window.draw(menu.MenuSprite);

            window.display();
            std::string playerClass[3] = {"Knight", "Rogue", "Priest"};
            PlayerType = playerClass[menu.ClassSEL];
            
            if(MenuSel == EXITGAME)
            {
                window.close();
                IsOpen = false;
            }
            mode = RUNNING;
            init_gameplay = true;
        }
        else if(InGame)
        {
            if(init_gameplay)
            {
                RoomCleared = 0;
                RoomIn_A_Map = 5;
                HardnessMultiplier = 0;
                world.CreateWorld(RoomIn_A_Map);
                gameLogic.RandomRoomType(RoomIn_A_Map);
                player.setPlayer_attribute(PlayerType);
                //First time set up
                view.setCenter(world.SpawnPointPos.x, world.SpawnPointPos.y);
                player.setPlayerSpawnPos(world.SpawnPointPos.x, world.SpawnPointPos.y);
                weapon[0].init_Gun(std::string("Pistol"), player.collisionHitbox.getPosition().x, player.collisionHitbox.getPosition().y);
                weapon[1].init_Gun(gunType, player.collisionHitbox.getPosition().x, player.collisionHitbox.getPosition().y);
                for(i = 0; i < RoomIn_A_Map + 1; i++)
                {
                    if (gameLogic.roomType[i].compare("EnemyRoom") == 0)
                    {
                        gameLogic.SpawnEnemies(RoomIn_A_Map, Enemies, HardnessMultiplier, world.Field_Posi[i].Grid_col, world.Field_Posi[i].Grid_row);
                    }
                }
                portal.setupPortal(world.SpawnPoint_Posi.Grid_col, world.SpawnPoint_Posi.Grid_row, world.PortalRoom_Posi.Grid_col, world.PortalRoom_Posi.Grid_row);
                for(i = 0; i < RoomIn_A_Map + 1 ; i++)
                {
                    if (gameLogic.roomType[i].compare("ChestRoom") == 0)
                    {
                        gameLogic.SpawnChest(Chests, world.Field_Posi[i].Grid_col, world.Field_Posi[i].Grid_row);
                    }
                }
                init_gameplay = false;
            }
            else
            {
        if(player.current_Health == 0)
        {
            mode = GAMEOVER;
            toggleCLK = true;
        }
        //## GAME LOGIC process ##
        // Input Handle
            // NW NE SW SE
            //////////////////////////////////////////////////////////////////////////////////
            // Pre-Update
        mousePosi = window.mapPixelToCoords(mouse.getPosition(window));
        playerPosi = {player.collisionHitbox.getPosition().x, player.collisionHitbox.getPosition().y};
        current_PlayerPosi_RoomID = world.CurrentPlayerGrid(playerPosi.x, playerPosi.y, RoomIn_A_Map);
        player.setZeroVelocity();
        dt = dt_clock.reset(true).asSeconds(); // เอาเวลาระหว่างเฟรม
        if(mode == RUNNING)
        {
            AimDir = mousePosi - MiddleOfWin;
            AimDir_Normal = AimDir / static_cast<float>(sqrt(pow(AimDir.x, 2) + pow(AimDir.y, 2)));
            bullet_Timer = Timer_FireRate.getElapsedTime();
            if(current_PlayerPosi_RoomID == RoomIn_A_Map)
            {
                if(portal.isPlayerNearPortalOut(player.Hitbox.getPosition()))
                {
                    sfx.PortalActive.play();
                    player.current_Ammor = player.player_Ammor;
                    RoomCleared = (RoomCleared + 1) % 3;
                    if(RoomCleared == 2 && RoomIn_A_Map < 12)
                    {
                        RoomIn_A_Map += 1;
                    }
                    HardnessMultiplier += 1;
                    world.AllClear();
                    world.CreateWorld(RoomIn_A_Map);
                    gameLogic.RandomRoomType(RoomIn_A_Map);
                    Enemies.clear();
                    Chests.clear();
                    items.clear();
                    for(i = 0; i < RoomIn_A_Map ; i++)
                    {
                        if (gameLogic.roomType[i].compare("EnemyRoom") == 0)
                        {
                            gameLogic.SpawnEnemies(RoomIn_A_Map, Enemies, HardnessMultiplier, world.Field_Posi[i].Grid_col, world.Field_Posi[i].Grid_row);
                        }
                    }
                    view.setCenter(world.SpawnPointPos.x, world.SpawnPointPos.y);
                    player.setPlayerSpawnPos(world.SpawnPointPos.x, world.SpawnPointPos.y);
                    portal.setupPortal(world.SpawnPoint_Posi.Grid_col, world.SpawnPoint_Posi.Grid_row, world.PortalRoom_Posi.Grid_col, world.PortalRoom_Posi.Grid_row);
                    for(i = 0; i < RoomIn_A_Map + 1 ; i++)
                    {
                        if (gameLogic.roomType[i].compare("ChestRoom") == 0)
                        {
                            gameLogic.SpawnChest(Chests, world.Field_Posi[i].Grid_col, world.Field_Posi[i].Grid_row);
                        }
                    }
                }
            }   
            if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||  sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
            {   
                sfx.walking_Timer = sfx.walking_CLK.getElapsedTime();
   		        if(sfx.walking_Timer.asMilliseconds() > sfx.walkingbuffer.getDuration().asMilliseconds())
   		        {
			        sfx.walking.play();
			        sfx.walking_CLK.reset(true);
   		        }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    player.velocity.y += -(player.current_Speed * dt) / sqrt(2.f);
                    player.velocity.x += -(player.current_Speed * dt) / sqrt(2.f);
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    player.velocity.y += -(player.current_Speed * dt) / sqrt(2.f);
                    player.velocity.x +=  (player.current_Speed * dt) / sqrt(2.f);
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {   
                    player.velocity.y +=  (player.current_Speed * dt) / sqrt(2.f);
                    player.velocity.x += -(player.current_Speed * dt) / sqrt(2.f);
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {   
                    player.velocity.y +=  (player.current_Speed * dt) / sqrt(2.f);
                    player.velocity.x +=  (player.current_Speed * dt) / sqrt(2.f);
                }
                // NEWS
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    player.velocity.y += -player.current_Speed * dt;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    player.velocity.x += -player.current_Speed * dt;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    player.velocity.y += player.current_Speed * dt;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    player.velocity.x += player.current_Speed * dt;
                }
            }
            if(player.Skillcast(increaseFireRate))
            {
                sfx.castSkill.play();
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && bullet_Timer.asMilliseconds()*increaseFireRate > weapon[currentGun].FireRate && ((player.current_Energy - weapon[currentGun].Cost) >= 0))
            {
                Timer_FireRate.reset(true);
                weapon[currentGun].shotingOut(std::string(weapon[currentGun].it->first), AimDir_Normal.x, AimDir_Normal.y, bullets);
                if(weapon[currentGun].it->first.compare("Gatling Gun") == 0)
                {
                    player.velocity /= 3.f;
                }
                player.current_Energy -= weapon[currentGun].Cost;
            }
        
            //##UPDATE movement LOGIC##
                portal.update(dt);
                player.PlayerCollision(current_PlayerPosi_RoomID, world.Wall);
                if(items.size() > 0)
                {
                    for(auto *Element_item: items)
                    {
                        auto it_item = std::find(items.begin(), items.end(), Element_item);            
                        if(it_item != items.end())
                        {
                        if(Element_item->isItemPickedUp(player.Hitbox, player.current_Health, player.current_Energy, gunType))
                        {
                                if(Element_item->itemType.compare("Gun") == 0)
                                {
                                    weapon[1].init_Gun(gunType, player.collisionHitbox.getPosition().x, player.collisionHitbox.getPosition().y);
                                    pickedUp = true;
                                }
                                sfx.PickupItem.play();
                                items.erase(it_item);
                        }
                        }
                    }
                    if(pickedUp)
                    {
                        items.push_back(new ITEM(lastGun, player.Hitbox.getPosition().x,  player.Hitbox.getPosition().y));
                        pickedUp = false;
                    }
                }
                player.update(AimDir.x);
                weapon[0].update(playerPosi.x, playerPosi.y, AimDir_Normal.x, AimDir_Normal.y);
                weapon[1].update(playerPosi.x, playerPosi.y, AimDir_Normal.x, AimDir_Normal.y);
                view.setCenter(playerPosi.x, playerPosi.y);
                gui.isPauseButtonPressed(mousePosi.x, mousePosi.y, toggleCLK);
                gui.update(currentGun, weapon[0].GunTexture, weapon[1].GunTexture, player.CharModel, score, playerPosi.x, playerPosi.y, player.current_Health, player.current_Energy, player.player_Health, player.player_Energy, player.current_Ammor, player.player_Skill , player.Cooldown_Skill.asMilliseconds(), player.Cooldown);
                for(auto *Enemy: Enemies)
                {
                    auto it_enemy = std::find(Enemies.begin(), Enemies.end(), Enemy);
                    if(it_enemy != Enemies.end())
                    {
                        if(Enemy->Hitting(player.Hitbox))
                        {
                            if(player.current_Ammor > 0)
                            {
                                player.current_Ammor -= Enemy->Enemy_damage;
                                sfx.sheildBlock.play();
                            }
                            else
                            {
                                player.current_Health -= Enemy->Enemy_damage;
                                sfx.takeDamage.play();
                            }
                        }
                        Enemy->update(dt, world.CurrentEnemyGrid(Enemy->Position.x, Enemy->Position.y, RoomIn_A_Map), playerPosi, world.Wall);
                        if(Enemy->tiggerAlert)
                        {
                            sfx.EnemyAlert.play();
                        }
                        if(Enemy->Enemy_Health <= 0)
                        {
                            score += Enemy->Enemy_Score;
                            int RndPotionDrop = rand()%100 + 1;
                            if(RndPotionDrop%10 == 0)
                            {
                                items.push_back(new ITEM("EnergyPotion", Enemy->Position.x,  Enemy->Position.y));
                            }
                            Enemies.erase(it_enemy);
                            sfx.EnemyDeath.play();
                        }
                        bool hitcheck = false;
                        if(bullets.size() > 0)
                        {
                            for(auto *bullet: bullets)
                            {
                                auto it = std::find(bullets.begin(), bullets.end(), bullet);
                                if(it != bullets.end())
                                {
                                    if(Enemy->getHitted(bullet->bulletShape , bullets.size(), bullet->bulletDamage, player.current_Crit_Chance, weapon[currentGun].Crit))
                                    {
                                        if(!hitcheck)
                                        {
                                            hitcheck = true;
                                            sfx.EnemyPain.play();
                                        }
                                        bullets.erase(it);
                                    }
                                }
                            }
                        }
                    }
                }

                if(bullets.size() > 0)
                {
                    for(auto *bullet: bullets)
                    {
                        auto it = std::find(bullets.begin(), bullets.end(), bullet);
                        if(it != bullets.end())
                        {
                            bullet->update(dt);
                            if(bullet->bulletCollision(world.Wall) || bullet->bulletLifeTime())
                            {
                                sfx.bulletWallhit.play();
                                bullets.erase(it);
                            }
                        }
                    }
                }
                if(Chests.size() > 0)
                {
                    for(int i = 0; i < Chests.size(); i++)
                    {
                        Chests[i]->update(player.Hitbox.getPosition());
                        if(Chests[i]->SpawnItem)
                        {
                            sfx.Chestopen.play();
                            items.push_back(new ITEM((rand()%2 == 0? "Potion":"Gun"), Chests[i]->ChestSprite.getPosition().x,  Chests[i]->ChestSprite.getPosition().y - 5.f));
                            Chests[i]->SpawnItem = false;
                        }
                    }
                }
            lastGun = gunType;
            MenuSel = 0;
            }
        else if(mode == PAUSING)
        {
            int changer;
            pause.update(playerPosi.x, playerPosi.y, mousePosi.x, mousePosi.y, toggleCLK, changer);
            
            if(changer == 3)
            {
                mode = GAMEOVER;
            }
        } 
        else if(mode == GAMEOVER)
        {
            cal_score.update(playerPosi.x, playerPosi.y, mousePosi.x, mousePosi.y, toggleCLK, InGame, score);
            if(InGame == false)
            {
                cal_score.sorting(menu.playerNameContrainer, score);
                world.AllClear();
                Enemies.clear();
                Chests.clear();
                items.clear();
                cal_score.currentAnimation = 0;
                mode = RUNNING;
                MenuSel = 2;
            }
        }
            }
            //##Render##
            // clear old frame before render new one
                window.clear(sf::Color::Transparent);
                window.setView(view);

            // Draw game object
                //Draw Map and object first before draw the Entity
                for (x = 0; x < 9; x++)
                {
                    for(y = 0; y < 9; y++)
                    {
                        window.draw(world.TileMap[x][y]);
                    }
                }
                //Draw wall object
                for (auto &e_row: world.Wall)
                {
                    for (auto &e_col: e_row)
                    {
                        window.draw(e_col);
                    }
                }

                //Draw Chest
                if(Chests.size() > 0)
                {
                    for(int i = 0; i < Chests.size(); i++)
                    {
                        window.draw(Chests[i]->ChestSprite);
                    }
                }
                //draw Portal
                window.draw(portal.PortalIn);
                window.draw(portal.PortalOut);

                //draw player
                window.draw(player.CharModel);
                // window.draw(player.Hitbox);
                window.draw(weapon[currentGun].GunModel);

                //draw Item
                if(items.size() > 0)
                {
                    for(auto *Element_item: items)
                    {
                        window.draw(Element_item->ItemSprite);
                    }
                }

                //draw Enemies
                if(Enemies.size() > 0)
                {
                    for(auto *Enemy: Enemies)
                    {
                        auto it_enemy = std::find(Enemies.begin(), Enemies.end(), Enemy);            
                        if(it_enemy != Enemies.end())
                        {
                            if(EnableEnemiesCLK)
                            {
                                Enemy->ToggleCLK();
                            }
                            window.draw(Enemy->EnemySprite);
                        }
                        else
                        {
                            EnableEnemiesCLK = false;
                        }
                    }
                }
                //draw bullet
                if(bullets.size() > 0)
                {
                    for(auto *bullet: bullets)
                    {
                        window.draw(bullet->bulletShape);
                        //window.draw(bullet->bulletHitbox);
                    }
                }
                if(mode == RUNNING)
                {
                    window.draw(gui.currentGUI);
                }
                else if(mode == PAUSING)
                {
                    window.draw(pause.PauseSprite);
                }
                else if(mode == GAMEOVER)
                {
                    window.draw(cal_score.currentCAL_SCORE);
                }
                window.setView(window.getDefaultView());
            // Done Draw and Display
                window.display();
            }
        else if(!InGame && !InMenu)
        {
            InMenu = true;
            player.current_Ammor = player.player_Ammor;
            RoomIn_A_Map = 5;
            score = 0;
            HardnessMultiplier = 0;
            world.AllClear();
            Enemies.clear();
            Chests.clear();
            items.clear();
            gunType = "Pistol";
            menu.playerNameContrainer.clear();
        }
    }
    return 0;
}