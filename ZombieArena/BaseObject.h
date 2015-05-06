#pragma once 
#include "Globals.h"

class BaseObject
{
protected:
		int ID;

		int type;

		bool alive;
		bool collidable;

		float x;		
		float speedX;
		float dirX;
		float boundX;

		float y;
		float speedY;
		float dirY;		
		float boundY;		

		int curFrame;
		int frameCount;
		int frameDelay;
		int frameWidth;
		int frameHeight;
		int maxFrame;
		int animationColumns;
		int animationRow;

		int state;

		float aggroZone;

		ALLEGRO_BITMAP * image;

public:
	BaseObject();
	void InitObject(int ID, bool alive, bool collidable, float x, float speedX, int dirX, float y, float speedY, int dirY, int boundX, 
					 int boundY, int curFrame, int frameCount, int frameDelay, int frameWidth, int frameHeight, int maxFrame, int animationColumns, 
					 int animationRow, ALLEGRO_BITMAP *image);	
	
	void SetID(int ID) {BaseObject::ID = ID;}
	int GetID() {return BaseObject::ID;}

	int GetType() {return BaseObject::type;}
	void SetType(int type) {BaseObject::type = type;}

	bool GetAlive() {return BaseObject::alive;}
	void SetAlive(bool alive) {BaseObject::alive = alive;}

	void SetX(float x) {BaseObject::x = x;}
	float GetX() {return BaseObject::x;}
	float GetBoundX() {return BaseObject::boundX;}

	void SetSpeedX(float speedX) {BaseObject::speedX = speedX;}
	float GetSpeedX() {return BaseObject::speedX;}

	void SetDirectionX(int dirX) {BaseObject::dirX = dirX;}
	int GetDirectionX() {return BaseObject::dirX;}

	void SetY(float y) {BaseObject::y = y;}
	float GetY() {return BaseObject::y;}
	float GetBoundY() {return BaseObject::boundY;}

	void SetSpeedY(float speedY) {BaseObject::speedY = speedY;}
	float GetSpeedY() {return BaseObject::speedY;}

	void SetDirectionY(int dirY) {BaseObject::dirY = dirY;}
	int GetDirectionY() {return BaseObject::dirY;}

	void SetCollidable(bool collidable) {BaseObject::collidable = collidable;}
	bool GetCollidable() {return BaseObject::collidable;}

	int GetState() {return BaseObject::state;}
	void SetState(int state) {BaseObject::state = state;}

	float GetAggroZone() {return BaseObject::aggroZone;}
	void SetAggroZone(float aggroZone) {BaseObject::aggroZone = aggroZone;}

	void virtual Update();
	void virtual Render()=0;
	bool virtual CheckCollisions(BaseObject *target);
	bool Collidable() {return BaseObject::collidable;}
	void virtual Collided(BaseObject *target);
	void RenderCollision();
};