#include "Assault.h"

Assault::Assault(float x, float y, int direction)
{	
	Assault::direction = direction;
	Bullet::InitObject(BULLET, false, true, x, 7, 1, y, 7, 1, 10, 2, 0, 0, 0, 0, 0, 0, 0, 0, NULL);
}

void Assault::Update()
{
	Bullet::Update();
}

void Assault::Render()
{
	switch(direction)
	{
	case NORTH:
		al_draw_line(x, y - 10, x, y - 20, al_map_rgb(255, 0, 255), 2);
		break;
	case SOUTH:
		al_draw_line(x, y + 10, x, y + 20, al_map_rgb(255, 0, 255), 2);
		break;
	case EAST:
		al_draw_line(x + 10, y, x + 20, y, al_map_rgb(255, 0, 255), 2);
		break;
	case WEST:
		al_draw_line(x - 10, y, x - 20, y, al_map_rgb(255, 0, 255), 2);
		break;
	case NORTHEAST:
		
		break;
	case NORTHWEST:
		
		break;
	case SOUTHEAST:
		
		break;
	case SOUTHWEST:
		
		break;
	}	
}