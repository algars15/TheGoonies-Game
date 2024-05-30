#include "Enemy.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Globals.h"
#include <raymath.h>

Enemy::Enemy(const Point& position, EnemyState initialState) :
    Entity(position, ENEMY_WIDTH, ENEMY_HEIGHT, ENEMY_FRAME_SIZE, ENEMY_FRAME_SIZE)
{
    state = initialState;
    map = nullptr;
}

Enemy::~Enemy()
{
}

AppStatus Enemy::Initialize()
{
    int i;
    const int n = ENEMY_FRAME_SIZE;

    ResourceManager& data = ResourceManager::Instance();
    if (data.LoadTexture(Resource::IMG_ENEMY, "images/Enemy.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }

    render = new Sprite(data.GetTexture(Resource::IMG_ENEMY));
    if (render == nullptr)
    {
        LOG("Failed to allocate memory for enemy sprite");
        return AppStatus::ERROR;
    }

    Sprite* sprite = dynamic_cast<Sprite*>(render);
    sprite->SetNumberAnimations(2); 

    sprite->SetAnimationDelay((int)EnemyAnim::WALKING_LEFT, ANIM_DELAY);  
    for (i = 0; i < 2; ++i)
        sprite->AddKeyFrame((int)EnemyAnim::WALKING_LEFT, { (float)i * n, 0, n, n });

    sprite->SetAnimationDelay((int)EnemyAnim::WALKING_RIGHT, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        sprite->AddKeyFrame((int)EnemyAnim::WALKING_RIGHT, { (float)i * n, 0, -n, n });

    sprite->SetAnimation((int)EnemyAnim::WALKING_LEFT); //Start animation walking left

    return AppStatus::OK;
}


void Enemy::SetTileMap(TileMap* tilemap)
{
    map = tilemap;
}

void Enemy::Update()
{

    Move();
}

void Enemy::Release()
{
    ResourceManager& data = ResourceManager::Instance();
    data.ReleaseTexture(Resource::IMG_ENEMY);

    render->Release();
}

void Enemy::DrawDebug(const Color& col) const
{
    Entity::DrawHitbox(pos.x, pos.y, width, height, col);

    DrawText(TextFormat("Position: (%d,%d)\nSize: %dx%d\nFrame: %dx%d", pos.x, pos.y, width, height, frame_width, frame_height), 18 * 16, 0, 8, LIGHTGRAY);
    DrawPixel(pos.x, pos.y, WHITE);
}

int Enemy::EXPPoints() const
{
    return 20;
}

void Enemy::Move()
{
    AABB box;
    int prev_x = pos.x;

    
    if (state == EnemyState::WALKING_LEFT){   
        pos.x += -ENEMY_SPEED; 
        box = GetHitbox();
        SetAnimation((int)EnemyAnim::WALKING_LEFT);
       
        if (map->TestCollisionWallLeft(box))
        {
            pos.x = prev_x;
            state = EnemyState::WALKING_RIGHT; 
        }
    }
 
    else if (state == EnemyState::WALKING_RIGHT)
    {
        pos.x += ENEMY_SPEED; 
        box = GetHitbox();
        SetAnimation((int)EnemyAnim::WALKING_RIGHT);
       
        if (map->TestCollisionWallRight(box))
        {
            pos.x = prev_x; 
            state = EnemyState::WALKING_LEFT; 
        }
    }
}

void Enemy::SetAnimation(int id)
{
    Sprite* sprite = dynamic_cast<Sprite*>(render);
    sprite->SetAnimation(id);
}
EnemyAnim Enemy::GetAnimation()
{
    Sprite* sprite = dynamic_cast<Sprite*>(render);
    return (EnemyAnim)sprite->GetAnimation();
}