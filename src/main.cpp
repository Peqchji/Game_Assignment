#include "MASTER.h"
#include "PLAYER.h"
#include "WORLD.h"
#include "GAMELOGIC.h"
#include "WEAPON.h"
#include "GUI.h"

int Gameplay(sf::RenderWindow &window, sf::View &view);
int main()
{   
    int gameState = 0;
    sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHeight), "Let's Me Out: The Dungeon", sf::Style::Titlebar | sf::Style::Close);
    sf::View view;
    while(window.isOpen())
    {
        switch(gameState)
        {
            case 0:
                Gameplay(window, view);
                gameState = 2;
                break;
            default:
                window.close();
                break;
        }
    }
    return 0;
}

int Gameplay(sf::RenderWindow &window, sf::View &view)
{
    int x, y, i;
    short RoomIn_A_Map = 5;
    bool InGame = true;
    int score = 0;

    int current_PlayerPosi_RoomID;
    int room_id;

    WORLD world;
    Portal portal;
    GAMELOGIC gameLogic;
    GUI gui;

    PLAYER player;
    std::vector<ENEMY*> Enemies;

    std::vector<BULLET*> bullets;
    WEAPON weapon[2];
    
    //Timer
    sf::Clock Timer_FireRate;
    Timer_FireRate.restart();
    sf::Time bullet_Timer;

    //MIDDLE of WINDOW
    sf::Vector2f MiddleOfWin(ScreenWidth/2.f, ScreenHeight/2.f);

    //#player position
    sf::Vector2f playerPosi;

    //##Setup Window##
    window.setFramerateLimit(setFPS);

    //Setup Icon
    sf::Image icon;
    icon.loadFromFile("Icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());  

    // Setup View
    sf::Event ev;

    // mouse position and aiming
    sf::Mouse mouse;
    sf::Vector2f mousePosi;
    sf::Vector2f AimDir;
    sf::Vector2f AimDir_Normal;    
    std::string gunType = "Shotgun";
    int currentGun = 0;

    //Clock
    float dt;
    sf::Clock dt_clock;


    //##Setup Global Logic##
    world.Random_GRID(RoomIn_A_Map); // Should call first another METHOD
    world.SetupMAP();
    world.SetupRoom(RoomIn_A_Map);
    gameLogic.RandomRoomType(RoomIn_A_Map);

    view.setSize(ScreenWidth/ScaleUp, ScreenHeight/ScaleUp);
    player.setPlayer_attribute("temp");

    //First time set up
    view.setCenter(world.SpawnPointPos.x, world.SpawnPointPos.y);
    player.setPlayerSpawnPos(world.SpawnPointPos.x, world.SpawnPointPos.y);

    weapon[0].init_Gun(gunType, player.collisionHitbox.getPosition().x, player.collisionHitbox.getPosition().y);

    for(i = 0; i < RoomIn_A_Map ; i++)
    {
        if (gameLogic.roomType[i].compare("EnemyRoom") == 0)
        {
            gameLogic.SpawnEnemies(RoomIn_A_Map, Enemies, world.Field_Posi[i].Grid_col, world.Field_Posi[i].Grid_row);
        }
    }

    portal.setupPortal(world.Field_Posi[0].Grid_col, world.Field_Posi[0].Grid_row, world.Field_Posi[RoomIn_A_Map].Grid_col, world.Field_Posi[RoomIn_A_Map].Grid_row);

    //##GAME LOOP##
    while (InGame)
    {
        // Pre-Update
        playerPosi = {player.collisionHitbox.getPosition().x, player.collisionHitbox.getPosition().y};
        current_PlayerPosi_RoomID = world.CurrentPlayerGrid(playerPosi.x, playerPosi.y, RoomIn_A_Map);
        player.setZeroVelocity();

        mousePosi = window.mapPixelToCoords(mouse.getPosition(window));
        AimDir = mousePosi - MiddleOfWin;
        AimDir_Normal = AimDir / static_cast<float>(sqrt(pow(AimDir.x, 2) + pow(AimDir.y, 2)));

        dt = dt_clock.restart().asSeconds(); // เอาเวลาระหว่างเฟรม
        bullet_Timer = Timer_FireRate.getElapsedTime();

        //event
        //////////////////////////////////DEBUGGING TOOL//////////////////////////////////
        while(window.pollEvent(ev))
        {
            switch(ev.type)
            {
                case sf::Event::Closed :
                    InGame = false;
                    break;
                case sf::Event::KeyPressed:
                    if(ev.key.code == sf::Keyboard::Escape)
                        InGame = false;
                    if(ev.key.code == sf::Keyboard::P)
                    {
                        currentGun = (currentGun+1) % weapon[0].GunType.size();
                        std::map<std::string, struct GunAttribute>::iterator it;
                        auto key = weapon[0].GunType.begin();
                        std::advance(key, currentGun);
                        gunType = key->first;
                        weapon[0].init_Gun(gunType, playerPosi.x, playerPosi.y);
                    }
                default:
                    break;
            }
        }

        //## GAME LOGIC process ##
        // Input Handle
            // NW NE SW SE
        if(sf::Keyboard::isKeyPressed (sf::Keyboard::Q))
        {
            Enemies.clear();
            printf("\n%d:(%d, %d)\n",current_PlayerPosi_RoomID , world.Field_Posi[current_PlayerPosi_RoomID].Grid_row, world.Field_Posi[current_PlayerPosi_RoomID].Grid_col);
            printf("%.0lf, %.0lf\n", playerPosi.y, playerPosi.x);
            printf("%.2f %.2f | %.2f %.2f | %.2f %.2f\n", mousePosi.y, mousePosi.x, AimDir.x, AimDir.y, AimDir_Normal.x, AimDir_Normal.y);
        }
        if(sf::Keyboard::isKeyPressed (sf::Keyboard::R))
        {
            world.AllClear();
            world.Random_GRID(RoomIn_A_Map); // Should call first another METHOD
            world.SetupMAP();
            world.SetupRoom(RoomIn_A_Map);
            gameLogic.RandomRoomType(RoomIn_A_Map);
            Enemies.clear();
            for(i = 0; i < RoomIn_A_Map ; i++)
            {
                if (gameLogic.roomType[i].compare("EnemyRoom") == 0)
                {
                    gameLogic.SpawnEnemies(RoomIn_A_Map, Enemies, world.Field_Posi[i].Grid_col, world.Field_Posi[i].Grid_row);
                }
            }
            view.setCenter(world.SpawnPointPos.x, world.SpawnPointPos.y);
            player.setPlayerSpawnPos(world.SpawnPointPos.x, world.SpawnPointPos.y);
            printf("\nNew MAP Created\n");
            for (y = 0; y < 9; y++)//row
            {
                for(x = 0; x <9; x++)//col
                {
                    std::cout << world.MAP_MATRIX[y][x] << " ";
                }
                std::cout << std::endl;
            }
            for(i = 0; i < RoomIn_A_Map + 1; i++)
            {
                std::cout << gameLogic.roomType[i] ;
                std::cout << "(" << world.Field_Posi[i].Grid_row << ", " << world.Field_Posi[i].Grid_col << ") ";
                std :: cout << std::endl;
            }
            std :: cout << std::endl;
                portal.setupPortal(world.Field_Posi[0].Grid_col, world.Field_Posi[0].Grid_row, world.Field_Posi[RoomIn_A_Map].Grid_col, world.Field_Posi[RoomIn_A_Map].Grid_row);
        }
        //////////////////////////////////////////////////////////////////////////////////

        if(sf::Event::KeyPressed)
        {   
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                player.velocity.y += -(movementSpeed * dt) / sqrt(2.f);
                player.velocity.x += -(movementSpeed * dt) / sqrt(2.f);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                player.velocity.y += -(movementSpeed * dt) / sqrt(2.f);
                player.velocity.x +=  (movementSpeed * dt) / sqrt(2.f);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {   
                player.velocity.y +=  (movementSpeed * dt) / sqrt(2.f);
                player.velocity.x += -(movementSpeed * dt) / sqrt(2.f);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {   
                player.velocity.y +=  (movementSpeed * dt) / sqrt(2.f);
                player.velocity.x +=  (movementSpeed * dt) / sqrt(2.f);
            }
            // NEWS
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                player.velocity.y += -movementSpeed * dt;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                player.velocity.x += -movementSpeed * dt;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                player.velocity.y += movementSpeed * dt;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                player.velocity.x += movementSpeed * dt;
            }
        }
         if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && bullet_Timer.asMilliseconds() > weapon[0].FireRate && ((player.current_Energy - weapon[0].Cost) >= 0))
        {
            Timer_FireRate.restart();
            weapon[0].shotingOut(gunType, AimDir_Normal.x, AimDir_Normal.y, bullets);
            player.current_Energy -= weapon[0].Cost;
        }
    
        //##UPDATE movement LOGIC##
            portal.update(dt);
            player.PlayerCollision(current_PlayerPosi_RoomID, world.Wall);
            player.update(AimDir.x);
            weapon[0].update(playerPosi.x, playerPosi.y, AimDir_Normal.x, AimDir_Normal.y);
            view.setCenter(playerPosi.x, playerPosi.y);
            gui.update(playerPosi.x, playerPosi.y, player.current_Health, player.current_Energy, player.player_Health, player.player_Energy, player.player_Crit_Chance);
            for(auto *Enemy: Enemies)
            {
                auto it_enemy = std::find(Enemies.begin(), Enemies.end(), Enemy);
                if(it_enemy != Enemies.end())
                {
                    if(Enemy->Enemy_Health <= 0)
                    {
                        score += Enemy->Enemy_Score;
                        printf("score: %d", score);
                       Enemies.erase(it_enemy);
                    }
                    for(auto *bullet: bullets)
                    {
                        auto it = std::find(bullets.begin(), bullets.end(), bullet);
                        if(it != bullets.end())
                        {
                            if(Enemy->getHitted(bullet->bulletShape , bullets.size(), bullet->bulletDamage) 
                            || ((bullet->bulletCollision(world.Wall) || bullet->bulletLifeTime()) && bullets.size() > 0))
                            {
                                bullets.erase(it);
                            }
                        }
                    }
                    Enemy->update(dt, world.CurrentEnemyGrid(Enemy->Position.x, Enemy->Position.y, RoomIn_A_Map), playerPosi, world.Wall);
                    for(auto *otherEntity: Enemies)
                    {
                        auto it_Entity = std::find(Enemies.begin(), Enemies.end(), otherEntity);
                        if (it_enemy == it_Entity)
                        {
                            continue;
                        }
                        if(it_Entity != Enemies.end())
                        {
                            Enemy->AntiOverlap(otherEntity->EnemyHitbox);
                        }
                    }
                }
            }

            if(current_PlayerPosi_RoomID == RoomIn_A_Map)
            {
                portal.isPlayerNearPortalOut(player.Hitbox.getPosition());
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
            //draw Portal
            window.draw(portal.PortalIn);
            window.draw(portal.PortalOut);
            //draw player
            window.draw(player.CharModel);
           // window.draw(player.Hitbox);
            window.draw(weapon[0].GunModel);

            //draw Enemies
            for(auto *Enemy: Enemies)
            {
                auto it_enemy = std::find(Enemies.begin(), Enemies.end(), Enemy);
                {
                    if(it_enemy != Enemies.end())
                    {
                        window.draw(Enemy->EnemySprite);
                        window.draw(Enemy->EnemyHitbox);
                    }
                }
            }
            //draw bullet
            for(auto *bullet: bullets)
            {
                bullet->update(dt);
                window.draw(bullet->bulletShape);
            }

            window.draw(gui.currentGUI);
            window.setView(window.getDefaultView());
        // Done Draw and Display
            window.display();
    }
    return 0;
}