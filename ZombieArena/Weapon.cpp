#include "Weapon.h"

Weapon::Weapon()
{}

void Weapon::Init(int type, float x, float y)
{
	Weapon::type = type;
	BaseObject::InitObject(WEAPON, true, true, x, 0, 0, y, 0, 0, 10, 10, 0, 0, 0, 0, 0, 0, 0, 0, NULL);
}

void Weapon::Update()
{}

void Weapon::Render()
{
	switch(type)
	{
	case WEAPON_TYPE_ASSLT:
		al_draw_filled_rectangle(x + 15, y + 10, x - 15, y - 10, al_map_rgb(0, 0, 255));
		break;
	case WEAPON_TYPE_RCKT:
		al_draw_filled_rectangle(x + 15, y + 10, x - 15, y - 10, al_map_rgb(0, 255, 0));
		break;
	case WEAPON_TYPE_FLME:
		al_draw_filled_rectangle(x + 15, y + 10, x - 15, y - 10, al_map_rgb(0, 255, 255));
		break;
	}
}

bool Weapon::CheckCollisions(BaseObject *target)
{
	return BaseObject::CheckCollisions(target);
}

void Weapon::Collided(BaseObject *target)
{
	if(target->GetID() == PLAYER)
		alive = false;
}

