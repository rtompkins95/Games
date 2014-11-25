#pragma once
#include "Globals.h"
#include "BaseObject.h"
#include "Bullet.h"

class Assault: public Bullet
{
public:
	Assault(float x, float y, int direction);
	void Update();
	void Render();
};