#include "TileMap.h"
#include "Globals.h"
#include "ResourceManager.h"
#include <cstring>

TileMap::TileMap()
{
	map = nullptr;
	width = 0;
	height = 0;
	water = nullptr;
	img_tiles = nullptr;

	InitTileDictionary();
}
TileMap::~TileMap()
{
	if (map != nullptr)
	{
		delete[] map;
		map = nullptr;
	}
	if (water != nullptr)
	{
		water->Release();
		delete water;
		water = nullptr;
	}
}
void TileMap::InitTileDictionary()
{
	const int n = TILE_SIZE;


	//SOLID TILES
	dict_rect[(int)Tile::WALL1_TOP_LEFT] = { 0,  0, n, n };
	dict_rect[(int)Tile::WALL1_TOP_RIGHT] = { n,  0, n, n };
	dict_rect[(int)Tile::WALL1_MID1_LEFT] = { 0, n, n, n };
	dict_rect[(int)Tile::WALL1_MID1_RIGHT] = { n, n, n, n };
	dict_rect[(int)Tile::WALL1_MID2_LEFT] = { 0,  2*n, n, n };
	dict_rect[(int)Tile::WALL1_MID2_RIGHT] = { n,  2*n, n, n };
	dict_rect[(int)Tile::WALL1_MID3_LEFT] = { 0, 3*n, n, n };
	dict_rect[(int)Tile::WALL1_MID3_RIGHT] = { n, 3 * n, n, n };
	dict_rect[(int)Tile::WALL1_FLOOR_LEFT] = { 0,  4 * n, n, n };
	dict_rect[(int)Tile::WALL1_FLOOR_RIGHT] = { n, 4 * n, n, n };
	dict_rect[(int)Tile::GENERAL_WALL1] = { 0, 5 * n, n, n };
	dict_rect[(int)Tile::GENERAL_WALL2] = { n, 5 * n, n, n };
	dict_rect[(int)Tile::STALACTITE1] = {2*n, n, n, n };
	dict_rect[(int)Tile::STALACTITE2] = { 3*n, n, n, n };
	dict_rect[(int)Tile::STALACTITE3] = { 5*n, n, n, n };
	dict_rect[(int)Tile::STALACTITE4_LEFT] = { 6 * n, 0, n, n };
	dict_rect[(int)Tile::STALACTITE4_RIGHT] = { 7 * n, 0, n, n };
	dict_rect[(int)Tile::BIG_STALACTITE_TOP_LEFT] = { 8 * n, 0, n, n };
	dict_rect[(int)Tile::BIG_STALACTITE_TOP_RIGHT] = { 9 * n, 0, n, n };
	dict_rect[(int)Tile::BIG_STALACTITE_MID_LEFT] = { 8 * n, n, n, n };
	dict_rect[(int)Tile::BIG_STALACTITE_MID_RIGHT] = { 9 * n, n, n, n };
	dict_rect[(int)Tile::BIG_STALACTITE_MID2_LEFT] = { 8 * n, 2* n, n, n };
	dict_rect[(int)Tile::BIG_STALACTITE_MID2_RIGHT] = { 9 * n, 2 * n, n, n };
	dict_rect[(int)Tile::BIG_STALACTITE_BOTTOM_LEFT] = { 8 * n, 3 * n, n, n };
	dict_rect[(int)Tile::BIG_STALACTITE_BOTTOM_RIGHT] = { 9 * n, 3 * n, n, n };
	dict_rect[(int)Tile::STALACTITE5_LEFT] = { 6 * n, 5 * n, n, n };
	dict_rect[(int)Tile::STALACTITE5_RIGHT] = { 7 * n, 5 * n, n, n };
	

	//FLOOR
	dict_rect[(int)Tile::FLOOR_LEFT] = { 2 * n, 0, n, n };
	dict_rect[(int)Tile::FLOOR_RIGHT] = { 5 * n, 0, n, n };
	dict_rect[(int)Tile::FLOOR] = { 3 * n, 4 * n, n, n };

	dict_rect[(int)Tile::WOOD_SOLID_FLOOR_LEFT] = { 0, 11 * n, n, n };
	dict_rect[(int)Tile::WOOD_SOLID_FLOOR_RIGHT] = { n, 11 * n, n, n };

	dict_rect[(int)Tile::WOOD_STATIC_FLOOR_LEFT] = { 0, 10 * n, n, n };
	dict_rect[(int)Tile::WOOD_STATIC_FLOOR_RIGHT] = { n, 10 * n, n, n };

	
	//CAVE DOOR
	dict_rect[(int)Tile::DOOR_CAVE_FLOOR_RIGHT] = { 4 * n, 4 * n, n, n };
	dict_rect[(int)Tile::DOOR_CAVE_FLOOR_LEFT] = { 2 * n, 4 * n, n, n };

	dict_rect[(int)Tile::DOOR_CAVE_MID_LEFT] = { 2 * n, 3 * n, n, n };
	dict_rect[(int)Tile::DOOR_CAVE_MID_RIGHT] = { 4 * n, 3 * n, n, n };

	dict_rect[(int)Tile::DOOR_CAVE_TOP_LEFT] = { 2 * n, 2 * n, n, n };
	dict_rect[(int)Tile::DOOR_CAVE_TOP_MID] = { 3 * n, 2 * n, n, n };
	dict_rect[(int)Tile::DOOR_CAVE_TOP_RIGHT] = { 4 * n, 2 * n, n, n };

	//LIANA
	dict_rect[(int)Tile::LADDER_LIANA] = { 4 * n, 0, n, n };
	dict_rect[(int)Tile::LADDER_LIANA_FLOOR] = { 3 * n, 0, n, n };
	dict_rect[(int)Tile::LADDER_LIANA_TOP] = { 4 * n, n, n, n };


	//GATE DOOR CLOSED

	dict_rect[(int)Tile::DOOR_FLOOR_LEFT] = { 5 * n, 4 * n, n, n };
	dict_rect[(int)Tile::DOOR_FLOOR_MID] = { 6 * n, 4 * n, n, n };
	dict_rect[(int)Tile::DOOR_FLOOR_RIGHT] = { 7 * n, 4 * n, n, n };

	dict_rect[(int)Tile::DOOR_MID_LEFT] = { 5 * n, 3 * n, n, n };
	dict_rect[(int)Tile::DOOR_MID_MID] = { 6 * n, 3 * n, n, n };
	dict_rect[(int)Tile::DOOR_MID_RIGHT] = { 7 * n, 3 * n, n, n };

	dict_rect[(int)Tile::DOOR_TOP_LEFT] = { 5 * n, 2 * n, n, n };
	dict_rect[(int)Tile::DOOR_TOP_MID] =  { 6 * n, 2 * n, n, n };
	dict_rect[(int)Tile::DOOR_TOP_RIGHT] ={ 7 * n, 2 * n, n, n };
	
	//GATE DOOR OPEN

	dict_rect[(int)Tile::DOOR_OPEN_FLOOR_LEFT] = { 5 * n, 4 * n, n, n };
	dict_rect[(int)Tile::DOOR_OPEN_FLOOR_MID] = { 5 * n, 4 * n, n, n };
	dict_rect[(int)Tile::DOOR_OPEN_FLOOR_LEFT] = { 5 * n, 4 * n, n, n };

	dict_rect[(int)Tile::DOOR_OPEN_MID_LEFT] = { 5 * n, 4 * n, n, n };
	dict_rect[(int)Tile::DOOR_OPEN_MID_MID] = { 5 * n, 4 * n, n, n };
	dict_rect[(int)Tile::DOOR_OPEN_MID_RIGHT] = { 5 * n, 4 * n, n, n };

	dict_rect[(int)Tile::DOOR_OPEN_TOP_LEFT] = { 5 * n, 4 * n, n, n };
	dict_rect[(int)Tile::DOOR_OPEN_TOP_MID] = { 5 * n, 4 * n, n, n };
	dict_rect[(int)Tile::DOOR_OPEN_TOP_RIGHT] = { 5 * n, 4 * n, n, n };

	//SKELETON DOOR

	dict_rect[(int)Tile::SKELETON_DOOR_FLOOR_LEFT] = { 10 * n, 3 * n, n, n };
	dict_rect[(int)Tile::SKELETON_DOOR_FLOOR_RIGHT] = { 12 * n, 3 * n, n, n };

	dict_rect[(int)Tile::SKELETON_DOOR_MID1_LEFT] = { 10 * n, 2 * n, n, n };
	dict_rect[(int)Tile::SKELETON_DOOR_MID1_RIGHT] = { 12 * n, 2 * n, n, n };
	dict_rect[(int)Tile::SKELETON_DOOR_MID2_LEFT] = { 10 * n, n, n, n };
	dict_rect[(int)Tile::SKELETON_DOOR_MID2_MID] = { 11 * n, n, n, n };
	dict_rect[(int)Tile::SKELETON_DOOR_MID2_RIGHT] = { 12 * n, n, n, n };

	dict_rect[(int)Tile::SKELETON_DOOR_TOP_LEFT] = { 10 * n, 0, n, n };
	dict_rect[(int)Tile::SKELETON_DOOR_TOP_MID] = { 11 * n, 0, n, n };
	dict_rect[(int)Tile::SKELETON_DOOR_TOP_RIGHT] = { 12 * n, 0, n, n };

	//TUB

	dict_rect[(int)Tile::TUB_CORNER] = { 10 * n, 4*n, n, n };
	dict_rect[(int)Tile::TUB_HORITZONAL] = { 11 * n, 4*n, n, n };
	dict_rect[(int)Tile::TUB_FLOOR] = { 12 * n, 4*n, n, n };
	dict_rect[(int)Tile::TUB_TOP] = { 10 * n, 5*n, n, n };
	dict_rect[(int)Tile::TUB_VERTICAL] = { 11 * n, 5*n, n, n };

	//LOCK KEY, KEY, BAG
	dict_rect[(int)Tile::LOCK_KEY] = { 7 * n, n, n, n };
	dict_rect[(int)Tile::KEY] = { 3 * n, 3*n, n, n };
	dict_rect[(int)Tile::BAG] = { 6* n, n, n, n };


	//WATER LAKE
	dict_rect[(int)Tile::WATER_LAKE1] = { 8 * n, 5 * n, n, n };
	dict_rect[(int)Tile::WATER_LAKE2] = { 9 * n, 5 * n, n, n };

	//WATERFALL HOLE

	dict_rect[(int)Tile::WATERFALL_HOLE_TOP_LEFT] = { 0, 8 * n, n, n };
	dict_rect[(int)Tile::WATERFALL_HOLE_TOP_MID] = { n, 8 * n, n, n };
	dict_rect[(int)Tile::WATERFALL_HOLE_TOP_RIGHT] = { 2 * n, 8 * n, n, n };

	dict_rect[(int)Tile::WATERFALL_HOLE_LOW_LEFT] = { 0, 9 * n, n, n };
	dict_rect[(int)Tile::WATERFALL_HOLE_LOW_MID] = { n, 9 * n, n, n };
	dict_rect[(int)Tile::WATERFALL_HOLE_LOW_RIGHT] = { 2 * n, 9 * n, n, n };





}
AppStatus TileMap::Initialise()
{
	ResourceManager& data = ResourceManager::Instance();

	if (data.LoadTexture(Resource::IMG_TILES, "images/TitleSetMap.png") != AppStatus::OK)
	{
		return AppStatus::ERROR;
	}
	img_tiles = data.GetTexture(Resource::IMG_TILES);

	water = new Sprite(img_tiles);
	if (water == nullptr)
	{
		LOG("Failed to allocate memory for laser sprite");
		return AppStatus::ERROR;
	}
	//water->SetNumberAnimations(1);
	//water->SetAnimationDelay(0, ANIM_DELAY);
	//water->AddKeyFrame(0, dict_rect[(int)Tile::WATER_FRAME0]);
	//water->AddKeyFrame(0, dict_rect[(int)Tile::WATER_FRAME1]);              //NEEDS TO PUT WATER SPRITES
	//water->AddKeyFrame(0, dict_rect[(int)Tile::WATER_FRAME2]);
	//water->AddKeyFrame(0, dict_rect[(int)Tile::WATER_FRAME3]);
	//water->AddKeyFrame(0, dict_rect[(int)Tile::WATER_FRAME4]);

	water->SetAnimation(0);

	return AppStatus::OK;
}
AppStatus TileMap::Load(int data[], int w, int h)
{
	size = w*h;
	width = w;
	height = h;

	if (map != nullptr)	delete[] map;

	map = new Tile[size];
	if (map == nullptr)	
	{
		LOG("Failed to allocate memory for tile map");
		return AppStatus::ERROR;
	}
	memcpy(map, data, size * sizeof(int));

	return AppStatus::OK;
}
void TileMap::Update()
{
	water->Update();
}
Tile TileMap::GetTileIndex(int x, int y) const
{
	int idx = x + y*width;
	if(idx < 0 || idx >= size)
	{
		LOG("Error: Index out of bounds. Tile map dimensions: %dx%d. Given index: (%d, %d)", width, height, x, y)
		return Tile::AIR;
	}
	return map[x + y * width];
}
bool TileMap::IsTileSolid(Tile tile) const
{
	return (Tile::SOLID_FIRST <= tile && tile <= Tile::SOLID_LAST);
}
bool TileMap::IsTileLadderTop(Tile tile) const
{
	return tile == Tile::LADDER_LIANA_TOP;
}

bool TileMap::IsTileLadderBottom(Tile tile) const
{
	return tile == Tile::LADDER_LIANA_FLOOR;
}

bool TileMap::IsTileLadder(Tile tile) const
{
	bool b1, b2;
	b1 = tile == Tile::LADDER_LIANA;
	b2 = tile == Tile::LADDER_LIANA_FLOOR;
	return b1 || b2;
}

bool TileMap::TestCollisionWallLeft(const AABB& box) const
{
	return CollisionX(box.pos, box.height);
}
bool TileMap::TestCollisionWallRight(const AABB& box) const
{
	return CollisionX(box.pos + Point(box.width - 1, 0), box.height);
}
bool TileMap::TestCollisionGround(const AABB& box, int *py) const
{
	Point p(box.pos.x, *py);	//control point
	int tile_y;

	if (CollisionY(p, box.width))
	{
		tile_y = p.y / TILE_SIZE;

		*py = tile_y * TILE_SIZE - 1;
		return true;
	}
	return false;
}
bool TileMap::TestFalling(const AABB& box) const
{
	return !CollisionY(box.pos + Point(0, box.height), box.width);
}
bool TileMap::CollisionX(const Point& p, int distance) const
{
	int x, y, y0, y1;

	//Calculate the tile coordinates and the range of tiles to check for collision
	x = p.x / TILE_SIZE;
	y0 = p.y / TILE_SIZE;
	y1 = (p.y + distance - 1) / TILE_SIZE;
	
	//Iterate over the tiles within the vertical range
	for (y = y0; y <= y1; ++y)
	{
		//One solid tile is sufficient
		if (IsTileSolid(GetTileIndex(x, y)))
			return true;
	}
	return false;
}
bool TileMap::CollisionY(const Point& p, int distance) const
{
	int x, y, x0, x1;
	Tile tile;

	//Calculate the tile coordinates and the range of tiles to check for collision
	y = p.y / TILE_SIZE;
	x0 = p.x / TILE_SIZE;
	x1 = (p.x + distance - 1) / TILE_SIZE;

	//Iterate over the tiles within the horizontal range
	for (x = x0; x <= x1; ++x)
	{
		tile = GetTileIndex(x, y);

		//One solid or laddertop tile is sufficient
		if (IsTileSolid(tile) || IsTileLadderTop(tile))
			return true;
	}
	return false;
}
bool TileMap::TestOnLadder(const AABB& box, int* px) const
{
	int left, right, bottom;
	int tx1, tx2, ty;
	Tile tile1;
		
	//Control points
	left = box.pos.x;
	right = box.pos.x + box.width-1;
	bottom = box.pos.y + box.height-1;

	//Calculate the tile coordinates
	tx1 = left / TILE_SIZE;
	tx2 = right / TILE_SIZE;
	ty = bottom / TILE_SIZE;
	

	//To be able to climb up or down, both control points must be on ladder
	tile1 = GetTileIndex(tx1, ty);
	if (IsTileLadder(tile1))
	{
		*px = GetLadderCenterPos(left, bottom) - box.width/2;
		return true;
	}
	return false;
}
bool TileMap::TestOnLadderTop(const AABB& box, int* px) const
{
	int left, right, bottom;
	int tx1, tx2, ty;
	Tile tile1;

	//Control points
	left = box.pos.x;
	right = box.pos.x + box.width - 1;
	bottom = box.pos.y + box.height - 1;

	//Calculate the tile coordinates
	tx1 = left / TILE_SIZE;
	tx2 = right / TILE_SIZE;
	ty = bottom / TILE_SIZE;

	//To be able to climb up or down, both control points must be on ladder
	tile1 = GetTileIndex(tx1, ty);
	if (IsTileLadderTop(tile1))
	{
		*px = GetLadderCenterPos(left, bottom) - box.width / 2;
		return true;
	}
	
	return false;
}

bool TileMap::TestOnLadderBottom(const AABB& box, int* px) const
{
	int left, right, bottom;
	int tx1, tx2, ty;
	Tile tile1;
	

//Control points
	left = box.pos.x;
	right = box.pos.x + box.width - 1;
	bottom = box.pos.y + box.height - 1;

	//Calculate the tile coordinates
	tx1 = left / TILE_SIZE;
	tx2 = right / TILE_SIZE;
	ty = bottom / TILE_SIZE;

	//To be able to climb up or down, both control points must be on ladder
	tile1 = GetTileIndex(tx1, ty);
	if (IsTileLadderTop(tile1))
	{
		*px = GetLadderCenterPos(left, bottom) - box.width / 2;
		return true;
	}

	return false;
}

int TileMap::GetLadderCenterPos(int pixel_x, int pixel_y) const
{
	int tx, ty;
	
	tx = pixel_x / TILE_SIZE;
	ty = pixel_y / TILE_SIZE;
	Tile tile = GetTileIndex(tx, ty);

	if (tile == Tile::LADDER_LIANA || tile == Tile::LADDER_LIANA_TOP || tile == Tile::LADDER_LIANA_FLOOR)		return tx * TILE_SIZE + TILE_SIZE;
	
	else
	{
		LOG("Internal error, tile should be a LADDER, coord: (%d,%d), tile type: %d", pixel_x, pixel_y, (int)tile);
		return 0;
	}
}
void TileMap::Render()
{
	Tile tile;
	Rectangle rc;
	Vector2 pos;

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			tile = map[i * width + j];
			if (tile != Tile::AIR)
			{
				pos.x = (float)j * TILE_SIZE;
				pos.y = (float)i * TILE_SIZE;

				if (tile != Tile::WATER)
				{
					rc = dict_rect[(int)tile];
					DrawTextureRec(*img_tiles, rc, pos, WHITE);
				}
				else
				{
					water->Draw((int)pos.x, (int)pos.y);
				}
			}
		}
	}
}
void TileMap::Release()
{
	ResourceManager& data = ResourceManager::Instance(); 
	data.ReleaseTexture(Resource::IMG_TILES);
	if (water !=nullptr)
		water->Release();

	dict_rect.clear();
}