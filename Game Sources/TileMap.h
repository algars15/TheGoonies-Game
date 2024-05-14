#pragma once
#include <raylib.h>
#include "Sprite.h"
#include "Point.h"
#include "AABB.h"
#include "Globals.h"
#include <unordered_map>

enum class Tile {
	//
	NEXT_LEVEL = -2,

	// -1: area covered by an entity
	EMPTY = -1,
	//  0: air tile
	AIR = 0,


	// id 1 to 99 static tiles

	WALL1_TOP_LEFT = 1, WALL1_TOP_RIGHT, WALL1_MID1_LEFT, WALL1_MID1_RIGHT, WALL1_MID2_LEFT, WALL1_MID2_RIGHT,														//6
	WALL1_MID3_LEFT, WALL1_MID3_RIGHT, WALL1_FLOOR_LEFT, WALL1_FLOOR_RIGHT, GENERAL_WALL1, GENERAL_WALL2,															//12
	STALACTITE1, STALACTITE2, STALACTITE3, STALACTITE4_LEFT, STALACTITE4_RIGHT, BIG_STALACTITE_TOP_LEFT,															//18
	BIG_STALACTITE_TOP_RIGHT, BIG_STALACTITE_MID_LEFT, BIG_STALACTITE_MID_RIGHT, BIG_STALACTITE_MID2_LEFT, BIG_STALACTITE_MID2_RIGHT, BIG_STALACTITE_BOTTOM_LEFT,   //24
	BIG_STALACTITE_BOTTOM_RIGHT, STALACTITE5_LEFT, STALACTITE5_RIGHT, WOOD_SOLID_FLOOR_LEFT, WOOD_SOLID_FLOOR_RIGHT,												//29



	FLOOR_LEFT, FLOOR_RIGHT, FLOOR, DOOR_CAVE_FLOOR_RIGHT, DOOR_CAVE_FLOOR_LEFT, DOOR_CAVE_MID_LEFT,																//35
	DOOR_CAVE_MID_RIGHT, DOOR_CAVE_TOP_LEFT, DOOR_CAVE_TOP_MID, DOOR_CAVE_TOP_RIGHT, LADDER_LIANA, LADDER_LIANA_FLOOR,												//41
	LADDER_LIANA_TOP, DOOR_FLOOR_LEFT, DOOR_FLOOR_MID, DOOR_FLOOR_RIGHT, DOOR_MID_LEFT, DOOR_MID_MID,																//47
	DOOR_MID_RIGHT, DOOR_TOP_LEFT, DOOR_TOP_MID, DOOR_TOP_RIGHT, WOOD_STATIC_FLOOR_LEFT, WOOD_STATIC_FLOOR_RIGHT,													//53
	DOOR_OPEN_FLOOR_LEFT, DOOR_OPEN_FLOOR_MID, DOOR_OPEN_FLOOR_RIGHT, DOOR_OPEN_MID_LEFT, DOOR_OPEN_MID_MID, DOOR_OPEN_MID_RIGHT,									//59
	DOOR_OPEN_TOP_LEFT, DOOR_OPEN_TOP_MID, DOOR_OPEN_TOP_RIGHT, SKELETON_DOOR_FLOOR_LEFT, SKELETON_DOOR_FLOOR_RIGHT, SKELETON_DOOR_MID1_LEFT,						//65
	SKELETON_DOOR_MID1_RIGHT, SKELETON_DOOR_MID2_LEFT, SKELETON_DOOR_MID2_MID, SKELETON_DOOR_MID2_RIGHT, SKELETON_DOOR_TOP_LEFT, SKELETON_DOOR_TOP_MID,				//71
	SKELETON_DOOR_TOP_RIGHT, TUB_CORNER, TUB_HORITZONAL, TUB_FLOOR, TUB_TOP, TUB_VERTICAL,																			//77
	LOCK_KEY, WATER, WATER_LAKE1, WATER_LAKE2, WATER_LAKE_BANK_LEFT, WATER_LAKE_BANK_RIGHT,																			//83
	WATERFALL_HOLE_TOP_LEFT, WATERFALL_HOLE_TOP_MID, WATERFALL_HOLE_TOP_RIGHT, WATERFALL_HOLE_LOW_LEFT, WATERFALL_HOLE_LOW_MID, WATERFALL_HOLE_LOW_RIGHT,			//89
	
	//id >= 100 special tiles
	KEY = 100, CURE, BAG,
	

	// id >= 200: entities' initial locations
	PLAYER = 200,

	//Intervals
	STATIC_FIRST = WALL1_TOP_LEFT,
	STATIC_LAST = TUB_VERTICAL,
	SOLID_FIRST = WALL1_TOP_LEFT,
	SOLID_LAST = WOOD_SOLID_FLOOR_RIGHT,
	SPECIAL_FIRST = KEY,
	SPECIAL_LAST = BAG,
	ENTITY_FIRST = PLAYER,
	ENTITY_LAST = PLAYER

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
	bool TestCollisionGround(const AABB& box, int *py) const;
	
	//Test if there is a ground tile one pixel below the given box
	bool TestFalling(const AABB& box) const;
	
	//Test if box is on ladder and update 'px' with the x-center position of the ladder
	bool TestOnLadder(const AABB& box, int* px) const;
	
	//Test if box is on ladder top and update 'px' with the x-center position of the ladder
	bool TestOnLadderTop(const AABB& box, int* px) const;

	bool TestOnLadderBottom(const AABB& box, int* px) const;

private:
	void InitTileDictionary();

	Tile GetTileIndex(int x, int y) const;
	bool IsTileSolid(Tile tile) const;
	bool IsTileLadderTop(Tile tile) const;
	bool IsTileLadder(Tile tile) const;
	bool IsTileLadderBottom(Tile tile) const;
	bool CollisionX(const Point& p, int distance) const;
	bool CollisionY(const Point& p, int distance) const;
	int GetLadderCenterPos(int pixel_x, int pixel_y) const;

	//Tile map
	Tile *map;

	//Size of the tile map
	int size, width, height;
	
	//Dictionary of tile frames
	std::unordered_map<int, Rectangle> dict_rect;

	Sprite *water;
	
	//Tile sheet
	const Texture2D *img_tiles;
};

