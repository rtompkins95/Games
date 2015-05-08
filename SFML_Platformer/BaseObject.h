#pragma once 
#include <cstddef>
#include <SFML/Graphics.hpp>

class BaseObject
{
protected:
		int ID;
		bool collidable;

		float x;		
                float prevX;
		float speedX;
		float dirX;
		float boundX;

		float y;
                float prevY;
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
                
                sf::RectangleShape hitBox;

public:
	BaseObject();
	void virtual InitObject(int ID, bool collidable, float x, float speedX, int dirX, float y, float speedY, int dirY, int boundX, 
		        int boundY, int curFrame, int frameCount, int frameDelay, int frameWidth, int frameHeight, int maxFrame, 
                        int animationColumns, int animationRow);	
	
	void SetID(int ID) {BaseObject::ID = ID;}
	int GetID() {return BaseObject::ID;}

	void SetX(float x) {BaseObject::x = x;}
        void SetPrevX(float prevX) {BaseObject::prevX = prevX;}
        float GetPrevX() {return BaseObject::prevX;}
	float GetX() {return BaseObject::x;}
	float GetBoundX() {return BaseObject::boundX;}
        void SetBoundX(float boundX) {BaseObject::boundX = boundX;}
	void SetSpeedX(float speedX) {BaseObject::speedX = speedX;}
	float GetSpeedX() {return BaseObject::speedX;}
	void SetDirectionX(int dirX) {BaseObject::dirX = dirX;}
	int GetDirectionX() {return BaseObject::dirX;}

	void SetY(float y) {BaseObject::y = y;}
	float GetY() {return BaseObject::y;}
        void SetPrevY(float prevY) {BaseObject::prevY = prevY;}
        float GetPrevY() {return BaseObject::prevY;}  
	float GetBoundY() {return BaseObject::boundY;}
        void SetBoundY(float boundY) {BaseObject::boundY = boundY;}
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
        void virtual HandleEvent(sf::Event event)=0;
	void virtual Render(sf::RenderWindow *window)=0;
	bool virtual CheckCollisions(BaseObject *target);
	bool Collidable() {return BaseObject::collidable;}
	void virtual Collided(BaseObject *target);
	void RenderCollision(sf::RenderWindow *window);
};
