#include "MASTER.h"
#include "PLAYER.h"
#include "WORLD.h"
#include "GAMELOGIC.h"
#include "WEAPON.h"


int Gameplay(sf::RenderWindow &window, sf::View &view);
int main()
{   
    int gameState = 0;
    sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHeight), "Let's Me Out: The Dungeon", sf::Style::Titlebar | sf::Style::Close);
    sf::View view;
    switch(gameState)
    {
        case 0:
        Gameplay(window, view);
            break;
        default:
            break;
    }
    return 0;
}

int Gameplay(sf::RenderWindow &window, sf::View &view)
{
    int x, y, i;
    short RoomIn_A_Map = 5;
    int currentAnimation = 0;
    float Frame7thCount = 0;
    bool InGame = true;

    bool isFaceDirChange = true;
    short faceDIR = 1;
    short IdleLeft;

    short PlayerAnimationFrame = static_cast<int>(setFPS/8);
    int current_PlayerPosi_RoomID;
    WORLD world;
    GAMELOGIC gameLogic;

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

    //Clock
    float dt;
    sf::Clock dt_clock;


    //##Setup Global Logic##
    world.Random_GRID(RoomIn_A_Map); // Should call first another METHOD
    world.SetupMAP();
    world.SetupRoom(RoomIn_A_Map);
    gameLogic.RandomRoomType(RoomIn_A_Map);

    view.setSize(ScreenWidth/ScaleUp, ScreenHeight/ScaleUp);
    player.setPlayer_attribute();

    //First time set up
    view.setCenter(world.SpawnPointPos.x, world.SpawnPointPos.y);
    player.setPlayerSpawnPos(world.SpawnPointPos.x, world.SpawnPointPos.y);

    weapon[0].init_Gun(gunType, player.collisionHitbox.getPosition().x, player.collisionHitbox.getPosition().y);

    for (y = 0; y < 9; y++)//row
        {
            for(x = 0; x < 9; x++)//col
            {
                std::cout << world.MAP_MATRIX[y][x] << " ";
            }
            std::cout << std::endl;
        }
    
    //##GAME LOOP##
    while (window.isOpen())
    {
        // Pre-Update
        currentAnimation %= 5;
        playerPosi = {player.collisionHitbox.getPosition().x, player.collisionHitbox.getPosition().y};
        current_PlayerPosi_RoomID = world.CurrentPlayerGrid(playerPosi.x, playerPosi.y, RoomIn_A_Map);
        player.setZeroVelocity();

        mousePosi = window.mapPixelToCoords(mouse.getPosition(window));
        AimDir = mousePosi - MiddleOfWin;
        AimDir_Normal = AimDir / static_cast<float>(sqrt(pow(AimDir.x, 2) + pow(AimDir.y, 2)));

        Frame7thCount++;
        dt = dt_clock.restart().asSeconds(); // เอาเวลาระหว่างเฟรม
        bullet_Timer = Timer_FireRate.getElapsedTime();

        //event
        while(window.pollEvent(ev))
        {
                switch(ev.type)
                {
                    case sf::Event::Closed :
                        window.close();
                        break;
                    case sf::Event::KeyPressed :
                        if(ev.key.code == sf::Keyboard::Escape)
                            window.close();
                        break;
                }
        }

        //## GAME LOGIC process ##
        // Input Handle
            // NW NE SW SE

        //////////////////////////////////DEBUGGING TOOL//////////////////////////////////
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            printf("\n%d:(%d, %d)\n",current_PlayerPosi_RoomID , world.Field_Posi[current_PlayerPosi_RoomID].Grid_row, world.Field_Posi[current_PlayerPosi_RoomID].Grid_col);
            printf("%.0lf, %.0lf\n", playerPosi.y, playerPosi.x);
            printf("%.2f %.2f | %.2f %.2f | %.2f %.2f\n", mousePosi.y, mousePosi.x, AimDir.x, AimDir.y, AimDir_Normal.x, AimDir_Normal.y);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            faceDIR = 1;
            isFaceDirChange = true;
            world.AllClear();
            world.Random_GRID(RoomIn_A_Map); // Should call first another METHOD
            world.SetupMAP();
            world.SetupRoom(RoomIn_A_Map);
            gameLogic.RandomRoomType(RoomIn_A_Map);
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
        }
        //////////////////////////////////////////////////////////////////////////////////

        faceDIR = (AimDir.x < 0)? -1: 1;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
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

            IdleLeft = faceDIR == -1? 1: 0;
            if(Frame7thCount == PlayerAnimationFrame)
            {
                player.CharModel.setTextureRect(sf::IntRect((player.textureSize.x)*(currentAnimation + 3 + IdleLeft), 0, (player.textureSize.x)*faceDIR, (player.textureSize.y)));
                currentAnimation++;
                Frame7thCount = 0;
            }  
        }
        else
        {
            IDLE:
            if(Frame7thCount == PlayerAnimationFrame)
            {
                IdleLeft = faceDIR == -1? 1: 0;
                player.CharModel.setTextureRect(sf::IntRect((player.textureSize.x)*(currentAnimation + IdleLeft), 0, (player.textureSize.x)*faceDIR, (player.textureSize.y)));
                currentAnimation++;
                Frame7thCount = 0;
            }
        }

         if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && bullet_Timer.asMilliseconds() > weapon[0].FireRate)
        {
            Timer_FireRate.restart();
            gunType = "Shotgun";
            weapon[0].shotingOut(gunType, AimDir_Normal.x, AimDir_Normal.y, bullets);
            gameLogic.SpawnEnemies(RoomIn_A_Map, Enemies, playerPosi.x, playerPosi.y);
        }
    
        //##UPDATE movement LOGIC##
            player.PlayerCollision(current_PlayerPosi_RoomID, world.Wall);
            player.movePlayer();
            weapon[0].update(playerPosi.x, playerPosi.y, AimDir_Normal.x, AimDir_Normal.y);
            view.setCenter(playerPosi.x, playerPosi.y);

        //##Render##
        // clear old frame before render new one
            window.clear(sf::Color::Black);
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
            //draw player
            //window.draw(player.collisionHitbox);
            window.draw(player.CharModel);
            window.draw(weapon[0].GunModel);
            //draw bullet
           for(auto *bullet: bullets)
            {
                bullet->update(dt);
                if(bullet->bulletCollision(world.Wall) && bullets.size() > 0)
                {
                    auto it = std::find(bullets.begin(), bullets.end(), bullet);
                    if(it != bullets.end())
                        bullets.erase(it);
                }
                window.draw(bullet->bulletShape);
            }
            //draw Enemies
            for(auto *Enemy: Enemies)
            {
                auto it_enemy = std::find(Enemies.begin(), Enemies.end(), Enemy);
                {
                    if(it_enemy != Enemies.end())
                    {
                        Enemy->update();
                        window.draw(Enemy->EnemySprite);
                    }
                }
            }

            window.setView(window.getDefaultView());
        // Done Draw and Display
            window.display();
    }
    return 0;
}