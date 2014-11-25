#pragma once
#include "Globals.h"
#include "BaseObject.h"

class Enemy: public BaseObject
{
private:
	float health;
public:
	Enemy();
	void Init(int type, float x, float y);
	void StartEnemy();
	float GetAggroZone() {return Enemy::aggroZone;}	
	void Update(float angle);
	void Render();
	void RenderAggro();
	bool CheckCollisions(BaseObject *target);
	void Collided(BaseObject *target);

};