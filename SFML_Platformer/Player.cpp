#include "Player.h"
#include <iostream>

Player::Player()
{
    lives = 0;
    sprite = NULL;
    texture = NULL;
    gravity = 0;
    in_air = true;
    lives = 0;
    jump = false;
    collided_on_frame = false;
    BaseObject::hitBox.setFillColor(sf::Color::Green);

}

void Player::Init(char *file_name, sf::View *view, float x, float y, float boundX, float boundY) 
{
    (void)file_name;
    this->x = x;
    this->y = y;
    this->boundX = boundX;
    this->boundY = boundY;
    gravity = GRAVITY;
    in_air = true;
    lives = 3;
    jump = false;
    jump_counter = 100;
    collided_on_frame = false;
    BaseObject::hitBox.setFillColor(sf::Color::Green);
    this->view = view;
}

void Player::Render(sf::RenderWindow *window) 
{
    window->setView(*view);
    RenderCollision(window);
}

void Player::Collided(BaseObject *target) 
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
        jump_counter = 0;
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

void Player::Update() {
    prevX = x;
    prevY = y;
    x += speedX;
    if(in_air && !jump)
    {   
        y+=gravity;
    }
    /*if(jump) 
    {
        jump = false;
        in_air = true;
    }*/
    if(jump_counter > 0 && jump)
    {
        in_air = true;
        jump_counter--;
        y -= speedY;
    }
    else if(jump_counter <= 0) 
    {
        jump_counter = JUMP_TIME;
        jump = false;
    }
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
    view->setCenter(x, y);
    //std::cout << "collided on frame: " << collided_on_frame << "\n"; 
    //std::cout << "in air: " << in_air << "\n";
} 

void Player::HandleEvent(sf::Event event) 
{
    //if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
        //y -= speedY;
    //if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        speedX = -P_SPEEDX;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))  
        speedX = P_SPEEDX; 
    else speedX = 0;
    if(event.key.code == sf::Keyboard::Space && !in_air) 
    {
        jump = true;
    }
}

bool Player::CheckCollisions(BaseObject *target) 
{
    bool result = BaseObject::CheckCollisions(target);
    //std::cout << "before result: \n\n\n";
    //std::cout << target << "\n";
    if(!result) 
    {
        //std::cout << "collided and false \n\n\n\n\n";
        collided_on_frame = false;
    }
    return result;
}
