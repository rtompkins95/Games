#include "Tile.h"

Tile::Tile() 
{
    texture = NULL;
    image = NULL;
}

void Tile::Render(sf::RenderWindow *window)
{
    if(image)
        window->draw(*image);
    else
    {
        RenderCollision(window);
    }
}
