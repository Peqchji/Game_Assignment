#include "WORLD.h"
// Construct
WORLD::WORLD()
{
	FloorLoader();
	WallLoader();
	SetupWallHitbox();
}
//destruct
WORLD::~WORLD()
{
	free(Field_Posi);
	free(MAP_MATRIX);
}

//All world setting clear
void WORLD::AllClear()
{
	WallClear();
	TileMAPClear();
}

//Room setting
void WORLD::SetupRoom(short Amount_of_room)
{
	short Gateway_count = 0;
	int i, k;
	for(i = 0; i < Amount_of_room + 1; i++) //row
	{
		// Contrain current grid position(grid matrix)
		Current_Grid_Posi.Grid_row = Field_Posi[i].Grid_row;
		Current_Grid_Posi.Grid_col = Field_Posi[i].Grid_col;
			
		// Contrain Nearby grid position(grid matrix) 
		for(k = 0; k < 4; k++)
		{
			Near_Grid_Contrain[k].Grid_row = Current_Grid_Posi.Grid_row - (pow(-1, (k / 2)) * (-1 * ((k % 2) - 1)));
			Near_Grid_Contrain[k].Grid_col = Current_Grid_Posi.Grid_col + (pow(-1, static_cast<short>(k / 2)) * (k % 2));
		}
		// Check nearby grid
		for(k = 0; k < 4; k++)
		{
				if(MAP_MATRIX[Near_Grid_Contrain[k].Grid_row][Near_Grid_Contrain[k].Grid_col] == 1)
					{ RoomGateway_Check[k] = true ; }
				else if (MAP_MATRIX[Near_Grid_Contrain[k].Grid_row][Near_Grid_Contrain[k].Grid_col] == 0)
					{ RoomGateway_Check[k] = false; }
			}
			for(k = 0; k < 4; k++)
			{
				if(RoomGateway_Check[k] == true)
				{
					Gateway_count++;
				}
			}
			/* Gateway_count =
			- 0 Top
			- 1 Right
			- 2 Bottom
			- 3 Left
			*/
			switch(Gateway_count)
			{
				case 1:
					// 0
					if(RoomGateway_Check[0] == true && RoomGateway_Check[1] == false &&  RoomGateway_Check[2] == false && RoomGateway_Check[3] == false)
					{
						this->TileMap[Field_Posi[i].Grid_row][Field_Posi[i].Grid_col].setTexture(&RoomTexture[0]);
						SetupWall(Field_Posi[i].Grid_row, Field_Posi[i].Grid_col, 0);
					}
					// 1
					else if(RoomGateway_Check[0] == false && RoomGateway_Check[1] == true &&  RoomGateway_Check[2] == false && RoomGateway_Check[3] == false)
					{
						this->TileMap[Field_Posi[i].Grid_row][Field_Posi[i].Grid_col].setTexture(&RoomTexture[1]);
						SetupWall(Field_Posi[i].Grid_row, Field_Posi[i].Grid_col, 1);
					}
					// 2
					else if(RoomGateway_Check[0] == false && RoomGateway_Check[1] == false &&  RoomGateway_Check[2] == true && RoomGateway_Check[3] == false)
					{
						this->TileMap[Field_Posi[i].Grid_row][Field_Posi[i].Grid_col].setTexture(&RoomTexture[2]);
						SetupWall(Field_Posi[i].Grid_row, Field_Posi[i].Grid_col, 2);
					}
					// 3
					else if(RoomGateway_Check[0] == false && RoomGateway_Check[1] == false &&  RoomGateway_Check[2] == false && RoomGateway_Check[3] == true)
					{
						this->TileMap[Field_Posi[i].Grid_row][Field_Posi[i].Grid_col].setTexture(&RoomTexture[3]);
						SetupWall(Field_Posi[i].Grid_row, Field_Posi[i].Grid_col, 3);
					}
					break;
				case 2:
					// 0 2
					if(RoomGateway_Check[0] == true && RoomGateway_Check[1] == false && RoomGateway_Check[2] == true && RoomGateway_Check[3] == false)
					{
						this->TileMap[Field_Posi[i].Grid_row][Field_Posi[i].Grid_col].setTexture(&RoomTexture[4]);
						SetupWall(Field_Posi[i].Grid_row, Field_Posi[i].Grid_col, 4);
					}
					// 1 3
					else if(RoomGateway_Check[0] == false && RoomGateway_Check[1] == true && RoomGateway_Check[2] == false && RoomGateway_Check[3] == true)
					{
						this->TileMap[Field_Posi[i].Grid_row][Field_Posi[i].Grid_col].setTexture(&RoomTexture[5]);
						SetupWall(Field_Posi[i].Grid_row, Field_Posi[i].Grid_col, 5);
					}
					// 0 1
					else if(RoomGateway_Check[0] == true && RoomGateway_Check[1] == true && RoomGateway_Check[2] == false && RoomGateway_Check[3] == false)
					{
						// Flip horizonal
						this->TileMap[Field_Posi[i].Grid_row][Field_Posi[i].Grid_col].setTexture(&RoomTexture[6]);
						SetupWall(Field_Posi[i].Grid_row, Field_Posi[i].Grid_col, 6);
					}
					// 0 3
					else if(RoomGateway_Check[0] == true && RoomGateway_Check[1] == false && RoomGateway_Check[2] == false && RoomGateway_Check[3] == true)
					{
						this->TileMap[Field_Posi[i].Grid_row][Field_Posi[i].Grid_col].setTexture(&RoomTexture[7]);
						SetupWall(Field_Posi[i].Grid_row, Field_Posi[i].Grid_col, 7);
					}
					// 2 1
					else if(RoomGateway_Check[0] == false && RoomGateway_Check[1] == true && RoomGateway_Check[2] == true && RoomGateway_Check[3] == false)
					{
						this->TileMap[Field_Posi[i].Grid_row][Field_Posi[i].Grid_col].setTexture(&RoomTexture[8]);
						SetupWall(Field_Posi[i].Grid_row, Field_Posi[i].Grid_col, 8);
					}
					// 2 3
					else if(RoomGateway_Check[0] == false && RoomGateway_Check[1] == false && RoomGateway_Check[2] == true && RoomGateway_Check[3] == true)
					{
						this->TileMap[Field_Posi[i].Grid_row][Field_Posi[i].Grid_col].setTexture(&RoomTexture[9]);
						SetupWall(Field_Posi[i].Grid_row, Field_Posi[i].Grid_col, 9);
					}
					break;
				case 3:
					// 0 1 3
					if(RoomGateway_Check[0] == true && RoomGateway_Check[1] == true && RoomGateway_Check[2] == false && RoomGateway_Check[3] == true)
					{
						this->TileMap[Field_Posi[i].Grid_row][Field_Posi[i].Grid_col].setTexture(&RoomTexture[10]);
						SetupWall(Field_Posi[i].Grid_row, Field_Posi[i].Grid_col, 10);
					}
					// 0 2 3
					else if(RoomGateway_Check[0] == true && RoomGateway_Check[1] == true && RoomGateway_Check[2] == true && RoomGateway_Check[3] == false)
					{
						this->TileMap[Field_Posi[i].Grid_row][Field_Posi[i].Grid_col].setTexture(&RoomTexture[11]);
						SetupWall(Field_Posi[i].Grid_row, Field_Posi[i].Grid_col, 11);
					}
					// 1 2 3
					else if(RoomGateway_Check[0] == false && RoomGateway_Check[1] == true && RoomGateway_Check[2] == true && RoomGateway_Check[3] == true)
					{
						this->TileMap[Field_Posi[i].Grid_row][Field_Posi[i].Grid_col].setTexture(&RoomTexture[12]);
						SetupWall(Field_Posi[i].Grid_row, Field_Posi[i].Grid_col, 12);
					}
					// 0 1 2
					else if(RoomGateway_Check[0] == true && RoomGateway_Check[1] == false && RoomGateway_Check[2] == true && RoomGateway_Check[3] == true)
					{
						this->TileMap[Field_Posi[i].Grid_row][Field_Posi[i].Grid_col].setTexture(&RoomTexture[13]);
						SetupWall(Field_Posi[i].Grid_row, Field_Posi[i].Grid_col, 13);
					}
					break;
				default:
					this->TileMap[Field_Posi[i].Grid_row][Field_Posi[i].Grid_col].setTexture(&RoomTexture[14]);
						SetupWall(Field_Posi[i].Grid_row, Field_Posi[i].Grid_col, 14);
					break;
			}
		Gateway_count = 0;
		}
}

//setup and clear
void WORLD::SetupMAP()
{
	int y, x;
	for (y = 0; y < 9; y++)
	{
		for(x = 0; x < 9; x++)
		{
				if(MAP_MATRIX[y][x] == 1)
				{
					//Assign Room size and scale
					this->TileMap[y][x].setSize(sf::Vector2f(::GridPixelSize, ::GridPixelSize));
					this->TileMap[y][x].setFillColor(sf::Color::White);
					this->TileMap[y][x].setPosition(x*::GridPixelSize, y*::GridPixelSize); //col, row


				}
		}
	}
}
void WORLD::TileMAPClear()
{
	int x, y;
	for (y = 0; y < 9; y++)
	{
		for(x = 0; x < 9; x++)
		{
			if(MAP_MATRIX[y][x] == 1)
				{
					this->TileMap[y][x].setSize(sf::Vector2f(::GridPixelSize, ::GridPixelSize));
					this->TileMap[y][x].setFillColor(sf::Color::Transparent);
					this->TileMap[y][x].setPosition(x*::GridPixelSize, y*::GridPixelSize); //col, row
				}
		}
	}
}

//Floor
void WORLD::FloorLoader()
{		//ลบifด้วย เขียนไว้แก้บัคเฉยๆ
		if(!this->RoomTexture[0].loadFromFile("../content/map/FLOOR/1DirRoom_Top.png"))			printf("Loading 1DirRoom_Top			Failed");
		if(!this->RoomTexture[1].loadFromFile("../content/map/FLOOR/1DirRoom_Right.png"))		printf("Loading 1DirRoom_Right			Failed");
		if(!this->RoomTexture[2].loadFromFile("../content/map/FLOOR/1DirRoom_Bottom.png"))		printf("Loading 1DirRoom_Bottom			Failed");
		if(!this->RoomTexture[3].loadFromFile("../content/map/FLOOR/1DirRoom_Left.png"))		printf("Loading 1DirRoom_Left	 		Failed");
		if(!this->RoomTexture[4].loadFromFile("../content/map/FLOOR/2DirRoom_TopBottom.png"))	printf("Loading 2DirRoom_TopBottom		Failed");
		if(!this->RoomTexture[5].loadFromFile("../content/map/FLOOR/2DirRoom_Side.png"))		printf("Loading 2DirRoom_Side	 		Failed");
		if(!this->RoomTexture[6].loadFromFile("../content/map/FLOOR/2DirRoom_RightTop.png"))	printf("Loading 2DirRoom_RightTop		Failed");
		if(!this->RoomTexture[7].loadFromFile("../content/map/FLOOR/2DirRoom_LeftTop.png"))		printf("Loading 2DirRoom_LeftTop		Failed");
		if(!this->RoomTexture[8].loadFromFile("../content/map/FLOOR/2DirRoom_RightBottom.png"))	printf("Loading 2DirRoom_RightBottom	Failed");
		if(!this->RoomTexture[9].loadFromFile("../content/map/FLOOR/2DirRoom_LeftBottom.png"))	printf("Loading 2DirRoom_LeftBottom	 	Failed");
		if(!this->RoomTexture[10].loadFromFile("../content/map/FLOOR/3DirRoom_Top.png"))		printf("Loading 3DirRoom_Top	 		Failed");
		if(!this->RoomTexture[11].loadFromFile("../content/map/FLOOR/3DirRoom_Right.png"))		printf("Loading 3DirRoom_Right	 		Failed");
		if(!this->RoomTexture[12].loadFromFile("../content/map/FLOOR/3DirRoom_Bottom.png"))		printf("Loading 3DirRoom_Bottom	 		Failed");
		if(!this->RoomTexture[13].loadFromFile("../content/map/FLOOR/3DirRoom_Left.png"))		printf("Loading 3DirRoom_Left	 		Failed");
		if(!this->RoomTexture[14].loadFromFile("../content/map/FLOOR/4DirRoom.png"))			printf("Loading 4DirRoom	 			Failed");
}

//Wall
void WORLD::WallLoader()
{
	this->WallTexture[0].loadFromFile("../content/map/WALL/Wall_hori15.png");			
	this->WallTexture[1].loadFromFile("../content/map/WALL/Wall_right15.png");			
	this->WallTexture[2].loadFromFile("../content/map/WALL/Wall_left15.png");			
	this->WallTexture[3].loadFromFile("../content/map/WALL/WallBottom_Left.png");
	this->WallTexture[4].loadFromFile("../content/map/WALL/WallBottom_Right.png");
	this->WallTexture[5].loadFromFile("../content/map/WALL/WallLeft_Bottom.png");
	this->WallTexture[6].loadFromFile("../content/map/WALL/WallLeft_Top.png");
	this->WallTexture[7].loadFromFile("../content/map/WALL/WallRight_Bottom.png");
	this->WallTexture[8].loadFromFile("../content/map/WALL/WallRight_Top.png");
	this->WallTexture[9].loadFromFile("../content/map/WALL/WallTop_Left.png");
	this->WallTexture[10].loadFromFile("../content/map/WALL/WallTop_Right.png");
	
}
void WORLD::SetupWallHitbox()
{
	// 15 Cell Horizonal
	this->Wall_HitBox15[0].setSize(sf::Vector2f(::CellPixelSize*15, ::CellPixelSize));
	this->Wall_HitBox15[0].setFillColor(sf::Color::White);
	this->Wall_HitBox15[0].setTexture(&WallTexture[0]);

	// 15 Cell Vertical right
	this->Wall_HitBox15[1].setSize(sf::Vector2f(::CellPixelSize, ::CellPixelSize*15));
	this->Wall_HitBox15[1].setFillColor(sf::Color::White);
	this->Wall_HitBox15[1].setTexture(&WallTexture[1]);

	// 15 Cell Vertical left
	this->Wall_HitBox15[2].setSize(sf::Vector2f(::CellPixelSize, ::CellPixelSize*15));
	this->Wall_HitBox15[2].setFillColor(sf::Color::White);
	this->Wall_HitBox15[2].setTexture(&WallTexture[2]);

	//WallBottom Left
	this->WallBottom[0].setSize(sf::Vector2f(::CellPixelSize * 5, ::CellPixelSize * 10));
	this->WallBottom[0].setFillColor(sf::Color::White);
	this->WallBottom[0].setTexture(&WallTexture[3]);

	//WallBottom Right
	this->WallBottom[1].setSize(sf::Vector2f(::CellPixelSize * 5, ::CellPixelSize * 10));
	this->WallBottom[1].setFillColor(sf::Color::White);
	this->WallBottom[1].setTexture(&WallTexture[4]);

	//WallLeft Bottom
	this->WallLeft[0].setSize(sf::Vector2f(::CellPixelSize * 10, ::CellPixelSize * 5));
	this->WallLeft[0].setFillColor(sf::Color::White);
	this->WallLeft[0].setTexture(&WallTexture[5]);

	//WallLeft Top
	this->WallLeft[1].setSize(sf::Vector2f(::CellPixelSize * 10, ::CellPixelSize * 5));
	this->WallLeft[1].setFillColor(sf::Color::White);
	this->WallLeft[1].setTexture(&WallTexture[6]);

	//WallRight Bottom
	this->WallRight[0].setSize(sf::Vector2f(::CellPixelSize * 10, ::CellPixelSize * 5));
	this->WallRight[0].setFillColor(sf::Color::White);
	this->WallRight[0].setTexture(&WallTexture[7]);

	//WallRight Top
	this->WallRight[1].setSize(sf::Vector2f(::CellPixelSize * 10, ::CellPixelSize * 5));
	this->WallRight[1].setFillColor(sf::Color::White);
	this->WallRight[1].setTexture(&WallTexture[8]);

	//WallTop Left
	this->WallTop[0].setSize(sf::Vector2f(::CellPixelSize * 5, ::CellPixelSize * 10));
	this->WallTop[0].setFillColor(sf::Color::White);
	this->WallTop[0].setTexture(&WallTexture[9]);

	//WallTop Right
	this->WallTop[1].setSize(sf::Vector2f(::CellPixelSize * 5, ::CellPixelSize * 10));
	this->WallTop[1].setFillColor(sf::Color::White);
	this->WallTop[1].setTexture(&WallTexture[10]);

	//virsualize wall
}

void WORLD::SetupWall(short row, short col, short RoomType)
{
	sf::Vector2 TopWall_ofRoom 			= 	{9, 8};
	sf::Vector2 RightWall_ofRoom		=	{24, 9};

	sf::Vector2 BottomWall_ofRoom 		= 	{9, 24};
	sf::Vector2 LeftWall_ofRoom 		= 	{8, 9};

	sf::Vector2 Top_HallWay_Right 		=	{19, -1};
	sf::Vector2 Top_HallWay_Left 		=	{9, -1};

	sf::Vector2 Bottom_HallWay_Right 	=	{19, 24};
	sf::Vector2 Bottom_HallWay_Left 	=	{9, 24};

	sf::Vector2 Right_HallWay_Top 		=	{24, 9};
	sf::Vector2 Right_HallWay_Bottom 	=	{24, 19};

	sf::Vector2 Left_HallWay_Top 		=	{-1, 9};
	sf::Vector2 Left_HallWay_Bottom 	=	{-1, 19};
	std::vector<sf::RectangleShape> temp;
	
	//Brute Force เอา จริงๆมีวิธีดีๆกว่านี้แต่ไม่ทำ
	switch(RoomType)
	{
	case 0:
	//Top
		this->Wall_HitBox15[2].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * LeftWall_ofRoom.x), (row*::GridPixelSize ) + ::CellPixelSize * LeftWall_ofRoom.y));
		temp.push_back(this->Wall_HitBox15[2]);
		this->Wall_HitBox15[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * RightWall_ofRoom.x), (row*::GridPixelSize ) + ::CellPixelSize * RightWall_ofRoom.y));
		temp.push_back(this->Wall_HitBox15[1]);
		this->Wall_HitBox15[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * BottomWall_ofRoom.x), (row*::GridPixelSize ) + ::CellPixelSize * BottomWall_ofRoom.y));
		temp.push_back(this->Wall_HitBox15[0]);

		this->WallTop[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Top_HallWay_Left.x), (row*::GridPixelSize ) + ::CellPixelSize * Top_HallWay_Left.y) );
		temp.push_back(this->WallTop[0]);
		this->WallTop[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Top_HallWay_Right.x), (row*::GridPixelSize ) + ::CellPixelSize * Top_HallWay_Right.y) );
		temp.push_back(this->WallTop[1]);
		break;
	case 1:
		//Right
		this->Wall_HitBox15[2].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * LeftWall_ofRoom.x), (row*::GridPixelSize ) + ::CellPixelSize * LeftWall_ofRoom.y));
		temp.push_back(this->Wall_HitBox15[2]);
		this->Wall_HitBox15[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * BottomWall_ofRoom.x), (row*::GridPixelSize ) + ::CellPixelSize * BottomWall_ofRoom.y));
		temp.push_back(this->Wall_HitBox15[0]);
		this->Wall_HitBox15[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * TopWall_ofRoom.x), (row*::GridPixelSize ) + ::CellPixelSize * TopWall_ofRoom.y));
		temp.push_back(this->Wall_HitBox15[0]);

		this->WallRight[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Right_HallWay_Top.x), (row*::GridPixelSize ) + ::CellPixelSize * Right_HallWay_Top.y)) ;
		temp.push_back(this->WallRight[1]);
		this->WallRight[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Right_HallWay_Bottom.x), (row*::GridPixelSize ) + ::CellPixelSize * Right_HallWay_Bottom.y) );
		temp.push_back(this->WallRight[0]);
		break;
	case 2:
		this->Wall_HitBox15[2].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * LeftWall_ofRoom.x), (row*::GridPixelSize ) + ::CellPixelSize * LeftWall_ofRoom.y));
		temp.push_back(this->Wall_HitBox15[2]);
		this->Wall_HitBox15[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * RightWall_ofRoom.x), (row*::GridPixelSize ) + ::CellPixelSize * RightWall_ofRoom.y));
		temp.push_back(this->Wall_HitBox15[1]);
		this->Wall_HitBox15[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * TopWall_ofRoom.x), (row*::GridPixelSize ) + ::CellPixelSize * TopWall_ofRoom.y));
		temp.push_back(this->Wall_HitBox15[0]);

		this->WallBottom[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Bottom_HallWay_Right.x), (row*::GridPixelSize ) + ::CellPixelSize * Bottom_HallWay_Right.y) );
		temp.push_back(this->WallBottom[1]);
		this->WallBottom[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Bottom_HallWay_Left.x), (row*::GridPixelSize ) + ::CellPixelSize * Bottom_HallWay_Left.y) );
		temp.push_back(this->WallBottom[0]);

		break;
	case 3:
		//left
		this->Wall_HitBox15[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * RightWall_ofRoom.x), (row*::GridPixelSize ) + ::CellPixelSize * RightWall_ofRoom.y));
		temp.push_back(this->Wall_HitBox15[1]);
		this->Wall_HitBox15[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * BottomWall_ofRoom.x), (row*::GridPixelSize ) + ::CellPixelSize * BottomWall_ofRoom.y));
		temp.push_back(this->Wall_HitBox15[0]);
		this->Wall_HitBox15[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * TopWall_ofRoom.x), (row*::GridPixelSize ) + ::CellPixelSize * TopWall_ofRoom.y));
		temp.push_back(this->Wall_HitBox15[0]);

		this->WallLeft[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Left_HallWay_Bottom.x), (row*::GridPixelSize ) + ::CellPixelSize * Left_HallWay_Bottom.y) );
		temp.push_back(this->WallLeft[0]);
		this->WallLeft[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Left_HallWay_Top.x), (row*::GridPixelSize ) + ::CellPixelSize * (Left_HallWay_Top.y)) );
		temp.push_back(this->WallLeft[1]);
		break;
	case 4:
		this->Wall_HitBox15[2].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * LeftWall_ofRoom.x), (row*::GridPixelSize ) + ::CellPixelSize * LeftWall_ofRoom.y));
		temp.push_back(this->Wall_HitBox15[2]);
		this->Wall_HitBox15[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * RightWall_ofRoom.x), (row*::GridPixelSize ) + ::CellPixelSize * RightWall_ofRoom.y));
		temp.push_back(this->Wall_HitBox15[1]);

		this->WallTop[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Top_HallWay_Left.x), (row*::GridPixelSize ) + ::CellPixelSize * Top_HallWay_Left.y) );
		temp.push_back(this->WallTop[0]);
		this->WallTop[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Top_HallWay_Right.x), (row*::GridPixelSize ) + ::CellPixelSize * Top_HallWay_Right.y) );
		temp.push_back(this->WallTop[1]);

		this->WallBottom[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Bottom_HallWay_Left.x), (row*::GridPixelSize ) + ::CellPixelSize * Bottom_HallWay_Left.y) );
		temp.push_back(this->WallBottom[0]);
		this->WallBottom[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Bottom_HallWay_Right.x), (row*::GridPixelSize ) + ::CellPixelSize * Bottom_HallWay_Right.y) );
		temp.push_back(this->WallBottom[1]);
		
		break;
	case 5:
		this->Wall_HitBox15[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * BottomWall_ofRoom.x), (row*::GridPixelSize ) + ::CellPixelSize * BottomWall_ofRoom.y));
		temp.push_back(this->Wall_HitBox15[0]);
		this->Wall_HitBox15[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * TopWall_ofRoom.x), (row*::GridPixelSize ) + ::CellPixelSize * TopWall_ofRoom.y));
		temp.push_back(this->Wall_HitBox15[0]);

		
		this->WallRight[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Right_HallWay_Bottom.x), (row*::GridPixelSize ) + ::CellPixelSize * Right_HallWay_Bottom.y) );
		temp.push_back(this->WallRight[0]);
		this->WallRight[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Right_HallWay_Top.x), (row*::GridPixelSize ) + ::CellPixelSize * Right_HallWay_Top.y)) ;
		temp.push_back(this->WallRight[1]);

		this->WallLeft[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Left_HallWay_Bottom.x), (row*::GridPixelSize ) + ::CellPixelSize * Left_HallWay_Bottom.y) );
		temp.push_back(this->WallLeft[0]);
		this->WallLeft[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Left_HallWay_Top.x), (row*::GridPixelSize ) + ::CellPixelSize * (Left_HallWay_Top.y)) );
		temp.push_back(this->WallLeft[1]);

		break;
	case 6:
		this->Wall_HitBox15[2].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * LeftWall_ofRoom.x), (row*::GridPixelSize ) + ::CellPixelSize * LeftWall_ofRoom.y));
		temp.push_back(this->Wall_HitBox15[2]);
		this->Wall_HitBox15[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * BottomWall_ofRoom.x), (row*::GridPixelSize ) + ::CellPixelSize * BottomWall_ofRoom.y));
		temp.push_back(this->Wall_HitBox15[0]);

		this->WallRight[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Right_HallWay_Bottom.x), (row*::GridPixelSize ) + ::CellPixelSize * Right_HallWay_Bottom.y) );
		temp.push_back(this->WallRight[0]);
		this->WallRight[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Right_HallWay_Top.x), (row*::GridPixelSize ) + ::CellPixelSize * Right_HallWay_Top.y)) ;
		temp.push_back(this->WallRight[1]);

		this->WallTop[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Top_HallWay_Left.x), (row*::GridPixelSize ) + ::CellPixelSize * Top_HallWay_Left.y) );
		temp.push_back(this->WallTop[0]);
		this->WallTop[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Top_HallWay_Right.x), (row*::GridPixelSize ) + ::CellPixelSize * Top_HallWay_Right.y) );
		temp.push_back(this->WallTop[1]);
		break;
	case 7:
		this->Wall_HitBox15[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * RightWall_ofRoom.x), (row*::GridPixelSize ) + ::CellPixelSize * RightWall_ofRoom.y));
		temp.push_back(this->Wall_HitBox15[1]);
		this->Wall_HitBox15[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * BottomWall_ofRoom.x), (row*::GridPixelSize ) + ::CellPixelSize * BottomWall_ofRoom.y));
		temp.push_back(this->Wall_HitBox15[0]);

		this->WallLeft[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Left_HallWay_Bottom.x), (row*::GridPixelSize ) + ::CellPixelSize * Left_HallWay_Bottom.y) );
		temp.push_back(this->WallLeft[0]);
		this->WallLeft[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Left_HallWay_Top.x), (row*::GridPixelSize ) + ::CellPixelSize * (Left_HallWay_Top.y)) );
		temp.push_back(this->WallLeft[1]);

		this->WallTop[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Top_HallWay_Left.x), (row*::GridPixelSize ) + ::CellPixelSize * Top_HallWay_Left.y) );
		temp.push_back(this->WallTop[0]);
		this->WallTop[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Top_HallWay_Right.x), (row*::GridPixelSize ) + ::CellPixelSize * Top_HallWay_Right.y) );
		temp.push_back(this->WallTop[1]);
		break;
	case 8:
		this->Wall_HitBox15[2].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * LeftWall_ofRoom.x), (row*::GridPixelSize ) + ::CellPixelSize * LeftWall_ofRoom.y));
		temp.push_back(this->Wall_HitBox15[2]);
		this->Wall_HitBox15[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * TopWall_ofRoom.x), (row*::GridPixelSize ) + ::CellPixelSize * TopWall_ofRoom.y));
		temp.push_back(this->Wall_HitBox15[0]);

		this->WallRight[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Right_HallWay_Bottom.x), (row*::GridPixelSize ) + ::CellPixelSize * Right_HallWay_Bottom.y) );
		temp.push_back(this->WallRight[0]);
		this->WallRight[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Right_HallWay_Top.x), (row*::GridPixelSize ) + ::CellPixelSize * Right_HallWay_Top.y)) ;
		temp.push_back(this->WallRight[1]);

		this->WallBottom[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Bottom_HallWay_Left.x), (row*::GridPixelSize ) + ::CellPixelSize * Bottom_HallWay_Left.y) );
		temp.push_back(this->WallBottom[0]);
		this->WallBottom[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Bottom_HallWay_Right.x), (row*::GridPixelSize ) + ::CellPixelSize * Bottom_HallWay_Right.y) );
		temp.push_back(this->WallBottom[1]);
		break;
	case 9:
		this->Wall_HitBox15[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * RightWall_ofRoom.x), (row*::GridPixelSize ) + ::CellPixelSize * RightWall_ofRoom.y));
		temp.push_back(this->Wall_HitBox15[1]);
		this->Wall_HitBox15[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * TopWall_ofRoom.x), (row*::GridPixelSize ) + ::CellPixelSize * TopWall_ofRoom.y));
		temp.push_back(this->Wall_HitBox15[0]);

		this->WallLeft[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Left_HallWay_Bottom.x), (row*::GridPixelSize ) + ::CellPixelSize * Left_HallWay_Bottom.y) );
		temp.push_back(this->WallLeft[0]);
		this->WallLeft[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Left_HallWay_Top.x), (row*::GridPixelSize ) + ::CellPixelSize * (Left_HallWay_Top.y)) );
		temp.push_back(this->WallLeft[1]);

		this->WallBottom[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Bottom_HallWay_Left.x), (row*::GridPixelSize ) + ::CellPixelSize * Bottom_HallWay_Left.y) );
		temp.push_back(this->WallBottom[0]);
		this->WallBottom[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Bottom_HallWay_Right.x), (row*::GridPixelSize ) + ::CellPixelSize * Bottom_HallWay_Right.y) );
		temp.push_back(this->WallBottom[1]);
		break;
	case 10:
		this->Wall_HitBox15[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * BottomWall_ofRoom.x), (row*::GridPixelSize ) + ::CellPixelSize *  BottomWall_ofRoom.y));
		temp.push_back(this->Wall_HitBox15[0]);

		this->WallTop[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Top_HallWay_Left.x), (row*::GridPixelSize ) + ::CellPixelSize * Top_HallWay_Left.y) );
		temp.push_back(this->WallTop[0]);
		this->WallTop[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Top_HallWay_Right.x), (row*::GridPixelSize ) + ::CellPixelSize * Top_HallWay_Right.y) );
		temp.push_back(this->WallTop[1]);

		this->WallRight[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Right_HallWay_Bottom.x), (row*::GridPixelSize ) + ::CellPixelSize * Right_HallWay_Bottom.y) );
		temp.push_back(this->WallRight[0]);
		this->WallRight[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Right_HallWay_Top.x), (row*::GridPixelSize ) + ::CellPixelSize * Right_HallWay_Top.y)) ;
		temp.push_back(this->WallRight[1]);

		this->WallLeft[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Left_HallWay_Bottom.x), (row*::GridPixelSize ) + ::CellPixelSize * Left_HallWay_Bottom.y) );
		temp.push_back(this->WallLeft[0]);
		this->WallLeft[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Left_HallWay_Top.x), (row*::GridPixelSize ) + ::CellPixelSize * (Left_HallWay_Top.y)) );
		temp.push_back(this->WallLeft[1]);

		break;
	case 11:
		this->Wall_HitBox15[2].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * LeftWall_ofRoom.x), (row*::GridPixelSize ) + ::CellPixelSize * LeftWall_ofRoom.y));
		temp.push_back(this->Wall_HitBox15[2]);

		this->WallTop[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Top_HallWay_Left.x), (row*::GridPixelSize ) + ::CellPixelSize * Top_HallWay_Left.y) );
		temp.push_back(this->WallTop[0]);
		this->WallTop[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Top_HallWay_Right.x), (row*::GridPixelSize ) + ::CellPixelSize * Top_HallWay_Right.y) );
		temp.push_back(this->WallTop[1]);

		this->WallRight[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Right_HallWay_Bottom.x), (row*::GridPixelSize ) + ::CellPixelSize * Right_HallWay_Bottom.y) );
		temp.push_back(this->WallRight[0]);
		this->WallRight[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Right_HallWay_Top.x), (row*::GridPixelSize ) + ::CellPixelSize * Right_HallWay_Top.y)) ;
		temp.push_back(this->WallRight[1]);

		this->WallBottom[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Bottom_HallWay_Left.x), (row*::GridPixelSize ) + ::CellPixelSize * Bottom_HallWay_Left.y) );
		temp.push_back(this->WallBottom[0]);
		this->WallBottom[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Bottom_HallWay_Right.x), (row*::GridPixelSize ) + ::CellPixelSize * Bottom_HallWay_Right.y) );
		temp.push_back(this->WallBottom[1]);

		break;
	case 12:
		this->Wall_HitBox15[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * TopWall_ofRoom.x), (row*::GridPixelSize ) + ::CellPixelSize * TopWall_ofRoom.y));
		temp.push_back(this->Wall_HitBox15[0]);

		this->WallRight[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Right_HallWay_Bottom.x), (row*::GridPixelSize ) + ::CellPixelSize * Right_HallWay_Bottom.y) );
		temp.push_back(this->WallRight[0]);
		this->WallRight[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Right_HallWay_Top.x), (row*::GridPixelSize ) + ::CellPixelSize * Right_HallWay_Top.y)) ;
		temp.push_back(this->WallRight[1]);

		this->WallBottom[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Bottom_HallWay_Left.x), (row*::GridPixelSize ) + ::CellPixelSize * Bottom_HallWay_Left.y) );
		temp.push_back(this->WallBottom[0]);
		this->WallBottom[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Bottom_HallWay_Right.x), (row*::GridPixelSize ) + ::CellPixelSize * Bottom_HallWay_Right.y) );
		temp.push_back(this->WallBottom[1]);

		this->WallLeft[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Left_HallWay_Bottom.x), (row*::GridPixelSize ) + ::CellPixelSize * Left_HallWay_Bottom.y) );
		temp.push_back(this->WallLeft[0]);
		this->WallLeft[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Left_HallWay_Top.x), (row*::GridPixelSize ) + ::CellPixelSize * (Left_HallWay_Top.y)) );
		temp.push_back(this->WallLeft[1]);
		break;
	case 13:
		this->Wall_HitBox15[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * RightWall_ofRoom.x), (row*::GridPixelSize ) + ::CellPixelSize * RightWall_ofRoom.y));
		temp.push_back(this->Wall_HitBox15[1]);

		this->WallTop[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Top_HallWay_Left.x), (row*::GridPixelSize ) + ::CellPixelSize * Top_HallWay_Left.y) );
		temp.push_back(this->WallTop[0]);
		this->WallTop[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Top_HallWay_Right.x), (row*::GridPixelSize ) + ::CellPixelSize * Top_HallWay_Right.y) );
		temp.push_back(this->WallTop[1]);

		this->WallBottom[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Bottom_HallWay_Left.x), (row*::GridPixelSize ) + ::CellPixelSize * Bottom_HallWay_Left.y) );
		temp.push_back(this->WallBottom[0]);
		this->WallBottom[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Bottom_HallWay_Right.x), (row*::GridPixelSize ) + ::CellPixelSize * Bottom_HallWay_Right.y) );
		temp.push_back(this->WallBottom[1]);

		this->WallLeft[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Left_HallWay_Bottom.x), (row*::GridPixelSize ) + ::CellPixelSize * Left_HallWay_Bottom.y) );
		temp.push_back(this->WallLeft[0]);
		this->WallLeft[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Left_HallWay_Top.x), (row*::GridPixelSize ) + ::CellPixelSize * (Left_HallWay_Top.y)) );
		temp.push_back(this->WallLeft[1]);

		break;
	case 14:
		this->WallTop[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Top_HallWay_Left.x), (row*::GridPixelSize ) + ::CellPixelSize * Top_HallWay_Left.y) );
		temp.push_back(this->WallTop[0]);
		this->WallTop[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Top_HallWay_Right.x), (row*::GridPixelSize ) + ::CellPixelSize * Top_HallWay_Right.y) );
		temp.push_back(this->WallTop[1]);

		this->WallRight[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Right_HallWay_Bottom.x), (row*::GridPixelSize ) + ::CellPixelSize * Right_HallWay_Bottom.y) );
		temp.push_back(this->WallRight[0]);
		this->WallRight[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Right_HallWay_Top.x), (row*::GridPixelSize ) + ::CellPixelSize * Right_HallWay_Top.y)) ;
		temp.push_back(this->WallRight[1]);

		this->WallBottom[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Bottom_HallWay_Left.x), (row*::GridPixelSize ) + ::CellPixelSize * Bottom_HallWay_Left.y) );
		temp.push_back(this->WallBottom[0]);
		this->WallBottom[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Bottom_HallWay_Right.x), (row*::GridPixelSize ) + ::CellPixelSize * Bottom_HallWay_Right.y) );
		temp.push_back(this->WallBottom[1]);

		this->WallLeft[0].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Left_HallWay_Bottom.x), (row*::GridPixelSize ) + ::CellPixelSize * Left_HallWay_Bottom.y) );
		temp.push_back(this->WallLeft[0]);
		this->WallLeft[1].setPosition(sf::Vector2f( (col*::GridPixelSize) + (::CellPixelSize * Left_HallWay_Top.x), (row*::GridPixelSize ) + ::CellPixelSize * (Left_HallWay_Top.y)) );
		temp.push_back(this->WallLeft[1]);
		break;
	default:
		break;
	}
	this->Wall.push_back(temp);
	temp.clear();
}
void WORLD::WallClear()
{
	this->Wall.clear();
}

//Player interact with world
int WORLD::CurrentPlayerGrid(float Pos_x, float Pos_y, short Amount_of_Room)
{
   int room_id = 0;
   for(room_id = 0; room_id < Amount_of_Room + 1; room_id++)
   {
      if(	((Pos_x) >= ::GridPixelSize * Field_Posi[room_id].Grid_col && (Pos_x) < ::GridPixelSize * (Field_Posi[room_id].Grid_col + 1))
       &&  	((Pos_y) >= ::GridPixelSize * Field_Posi[room_id].Grid_row && (Pos_y) < ::GridPixelSize * (Field_Posi[room_id].Grid_row + 1))  )
      {
         return room_id;
      }
   }
   return room_id;
}

int WORLD::CurrentEnemyGrid(float Pos_x, float Pos_y, short Amount_of_Room)
{
   int room_id = 0;
   for(room_id = 0; room_id < Amount_of_Room + 1; room_id++)
   {
      if(	((Pos_x) >= ::GridPixelSize * Field_Posi[room_id].Grid_col && (Pos_x) < ::GridPixelSize * (Field_Posi[room_id].Grid_col + 1))
       &&  	((Pos_y) >= ::GridPixelSize * Field_Posi[room_id].Grid_row && (Pos_y) < ::GridPixelSize * (Field_Posi[room_id].Grid_row + 1))  )
      {
         return room_id;
      }
   }
   return room_id;
}

//random map

void WORLD::Random_GRID(short AMOUNT_Room = 5) //default number = 5 room + 1 spawnroom
{
	bool Nearby_Grid_Check;
	int i, j;
	short Amount_GridInMap = 9;
	short MAP_CREATE_DIR;
	srand(time(NULL));
	// ### Create matrix for mapping ###
	CREATE_MATRIX_POINT:
	free(this->Field_Posi);
	this->Field_Posi = (struct Posi_InMap*)calloc(AMOUNT_Room+1, sizeof(*Field_Posi));

	free(this->MAP_MATRIX);
	this->MAP_MATRIX = (short**)calloc(Amount_GridInMap, sizeof(short*));
	for (i = 0; i < Amount_GridInMap; i++) { this->MAP_MATRIX[i] = (short*)calloc(Amount_GridInMap, sizeof(short)); }


	// ### Rand and set SpawnPoint room ###
	SpawnPoint_Posi.Grid_row = (rand() % (Amount_GridInMap - 3)) + 1;
	SpawnPoint_Posi.Grid_col = (rand() % (Amount_GridInMap - 3)) + 1;
	this->SpawnPointPos.x = ((SpawnPoint_Posi.Grid_col * ::GridPixelSize) + GridPixelSize/2);
	this->SpawnPointPos.y = ((SpawnPoint_Posi.Grid_row * ::GridPixelSize) + GridPixelSize/2);

	this->MAP_MATRIX[SpawnPoint_Posi.Grid_row][SpawnPoint_Posi.Grid_col] = 1;
	
	// Spawnpoint located
	Current_Grid_Posi.Grid_row = SpawnPoint_Posi.Grid_row;
	Current_Grid_Posi.Grid_col = SpawnPoint_Posi.Grid_col;

	/*
	[[(0,0) (0,1) (0,2) (0,3) (0,4)
	(1,0) (1,1) (1,2) (1,3) (1,4)
	(2,0) (2,1) (2,2) (2,3) (2,4)
	(3,0) (3,1) (3,2) (3,3) (3,4)
	(4,0) (4,1) (4,2) (4,3) (4,4)]]
	*/
	// ### Rand Create room ###
	for (i = 0; i < (AMOUNT_Room); i++)
	{
		this->Field_Posi[i].Grid_row = Current_Grid_Posi.Grid_row;
		this->Field_Posi[i].Grid_col = Current_Grid_Posi.Grid_col;
		Nearby_Grid_Check = false;
		// Get nearby grid around Current grid
		for (j = 0; j < 4; j++)
		{
			/* if 0 then x -= 1  --> - (-1**(0/2)) * -1*(0%2(0)-1) = -1, + (-1**floor(0/2)) * (0%2(0)) =  0
			if 1 then y += 1	 --> - (-1**(1/2)) * -1*(1%2(1)-1) =  0, + (-1**floor(1/2)) * (1%2(1)) = +1
			if 2 then x += 1  	 --> - (-1**(2/2)) * -1*(2%2(0)-1) = +1, + (-1**floor(2/2)) * (2%2(0)) =  0
			if 3 then y -= 1	 --> - (-1**(3/2)) * -1*(3%2(1)-1) =  0, + (-1**floor(3/2)) * (3%2(1)) = -1
			*/
			Near_Grid_Contrain[j].Grid_row = Current_Grid_Posi.Grid_row - (pow(-1, (j / 2)) * (-1 * ((j % 2) - 1)));
			Near_Grid_Contrain[j].Grid_col = Current_Grid_Posi.Grid_col + (pow(-1, static_cast<short>(j / 2)) * (j % 2));
		}
		for (j = 0; j < 4; j++)
		{
			if (   Near_Grid_Contrain[j].Grid_row > Amount_GridInMap-2 || Near_Grid_Contrain[j].Grid_row < 1
				|| Near_Grid_Contrain[j].Grid_col > Amount_GridInMap-2 || Near_Grid_Contrain[j].Grid_col < 1) {
				continue;
			}
			if (this->MAP_MATRIX[Near_Grid_Contrain[j].Grid_row][Near_Grid_Contrain[j].Grid_col] == 0) {
				Nearby_Grid_Check = true;
			}// check ว่ารอบๆให้สร้างแมพมีที่ไหม
		}
		if (Nearby_Grid_Check) 
		{
			do
			{
				MAP_CREATE_DIR = rand() % 4;
				/*
				- 0 Go Up
				- 1 Go Right
				- 2 Go Down
				- 3 Go Left
				*/
			}while(Near_Grid_Contrain[MAP_CREATE_DIR].Grid_row > Amount_GridInMap-2 || Near_Grid_Contrain[MAP_CREATE_DIR].Grid_row < 1
				|| Near_Grid_Contrain[MAP_CREATE_DIR].Grid_col > Amount_GridInMap-2 || Near_Grid_Contrain[MAP_CREATE_DIR].Grid_col < 1
				|| this->MAP_MATRIX[Near_Grid_Contrain[MAP_CREATE_DIR].Grid_row][Near_Grid_Contrain[MAP_CREATE_DIR].Grid_col] == 1);
			//find that has "1" already in randommed grid will return false

			// Current Grid Position Set
			Current_Grid_Posi.Grid_row = Near_Grid_Contrain[MAP_CREATE_DIR].Grid_row;
			Current_Grid_Posi.Grid_col = Near_Grid_Contrain[MAP_CREATE_DIR].Grid_col;

			// Assign " 1 " to Grid that be a game map
			this->MAP_MATRIX[Current_Grid_Posi.Grid_row][Current_Grid_Posi.Grid_col] = 1;

			PortalRoom_Posi.Grid_row = Current_Grid_Posi.Grid_row;
			PortalRoom_Posi.Grid_col = Current_Grid_Posi.Grid_col;
		}
		else
		{
			goto CREATE_MATRIX_POINT;
		}
	}
	this->Field_Posi[AMOUNT_Room].Grid_col = PortalRoom_Posi.Grid_col;
	this->Field_Posi[AMOUNT_Room].Grid_row = PortalRoom_Posi.Grid_row;


}

void WORLD::CreateWorld(short &Amount)
{
	Random_GRID(Amount); // Should call first another METHOD
    SetupMAP();
    SetupRoom(Amount);
}
//End of code line