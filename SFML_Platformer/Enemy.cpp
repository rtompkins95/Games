#include "Enemy.h"

Enemy::Enemy() 
{
    walk_counter = 0;
    prevX = 0;
    prevY = 0;
    collided_on_frame = false;
    in_air = false;
    gravity = GRAVITY;
}

void Enemy::InitObject(int ID, bool collidable, float x, float speedX, int dirX, float y, float speedY, 
                       int dirY, int boundX, int boundY, int curFrame, int frameCount, int frameDelay, 
                       int frameWidth, int frameHeight, int maxFrame, int animationColumns, int animationRow)
{
    BaseObject::InitObject(ID, collidable, x, speedX, dirX, y, speedY, dirY, boundX, boundY, curFrame, 
                           frameCount, frameDelay, frameWidth, frameHeight, maxFrame, animationColumns, 
                           animationRow);
    this->hitBox.setFillColor(sf::Color::Red);
    walk_counter = 100;
}
void Enemy::Init() 
{
    this->hitBox.setFillColor(sf::Color::Red);
    walk_counter = 100;
}

void Enemy::Render(sf::RenderWindow *window) 
{
    window->draw(hitBox);
}

void Enemy::Update()
{
    prevX = x;
    prevY = y;
    walk_counter--;
    if(walk_counter <= 0) 
    {
        speedX = -speedX;
        walk_counter = 100;
    }
    x += speedX;
    if(in_air)// && !jump)
    {
        y+=gravity;
    }
    /*if(jump) 
    {
        jump = false;
        in_air = true;
    }*/
    /*if(jump_counter > 0 && jump)
    {
        in_air = true;
        jump_counter--;
        y -= speedY;
    }*/
    /*else if(jump_counter <= 0) 
    {
        jump_counter = JUMP_TIME;
        jump = false;
    }*/
    if((y + boundY < SCREEN_HEIGHT) && (!collided_on_frame))  
    {
        in_air = true;
    }
    else
    {
        if(y + boundY > SCREEN_HEIGHT)
            y = SCREEN_HEIGHT - boundY;
        in_air = false;
    }
    hitBox.setPosition(x, y);

}

void Enemy::HandleEvent(sf::Event event)
{
   (void)event;
}

bool Enemy::CheckCollisions(BaseObject *target)
{
    bool result = BaseObject::CheckCollisions(target);
    if(!result)
    {
        collided_on_frame = false;
    }
    return result;
}

void Enemy::Collided(BaseObject *target)
{
    if((prevY + boundY) <= (target->GetY() - target->GetBoundY()))
    {
        collided_on_frame = true;
        y = target->GetY() - target->GetBoundY() - boundY;
        in_air = false;
    }
    else if(prevY - boundY >= target->GetY() + target->GetBoundY())
    {
        y = target->GetY() + target->GetBoundY() + boundY;
    }
    else if((prevX - boundX) >= (target->GetX() + target->GetBoundX()))
    {
        x = target->GetX() + target->GetBoundX() + boundX;
    }
    else if((prevX + boundX) <= (target->GetX() - target->GetBoundX()))
    {
        x = target->GetX() - target->GetBoundX() - boundX;
    }
}
