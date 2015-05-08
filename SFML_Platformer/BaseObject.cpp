#include "BaseObject.h"


BaseObject::BaseObject()
{
	ID = -1;

	collidable = false;

	x = 0;
        prevX = 0;
	speedX = 0;
	dirX = 0;
	boundX = 0;

	y = 0;
        prevY = 0;
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

	aggroZone = -1;

	state = -1;
	
}

void BaseObject::InitObject(int ID, bool collidable, float x, float speedX, int dirX, float y, float speedY, int dirY, int boundX, 
			    int boundY, int curFrame, int frameCount, int frameDelay, int frameWidth, int frameHeight, int maxFrame,
                            int animationColumns, int animationRow)
{
	BaseObject::ID = ID;

	BaseObject::collidable = collidable;

	BaseObject::x = x;
        BaseObject::prevX = x;
	BaseObject::speedX = speedX;
	BaseObject::dirX = dirX;
	BaseObject::boundX = boundX;

	BaseObject::y = y;
        BaseObject::prevY = y;
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
        BaseObject::hitBox.setSize(sf::Vector2f(boundX*2, boundY*2));
        BaseObject::hitBox.setOrigin(boundX, boundY);
        BaseObject::hitBox.setFillColor(sf::Color::Blue);
        BaseObject::hitBox.setPosition(x, y);
}

void BaseObject::Update()
{
        prevX = x;
        prevY = y;
	x += speedX * dirX;
	y += speedY * dirY;
        hitBox.move(speedX * dirX, speedY * dirY);
}

bool BaseObject::CheckCollisions(BaseObject *target)
{
	if (x + boundX >= target->x - target->boundX &&
	    x - boundX <= target->x + target->boundX &&
	    y + boundY >= target->y - target->boundY &&
	    y - boundY <= target->y + target->boundY)
		return true;
	else return false;
}

void BaseObject::Collided(BaseObject *target)
{
	//alive = false;
}

void BaseObject::RenderCollision(sf::RenderWindow *window)
{
	window->draw(hitBox);
}
