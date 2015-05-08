#pragma once
#include "BaseObject.h"
#include "Globals.h"

class Enemy: public BaseObject
{
public:
       Enemy();
       void InitObject(int ID, bool collidable, float x, float speedX, int dirX, float y, float speedY, int dirY, int boundX,
                        int boundY, int curFrame, int frameCount, int frameDelay, int frameWidth, int frameHeight, int maxFrame,
                        int animationColumns, int animationRow);
       void Init();
       void Render(sf::RenderWindow *window);
       void Update();
       void HandleEvent(sf::Event event);
       bool CheckCollisions(BaseObject *target);
       void Collided(BaseObject *target);
       
private:
        int walk_counter;
        bool in_air;
        int gravity;
        bool collided_on_frame;
};
