#pragma once
#include "BaseObject.h"
#include <string>
#include "Globals.h"

class Player: public BaseObject 
{
public:
       Player();
       void Init(char *file_name, sf::View *view, float x, float y, float boundX, float boundY);
       void Render(sf::RenderWindow *window);
       void Update();
       void HandleEvent(sf::Event event);
       bool CheckCollisions(BaseObject *target);
       void Collided(BaseObject *target);
       void SetJumpCounter(int jump_counter) {Player::jump_counter = jump_counter;}
       int GetJumpCounter() {return jump_counter;}
private:
       int lives;
       int jump_counter;
       bool in_air;
       bool jump;
       bool collided_on_frame;
       int gravity;
       sf::View *view;
       sf::Texture *texture;
       sf::Sprite *sprite;
};
