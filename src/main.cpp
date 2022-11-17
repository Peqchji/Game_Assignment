#include "MASTER.h"
#include "PLAYER.h"
#include "WORLD.h"
#include "GAMELOGIC.h"
#include "WEAPON.h"
#include "GUI.h"
#include "ITEM.h"

int Gameplay(sf::RenderWindow &window, sf::View &view, sf::Font &font1,  sf::Font &font2);
int main()
{   
    int gameState = 0;
    sf::Image icon;
    icon.loadFromFile("Icon.png");
    sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHeight), "Let's Me Out: The Dungeon", sf::Style::Titlebar | sf::Style::Close);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());  
    sf::View view;
    sf::Font font_V1;
    font_V1.loadFromFile("../content/GUI/MinimalPixelFont.ttf");
    sf::Font font_V2;
    font_V2.loadFromFile("../content/GUI/MinimalPixel v2.ttf");
    while(window.isOpen())
    {
        switch(gameState)
        {
            case 0:
                Gameplay(window, view, font_V1, font_V2);
                gameState = 2;
                break;
            default:
                window.close();
                break;
        }
    }
    return 0;
}
int Gameplay(sf::RenderWindow &window, sf::View &view, sf::Font &font1,  sf::Font &font2)
{
    int x, y, i;
    short RoomIn_A_Map = 5;
    short RoomCleared = 0;
    bool InGame = true;
    unsigned int score =  0;

    int current_PlayerPosi_RoomID;
    int room_id;

    WORLD world;
    GAMELOGIC gameLogic;

    PLAYER player;
    std::vector<ENEMY*> Enemies;
    float HardnessMultiplier = 0;

    std::vector<CHEST*> Chests;
    std::vector<BULLET*> bullets;
    std::vector<ITEM*> items;
    Portal portal;
    WEAPON weapon[2];

    GUI gui(font1, font2);
    
    //Timer
    sftools::Chronometer Timer_FireRate;
    Timer_FireRate.reset(true);
    sf::Time bullet_Timer;

    //MIDDLE of WINDOW
    sf::Vector2f MiddleOfWin(ScreenWidth/2.f, ScreenHeight/2.f);

    //#player position
    sf::Vector2f playerPosi;

    //##Setup Window##
    window.setFramerateLimit(setFPS);

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


    //##Setup Global Logic##
    world.CreateWorld(RoomIn_A_Map);
    gameLogic.RandomRoomType(RoomIn_A_Map);

    view.setSize(ScreenWidth/ScaleUp, ScreenHeight/ScaleUp);
    player.setPlayer_attribute("temp");

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
    //##GAME LOOP##
    while (InGame)
    {
        //event
        //////////////////////////////////DEBUGGING TOOL//////////////////////////////////
        while(window.pollEvent(ev))
        {
            switch(ev.type)
            {
                case sf::Event::Closed:
                    InGame = false;
                    break;
                /*case sf::Event::LostFocus:
                    break;*/
                case sf::Event::KeyPressed:
                    if(ev.key.code == sf::Keyboard::Escape)
                    { 
                       InGame = false;
                    }
                    if(ev.key.code == sf::Keyboard::R)
                    {
                        currentGun = (currentGun+1) % 2;
                    }
                    /*if(ev.key.code == (sf::Keyboard::Q))
                    {
                        Enemies.clear();
                        printf("\n%d:(%d, %d)\n",current_PlayerPosi_RoomID , world.Field_Posi[current_PlayerPosi_RoomID].Grid_row, world.Field_Posi[current_PlayerPosi_RoomID].Grid_col);
                        printf("%.0lf, %.0lf\n", playerPosi.x, playerPosi.y);
                        printf("%.2f %.2f | %.2f %.2f | %.2f %.2f\n", mousePosi.y, mousePosi.x, AimDir.x, AimDir.y, AimDir_Normal.x, AimDir_Normal.y);
                    }*/
                    break;
                default:
                    break;
            }
        }

        //## GAME LOGIC process ##
        // Input Handle
            // NW NE SW SE
        if(current_PlayerPosi_RoomID == RoomIn_A_Map)
        {
            if(portal.isPlayerNearPortalOut(player.Hitbox.getPosition()))
            {
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
        //////////////////////////////////////////////////////////////////////////////////
        // Pre-Update
        playerPosi = {player.collisionHitbox.getPosition().x, player.collisionHitbox.getPosition().y};
        current_PlayerPosi_RoomID = world.CurrentPlayerGrid(playerPosi.x, playerPosi.y, RoomIn_A_Map);
        player.setZeroVelocity();

        mousePosi = window.mapPixelToCoords(mouse.getPosition(window));
        AimDir = mousePosi - MiddleOfWin;
        AimDir_Normal = AimDir / static_cast<float>(sqrt(pow(AimDir.x, 2) + pow(AimDir.y, 2)));

        dt = dt_clock.reset(true).asSeconds(); // เอาเวลาระหว่างเฟรม
        bullet_Timer = Timer_FireRate.getElapsedTime();

        if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||  sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
        {   
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
        player.Skillcast(increaseFireRate);
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
            gui.update(currentGun, weapon[0].GunTexture, weapon[1].GunTexture, player.CharModel, score, playerPosi.x, playerPosi.y, player.current_Health, player.current_Energy, player.player_Health, player.player_Energy, player.current_Ammor, player.Cooldown_Skill.asMilliseconds(), player.Cooldown);
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
                        }
                        else
                        {
                            player.current_Health -= Enemy->Enemy_damage;
                        }
                    }
                    Enemy->update(dt, world.CurrentEnemyGrid(Enemy->Position.x, Enemy->Position.y, RoomIn_A_Map), playerPosi, world.Wall);
                    if(Enemy->Enemy_Health <= 0)
                    {
                        score += Enemy->Enemy_Score;
                        int RndPotionDrop = rand()%100 + 1;
                        if(RndPotionDrop%10 == 0)
                        {
                            items.push_back(new ITEM("EnergyPotion", Enemy->Position.x,  Enemy->Position.y));
                        }
                       Enemies.erase(it_enemy);
                    }
                    if(bullets.size() > 0)
                    {
                        for(auto *bullet: bullets)
                        {
                            auto it = std::find(bullets.begin(), bullets.end(), bullet);
                            if(it != bullets.end())
                            {
                                if(Enemy->getHitted(bullet->bulletShape , bullets.size(), bullet->bulletDamage, player.current_Crit_Chance, weapon[currentGun].Crit))
                                {
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
                        if(bullet->bulletCollision(world.Wall) || bullet->bulletLifeTime())
                        {
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
                        items.push_back(new ITEM((rand()%2 == 0? "Potion":"Gun"), Chests[i]->ChestSprite.getPosition().x,  Chests[i]->ChestSprite.getPosition().y - 5.f));
                        Chests[i]->SpawnItem = false;
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
                       window.draw(Enemy->EnemySprite);
                    }
                    
                }
            }
            //draw bullet
            if(bullets.size() > 0)
            {
                for(auto *bullet: bullets)
                {
                    bullet->update(dt);
                    window.draw(bullet->bulletShape);
                    //window.draw(bullet->bulletHitbox);
                }
            }

            window.draw(gui.currentGUI);
            window.setView(window.getDefaultView());
        // Done Draw and Display
            window.display();

            lastGun = gunType;
    }
    return 0;
}