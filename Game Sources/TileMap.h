#pragma once
#include <raylib.h>
#include "Sprite.h"
#include "Point.h"
#include "AABB.h"
#include "Globals.h"
#include <unordered_map>

enum class Tile {

	// -1: area covered by an entity
	EMPTY = -1,
	//  0: air tile
	AIR = 0,

	// 0 < id < 50: static tiles
	STONE = 1, STONE_2, GROUND, GROUND_2, BLOCK_WITH_L_DOWN, BLOCK_WITH_R_DOWN,
	STONE_WITHOUT_1, STONE_WITHOUT_2, STONE_WITHOUT_3, STONE_WITHOUT_4, STONE_WITH_1, STONE_WITH_3, STONE_WITH_5,
	STONE_WITH_7, STONE_WITH_9, STONE_WITH_11, HALF_COLUMN_1_L, HALF_COLUMN_2_L, HALF_COLUMN_BOTTOM_L,

	COLUMN_TOP_L = 20, COLUMN_1_L, COLUMN_2_L, COLUMN_3_L, COLUMN_TOP_R, COLUMN_1_R, COLUMN_2_R, COLUMN_3_R,
	HALF_COLUMN_TOP_WITHOUT = 30, HALF_COLUMN_TOP, HALF_COLUMN_1, HALF_COLUMN_2, HALF_COLUMN_BOTTOM, HALF_COLUMN_BOTTOM_WITHOUT, TROPICAL_BLOCK_L, TROPICAL_BLOCK_R,
	HALF_COLUMN_TOP_L, HALF_COLUMN_TOP_BOT, PRIMERA_ROCA_ARRIBA, PRIMERA_ROCA_ABAJO, SEGUNDA_ROCA_ARRIBA, SEGUNDA_ROCA_ABAJO, PRIMERA_COLUMNA_SIN_LEFT, SEGUNDA_COLUMNA_SIN_LEFT,
	TERCERA_COLUMNA_SIN_LEFT, CUARTA_COLUMNA_SIN_LEFT, PRIMERA_COLUMNA_CON_LEFT_ARRIBA, PRIMERA_COLUMNA_CON_LEFT_ABAJO, ULTIMA_COLUMNA_CON, CON_1_ARRIBA, CON_2_ARRIBA, CON_3_ARRIBA,
	CON_4_ARRIBA,
	PRIMERA_ROCA_ARRIBA_VERDE, PRIMERA_ROCA_ABAJO_VERDE, SEGUNDA_ROCA_ARRIBA_VERDE, SEGUNDA_ROCA_ABAJO_VERDE, PRIMERA_COLUMNA_SIN_LEFT_VERDE, SEGUNDA_COLUMNA_SIN_LEFT_VERDE,
	TERCERA_COLUMNA_SIN_LEFT_VERDE, CUARTA_COLUMNA_SIN_LEFT_VERDE, PRIMERA_COLUMNA_CON_LEFT_ARRIBA_VERDE, PRIMERA_COLUMNA_CON_LEFT_ABAJO_VERDE, ULTIMA_COLUMNA_CON_VERDE,
	CON_1_ARRIBA_VERDE, CON_2_ARRIBA_VERDE, CON_3_ARRIBA_VERDE, CON_4_ARRIBA_VERDE,

	LADDER_TOP = 70, LADDER, LADDER_BOTTOM, STONE_WITH_2, STONE_WITH_4, STONE_WITH_6, STONE_WITH_8, STONE_WITH_10, STONE_WITH_12,
	DOOR_TOP_LEFT, DOOR_MID_LEFT, DOOR_BOTTOM_LEFT, DOOR_TOP_MID, DOOR_MID_MID, DOOR_BOTTOM_MID, DOOR_TOP_RIGHT, DOOR_MID_RIGHT, DOOR_BOTTOM_RIGHT, LADDER_TOP_AZUL, LADDER_BOTTOM_AZUL,
	CON_1_ABAJO, CON_2_ABAJO, CON_3_ABAJO, CON_4_ABAJO, SIN_1, SIN_2, SIN_3, SIN_4, LADDER_TOP_VERDE, LADDER_BOTTOM_VERDE, CON_1_ABAJO_VERDE, CON_2_ABAJO_VERDE, CON_3_ABAJO_VERDE,
	CON_4_ABAJO_VERDE, SIN_1_VERDE, SIN_2_VERDE, SIN_3_VERDE, SIN_4_VERDE,

	GREEN_DOOR_TOP_LEFT = 108, GREEN_DOOR_MID_LEFT, GREEN_DOOR_BOTTOM_LEFT, GREEN_DOOR_TOP_MID, GREEN_DOOR_MID_MID, GREEN_DOOR_BOTTOM_MID, GREEN_DOOR_TOP_RIGHT, GREEN_DOOR_MID_RIGHT, GREEN_DOOR_BOTTOM_RIGHT,

	ORANGE_C_TL, ORANGE_C_TM ,ORANGE_C_TR, ORANGE_C_BL = 124, ORANGE_C_BR, ORANGE_C_ML, ORANGE_C_MR,

	WATER_L = 120, WATER_R, LAVA_L, LAVA_R,
	// 50 <= id < 100: special tiles

	KEY = 130, OBJECT, EXP, PONER_LLAVE,
	LASER = 140, LASER_FRAME0, LASER_FRAME1, LASER_FRAME2, BLANCO, V_VIDA, I_VIDA, T_VIDA, E_EXPERIENCIA, X_EXPERIENCIA, P_EXPERIENCIA ,

	// id >= 100: entities' initial locations
	PLAYER = 151, ENEMY,

	PRIMERA_COLUMNA_SIN_RIGHT, SEGUNDA_COLUMNA_SIN_RIGHT,
	TERCERA_COLUMNA_SIN_RIGHT, CUARTA_COLUMNA_SIN_RIGHT, ULTIMA_COLUMNA_CON_RIGHT, PRIMERA_COLUMNA_CON_RIGHT_ARRIBA, PRIMERA_COLUMNA_CON_RIGHT_ABAJO,

	PRIMERA_COLUMNA_SIN_RIGHT_VERDE, SEGUNDA_COLUMNA_SIN_RIGHT_VERDE, TERCERA_COLUMNA_SIN_RIGHT_VERDE, CUARTA_COLUMNA_SIN_RIGHT_VERDE,
	ULTIMA_COLUMNA_CON_RIGHT_VERDE, PRIMERA_COLUMNA_CON_RIGHT_ARRIBA_VERDE, PRIMERA_COLUMNA_CON_RIGHT_ABAJO_VERDE,

	//Intervals
	STATIC_FIRST = STONE,
	STATIC_LAST = LAVA_R,
	SOLID_FIRST = STONE,
	SOLID_LAST = CON_4_ARRIBA_VERDE,
	SPECIAL_FIRST = KEY,
	SPECIAL_LAST = LASER,
	ENTITY_FIRST = PLAYER,
	ENTITY_LAST = ENEMY
};

class TileMap
{
public:
	TileMap();
	~TileMap();

	AppStatus Initialise();
	AppStatus Load(int data[], int w, int h);
	void Update();
	void Render();
	void Release();

	//Test for collisions with walls
	bool TestCollisionWallLeft(const AABB& box) const;
	bool TestCollisionWallRight(const AABB& box) const;

	//Test collision with the ground and update 'py' with the maximum y-position to prevent
	//penetration of the grounded tile, that is, the pixel y-position above the grounded tile.
	//Grounded tile = solid tile (blocks) or ladder tops.
	bool TestCollisionGround(const AABB& box, int* py) const;

	//Test if there is a ground tile one pixel below the given box
	bool TestFalling(const AABB& box) const;

	//Test if box is on ladder and update 'px' with the x-center position of the ladder
	bool TestOnLadder(const AABB& box, int* px) const;

	//Test if box is on ladder top and update 'px' with the x-center position of the ladder
	bool TestOnLadderTop(const AABB& box, int* px) const;

	//Test if box is on a door

	bool TestOnDoor(const AABB& box, int* px) const;



private:
	void InitTileDictionary();

	Tile GetTileIndex(int x, int y) const;
	bool IsTileSolid(Tile tile) const;
	bool IsTileLadderTop(Tile tile) const;
	bool IsTileLadder(Tile tile) const;
	bool IsTileDoor(Tile tile) const;
	bool CollisionX(const Point& p, int distance) const;
	bool CollisionY(const Point& p, int distance) const;
	int GetLadderCenterPos(int pixel_x, int pixel_y) const;

	//Tile map
	Tile* map;

	//Size of the tile map
	int size, width, height;

	//Dictionary of tile frames
	std::unordered_map<int, Rectangle> dict_rect;

	Sprite* laser;

	//Tile sheet
	const Texture2D* img_tiles;
};