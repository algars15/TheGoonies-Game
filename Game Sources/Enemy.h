#pragma once
#include "Entity.h"
#include "TileMap.h"

//Representation model size: 8X8
#define ENEMY_FRAME_SIZE		16

//Logical model size:  4X8
#define ENEMY_WIDTH	    12
#define ENEMY_HEIGHT	16

//Horizontal speed and vertical speed while falling down
#define ENEMY_SPEED			1

// Enemy logical states 
enum class EnemyState { WALKING_LEFT, WALKING_RIGHT };

// Enemy animation states
enum class EnemyAnim {
    WALKING_LEFT,
    WALKING_RIGHT,
    NUM_ANIMATIONS
};

class Enemy : public Entity {
public:
    Enemy(const Point& position, EnemyState initialState);

    ~Enemy();

    AppStatus Initialize();
    void SetTileMap(TileMap* tilemap);

    void Update();

    void Release();

    void DrawDebug(const Color& col) const;

    int EXPPoints() const;

private:
  
    void Move();


    
    void SetAnimation(int id);
    EnemyAnim GetAnimation();

    EnemyState state;
    TileMap* map;
};