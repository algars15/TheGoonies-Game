#pragma once
#include "Entity.h"
#include "TileMap.h"

//Representation model size: 8X8
#define ENEMY_FRAME_SIZE		16

//Logical model size:  4X8
#define ENEMY_WIDTH	    4
#define ENEMY_HEIGHT	8

//Horizontal speed and vertical speed while falling down
#define ENEMY_SPEED			1

// Estados l�gicos del enemigo
enum class EnemyState { WALKING_LEFT, WALKING_RIGHT };

// Estados de animaci�n del enemigo
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
    // Mec�nicas del enemigo
    void Move();


    // Gesti�n de animaciones
    void SetAnimation(int id);
    EnemyAnim GetAnimation();

    EnemyState state;
    TileMap* map;
};


