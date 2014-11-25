#include "Power.h"

Power::Power()
{}

void Power::Init(int type, float x, float y)
{
	Power::type = type;
	
	BaseObject::InitObject(MISC, true, true, x, 0, 0, y, 0, 0, 10, 10, 0, 0, 0, 0, 0, 0, 0, 0, NULL);
}

void Power::Update()
{

}

void Power::Render()
{
	if(type == TIME)
		al_draw_filled_rectangle(x + boundX, y + boundY, x - boundX, y - boundY, al_map_rgb(100, 0, 255));
}

bool Power::CheckCollisions(BaseObject *target)
{
	return BaseObject::CheckCollisions(target);
}

void Power::Collided(BaseObject *target)
{
	if(target->GetID() == PLAYER)
		alive = false;
}