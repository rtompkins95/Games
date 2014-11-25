#include "Bullet.h"


Bullet::Bullet(int type, float x, float y, int direction)
{
	Bullet::type = type;
	Bullet::direction = direction;

	if(type == BULLET_TYPE_DEF)
		BaseObject::InitObject(BULLET, false, true, x, 7, 1, y, 7, 1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, NULL);
	if(type == BULLET_TYPE_ASSLT)
		BaseObject::InitObject(BULLET, false, true, x, 7, 1, y, 7, 1, 2, 10, 0, 0, 0, 0, 0, 0, 0, 0, NULL);
	if(type == BULLET_TYPE_RCKT)
		BaseObject::InitObject(BULLET, false, true, x, 7, 1, y, 7, 1, 20, 10, 0, 0, 0, 0, 0, 0, 0, 0, NULL);
	if(type == BULLET_TYPE_FLME)
		BaseObject::InitObject(BULLET, false, true, x, 7, 1, y, 7, 1, 50, 20, 0, 0, 0, 0, 0, 0, 0, 0, NULL);

}

void Bullet::Init()
{}

void Bullet::FireBullet()
{
	alive = true;
}

void Bullet::Update()
{	
	switch(direction)
	{
	case NORTH:
		y -= speedY * dirY;
		break;
	case SOUTH:
		y += speedY * dirY;
		break;
	case EAST:
		x += speedX * dirX;
		break;
	case WEST:
		x -= speedX * dirX;
		break;
	case NORTHEAST:
		x += speedX * dirX;
		y += speedY * dirY;
		break;
	case NORTHWEST:
		x += speedX * dirX;
		y -= speedY * dirY;
		break;
	case SOUTHEAST:
		x += speedX * dirX;
		y += speedY * dirY;
		break;
	case SOUTHWEST:
		x -= speedX * dirX;
		y += speedY * dirY;
		break;
	}
	if(x + boundX > WIDTH || x - boundX < 0 ||
		y + boundY > HEIGHT || y - boundY < 0)
		alive = false;
}

void Bullet::Render()
{
	switch(type)
	{
	case BULLET_TYPE_DEF:
		al_draw_filled_circle(x, y, 2, al_map_rgb(255, 255, 255));
		break;
	case BULLET_TYPE_ASSLT:
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
		}
		break;
	case BULLET_TYPE_RCKT:
		switch(direction)
		{
		case NORTH:
			al_draw_line(x - boundY, y - boundX, x + boundY, y - boundX, al_map_rgb(255, 0, 255), 2);
			break;
		case SOUTH:
			al_draw_line(x, y + boundY, x, y + boundY * 2, al_map_rgb(255, 0, 255), 2);
			break;
		case EAST:
			al_draw_line(x + boundX, y, x + boundX * 2, y, al_map_rgb(255, 0, 255), 2);
			break;
		case WEST:
			al_draw_line(x - 10, y, x - 20, y, al_map_rgb(255, 0, 255), 2);
			break;
		}
		break;
	case BULLET_TYPE_FLME:
		switch(direction)
		{
		case NORTH:
			al_draw_filled_rectangle(x - boundX, y - boundX, x + boundX, y - boundY * 2, al_map_rgb(255, 0, 0));
			break;
		case SOUTH:
			al_draw_filled_rectangle(x - boundX, y + boundX, x + boundX, y + boundY * 2, al_map_rgb(255, 0, 0));
			break;
		case EAST:
			al_draw_filled_rectangle(x + boundX, y - boundX, x + boundX * 2, y + boundY, al_map_rgb(255, 0, 0));
			break;
		case WEST:
			al_draw_filled_rectangle(x - boundX, y - boundX, x - boundX * 2, y + boundY, al_map_rgb(255, 0, 0));
			break;
		}
		break;
	}
	
}

bool Bullet::CheckCollisions(BaseObject *target)
{
	return BaseObject::CheckCollisions(target);
}

void Bullet::Collided(BaseObject *target)
{
	if(target->GetID() == ENEMY)
		alive = false;
}
