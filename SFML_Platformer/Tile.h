#pragma once
#include "BaseObject.h"
#include "Globals.h"

class Tile: public BaseObject 
{
public:
    Tile();
    void Update() {}
    void HandleEvent(sf::Event event) {}
    void Render(sf::RenderWindow *window);
    void Collided(BaseObject *target) {}
private:
    sf::Texture *texture;
    sf::Sprite *image;
};
