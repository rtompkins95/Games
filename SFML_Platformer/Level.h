#pragma once
#include <iostream>
#include <sstream>
#include <list>
#include <string>
#include <fstream>
#include "Globals.h"
#include "BaseObject.h"
#include "Tile.h"
#include "Enemy.h"

class Level 
{
public:
       Level();
       void Init(char *file_name);
       void Render(sf::RenderWindow *window);
       void CheckCollisions();
       void AddObject(BaseObject *o) {objects.push_back(o);}
       void virtual HandleEvent(sf::Event event);
       bool virtual Cleared();
       void virtual Update();
private:
       std::list<BaseObject *> objects;
};
