	#include "EnemyManager.h"
#include "Slime.h"


EnemyManager::~EnemyManager()
{
	Release();
}
AppStatus EnemyManager::Initialise()
{
	ResourceManager& data = ResourceManager::Instance();
	if (data.LoadTexture(Resource::IMG_ENEMIES, "images/Skeleton_enemy.png") != AppStatus::OK)
	{
		LOG("Failed to load enemies sprite texture");
		return AppStatus::ERROR;
	}

	return AppStatus::OK;
}
void EnemyManager::Add(const Point& pos, EnemyType type, const AABB& area, Look look)
{
	Enemy *enemy;
	
	if(type == EnemyType::SLIME)
	{
		enemy = new Slime(pos, SLIME_PHYSICAL_WIDTH, SLIME_PHYSICAL_HEIGHT, SLIME_FRAME_SIZE, SLIME_FRAME_SIZE);
	}
	else
	{
		LOG("Internal error: trying to add a new enemy with invalid type");
		return;
	}
		
	enemy->Initialise(look, area);
	enemies.push_back(enemy);
}
AABB EnemyManager::GetEnemyHitBox(const Point& pos, EnemyType type) const
{
	int width, height;
	if (type == EnemyType::SLIME)
	{
		width = SLIME_PHYSICAL_WIDTH;
		height = SLIME_PHYSICAL_HEIGHT;
	}
}
	void EnemyManager::Draw() const
	{
		for (const Enemy* enemy : enemies)
			enemy->Draw();
	}
	void EnemyManager::DrawDebug() const
	{
		for (const Enemy* enemy : enemies)
		{
			enemy->DrawVisibilityArea(DARKGRAY);
			enemy->DrawHitbox(RED);
		}
	}
	void EnemyManager::Release()
	{
		for (Enemy* enemy : enemies)
			delete enemy;
		enemies.clear();
	}