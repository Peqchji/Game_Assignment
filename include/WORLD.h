#ifndef WORLD_H
#define WORLD_H

#include "MASTER.h"
class WORLD
{
	public:
		short **MAP_MATRIX;
		sf::Vector2f SpawnPointPos;
		sf::RectangleShape TileMap[9][9];
		std::vector<std::vector<sf::RectangleShape>> Wall;
		struct Posi_InMap
		{
			short Grid_row;
			short Grid_col;
		}SpawnPoint_Posi, PortalRoom_Posi, Near_Grid_Contrain[4], Current_Grid_Posi, *Field_Posi;
		
		WORLD();
		~WORLD();
		void CreateWorld(short &Amount);
		int CurrentEnemyGrid(float Pos_x, float Pos_y, short Amount_of_Room);
		int CurrentPlayerGrid(float Pos_x, float Pos_y, short Amount_of_Room);
		void PlayerCollision(float Pos_x, float Pos_y, short currentRoom, sf::RectangleShape &playerModel, sf::RectangleShape &playerHitbox, float &velo_X,  float &velo_Y);
		void Random_GRID(short);
		void SetupMAP();
		void SetupRoom(short Amount_of_room);
		void SetupWall(short, short, short);

		void AllClear();
	private:
		sf::RectangleShape Wall_HitBox15[3];
		sf::RectangleShape WallBottom[2];
		sf::RectangleShape WallLeft[2];
		sf::RectangleShape WallRight[2];
		sf::RectangleShape WallTop[2];
		
									 //0	  1	 	 2		3
		bool RoomGateway_Check[4] = {false, false, false, false};
		/*
				- 0 Top
				- 1 Right
				- 2 Bottom
				- 3 Left
		*/
		sf::Texture RoomTexture[15];
		sf::Texture WallTexture[11];

		// มีการใช้หลายครั้งนะอย่าลืม
		/*
			1.rand map
			2. setup โหลดแมพ
		*/

		void FloorLoader();
		void WallLoader();
		void SetupWallHitbox();
		
		// Clearing
		void TileMAPClear();
		void WallClear();
		
};

#endif