
#pragma once
#include <raylib.h>
#include "Point.h"
#include "ResourceManager.h"
#include "RenderComponent.h"
#include "AABB.h"

class Entity
{
public:
	Entity(const Point& p, int width, int height);
	Entity(const Point& p, int width, int height, int frame_width, int frame_height);
	virtual ~Entity();

	void SetPos(const Point& p);
	int GetY() const { return pos.y; }
	int GetX() const { return pos.x; }
	void Update();
	AABB GetHitbox() const;


	//Draw representation model
	void Draw() const;
	void DrawTint(const Color& col) const;

	//Draw logical/physical model (hitbox)
	void DrawHitbox(const Color& col) const;
	void DrawHitbox(int x, int y, int w, int h, const Color& col) const;

	bool NextLevel() const;

	bool PrevLevel() const;

	bool NextLevelY() const;

	bool PrevLevelY() const;

protected:
	Point GetRenderingPosition() const;

	//Logical/physical model
	Point pos, dir;
	int width, height;

	//Representation model
	int frame_width, frame_height;

	RenderComponent* render;
};