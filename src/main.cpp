#include "MASTER.h"
#include "PLAYER.h"
#include "WORLD.h"

int main()
{   
    int x, y, i; //variable for Loop
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
    PLAYER player;

    //#player position
    sf::Vector2f playerPosi;

    //##Setup Window##
    sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHeight), "Let's Me Out: The Dungeon", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(setFPS);

    //Setup Icon
    sf::Image icon;
    icon.loadFromFile("Icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());  
    //

    // Setup View
    sf::View view;
    sf::Event ev;

    //Clock
    float dt;
    sf::Clock dt_clock;
    //##Setup Global Logic##
    world.Random_GRID(RoomIn_A_Map); // Should call first another METHOD
    world.SetupMAP();
    world.SetupRoom(RoomIn_A_Map);
    view.setSize(ScreenWidth/ScaleUp, ScreenHeight/ScaleUp);
    player.setPlayer_attribute();

    //First time set up
    view.setCenter(world.SpawnPointPos.x, world.SpawnPointPos.y);
    player.setPlayerSpawnPos(world.SpawnPointPos.x, world.SpawnPointPos.y);

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
        playerPosi = {player.Hitbox.getPosition().x, player.Hitbox.getPosition().y};
        current_PlayerPosi_RoomID = world.CurrentPlayerGrid(playerPosi.x, playerPosi.y, RoomIn_A_Map);

        player.setZeroVelocity();

        Frame7thCount++;
        dt = dt_clock.restart().asSeconds(); // เอาเวลาระหว่างเฟรม
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
                        if(ev.key.code == sf::Keyboard::Q)
                        {
                            printf("\n%d:(%d, %d)\n",current_PlayerPosi_RoomID , world.Field_Posi[current_PlayerPosi_RoomID].Grid_row, world.Field_Posi[current_PlayerPosi_RoomID].Grid_col);
                            printf("%.0lf, %.0lf\n", playerPosi.y,playerPosi.x);
                        }
                        if(ev.key.code == sf::Keyboard::R)
                        {
                            world.AllClear();
                            world.Random_GRID(RoomIn_A_Map); // Should call first another METHOD
                            world.SetupMAP();
                            world.SetupRoom(RoomIn_A_Map);
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
                                std::cout << "(" << world.Field_Posi[i].Grid_row << ", " << world.Field_Posi[i].Grid_col << ") ";
                                if (i == RoomIn_A_Map)
                                {
                                    std::cout << std::endl;
                                    std::cout << world.SpawnPoint_Posi.Grid_row << "," << world.SpawnPoint_Posi.Grid_col << std:: endl;
                                    std::cout << world.PortalRoom_Posi.Grid_row << "," << world.PortalRoom_Posi.Grid_col;
                                }
                            }
                            std :: cout << std::endl;
                        }
                        break;
                }
        }

        if(currentAnimation == 5) { currentAnimation = 0; }
        //## GAME LOGIC process ##
        // Input Handle
            // NW NE SW SE
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && isFaceDirChange)
        {
            isFaceDirChange = false;
            player.Hitbox.move(1.f, 0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !isFaceDirChange)
        {
            isFaceDirChange = true;
            player.Hitbox.move(-1.f, 0);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {   
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                player.velocity.y += -(movementSpeed * dt) / sqrt(2.f);
                player.velocity.x += -(movementSpeed * dt) / sqrt(2.f);
                faceDIR = -1;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                player.velocity.y += -(movementSpeed * dt) / sqrt(2.f);
                player.velocity.x +=  (movementSpeed * dt) / sqrt(2.f);
                faceDIR = 1;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {   
                player.velocity.y +=  (movementSpeed * dt) / sqrt(2.f);
                player.velocity.x += -(movementSpeed * dt) / sqrt(2.f);
                faceDIR = -1;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {   
                player.velocity.y +=  (movementSpeed * dt) / sqrt(2.f);
                player.velocity.x +=  (movementSpeed * dt) / sqrt(2.f);
                faceDIR = 1;
            }
            // NEWS
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                player.velocity.y += -movementSpeed * dt;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                player.velocity.x += -movementSpeed * dt;
                faceDIR = -1;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                player.velocity.y += movementSpeed * dt;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                player.velocity.x += movementSpeed * dt;
                faceDIR = 1;
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
    
        //##UPDATE LOGIC##
            world.PlayerCollision(playerPosi.x, playerPosi.y, current_PlayerPosi_RoomID, player.CharModel, player.Hitbox, player.velocity.x, player.velocity.y);
            player.movePlayer();
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

            window.draw(player.Hitbox);
            window.draw(player.CharModel);

            window.setView(window.getDefaultView());
        // Done Draw and Display
            window.display();
    }
    //delete window;
    return 0;
}