#include "BaseObject.h"


BaseObject::BaseObject()
{
	ID = -1;

	type = -1;

	alive = false;
	collidable = false;

	x = 0;
	speedX = 0;
	dirX = 0;
	boundX = 0;

	y = 0;
	speedY = 0;
	dirY = 0;
	boundY = 0;

	curFrame = 0;
	frameCount = 0;
	frameDelay = 0;
	frameWidth = 0;
	frameHeight = 0;
	maxFrame = 0;
	animationColumns = 0;
	animationRow = 0;

	aggroZone = NULL;

	state = NULL;
	
	image = NULL;
}

void BaseObject::InitObject(int ID, bool alive, bool collidable, float x, float speedX, int dirX, float y, float speedY, int dirY, int boundX, 
							int boundY, int curFrame, int frameCount, int frameDelay, int frameWidth, int frameHeight, int maxFrame, int animationColumns, 
							int animationRow, ALLEGRO_BITMAP *image)
{
	BaseObject::ID = ID;

	BaseObject::alive = alive;
	BaseObject::collidable = collidable;

	BaseObject::x = x;
	BaseObject::speedX = speedX;
	BaseObject::dirX = dirX;
	BaseObject::boundX = boundX;

	BaseObject::y = y;
	BaseObject::speedY = speedY;
	BaseObject::dirY = dirY;
	BaseObject::boundY = boundY;

	BaseObject::curFrame = curFrame;
	BaseObject::frameCount = frameCount;
	BaseObject::frameDelay = frameDelay;
	BaseObject::frameWidth = frameWidth;
	BaseObject::frameHeight = frameHeight;
	BaseObject::frameHeight = frameHeight;
	BaseObject::maxFrame = maxFrame;
	BaseObject::animationColumns = animationColumns;
	BaseObject::animationRow = animationRow;
	
	BaseObject::image = image;
}

void BaseObject::Update()
{
	x += speedX * dirX;
	y += speedY * dirY;
}

bool BaseObject::CheckCollisions(BaseObject *target)
{
	if (x + boundX > target->x - target->boundX &&
		x - boundX < target->x + target->boundX &&
		y + boundY > target->y - target->boundY &&
		y - boundY < target->y + target->boundY)
		return true;
	else return false;
}

void BaseObject::Collided(BaseObject *target)
{
	alive = false;
}

void BaseObject::RenderCollision()
{
	al_draw_filled_rectangle(x - boundX, y - boundY, x + boundX, y + boundY, al_map_rgba(255, 0, 255, 75));
}