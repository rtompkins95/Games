#pragma once
#include "Globals.h"
#include "BaseObject.h"

class Bullet: public BaseObject
{
private: 
	int direction;	
	int bulletDelay;
	int bulletCount;
public:
	Bullet(int type, float x, float y, int direction);
	void Init();
	void FireBullet();
	void virtual Update();
	void virtual Render();
	bool CheckCollisions(BaseObject *target);
	void Collided(BaseObject *target);
};