#include "Level.h"

Level::Level() 
{
    std::list<BaseObject *> objects;
}
void Level::Init(char *file_name) 
{
    std::ifstream lfile;
    std::string line;
    char buff[256];
    std::stringstream ss;
    lfile.open(file_name);
    int index_x = 0, index_y = 0;
    BaseObject *tile; //needed for obscure c++ syntax standards
    Enemy *e;
    while(std::getline(lfile, line))
    {
        ss << line;
        index_y++;
        index_x = 0;
        while(ss.getline(buff, 2, ' '))
        {
            int i = std::stoi(buff, nullptr, 10);
            switch(i)
            {
                case 0:
                    break;
                case 1:
                    tile = new Tile();
                    //std::cout << "x: " << index_x * TILE_SIZE * 2 << "\n" << "y: " << index_y * TILE_SIZE * 2 << "\n";
                    tile->InitObject(0, true, index_x * TILE_SIZE * 2 + TILE_SIZE, 0, 0, index_y * TILE_SIZE * 2,
                                     0, 0, TILE_SIZE, TILE_SIZE, 0, 0, 0, 0, 0, 0, 0, 0);
                    objects.push_back(tile);                    
                    break;
                case 2:
                    tile = new Enemy();
                    tile->InitObject(0, true, index_x * TILE_SIZE * 2 + TILE_SIZE, 0, 0, index_y * TILE_SIZE * 2,
                                     0, 0, TILE_SIZE, TILE_SIZE, 0, 0, 0, 0, 0, 0, 0, 0);
                    objects.push_back(tile);
                    break;
                default:
                    break;
            }
            index_x++;
        }
        ss.clear();
    }
    lfile.close(); 
}

void Level::Render(sf::RenderWindow *window) 
{
    std::list<BaseObject *>::iterator i;
    for(i = objects.begin(); i != objects.end(); i++) 
        (*i)->Render(window);
}

void Level::HandleEvent(sf::Event event) 
{
    std::list<BaseObject *>::iterator i;
    for(i = objects.begin(); i != objects.end(); i++)
        (*i)->HandleEvent(event);
}

bool Level::Cleared() {}

void Level::Update() 
{
    std::list<BaseObject *>::iterator i;
    for(i = objects.begin(); i != objects.end(); i++)
        (*i)->Update(); 
}

void Level::CheckCollisions()
{
    std::list<BaseObject *>::iterator i;
    std::list<BaseObject *>::iterator j;
    for(i = objects.begin(); i != objects.end(); i++)
    {
        for(j = i; j != objects.end(); j++)
        {
            if((*j) == (*i)) 
                continue;
            //if((*j)->GetID() == (*i)->GetID())
                //continue;
            //std::cout << "i: " << *i << "\n";
            //std::cout << "j: " << *j << "\n";
            //std::cout << ((*j) == (*i)) << "\n";
            if((*i)->CheckCollisions(*j) || (*j)->CheckCollisions(*i)) // every object must check, because state also depends on missed collisions
            {
                (*i)->Collided(*j);
                (*j)->Collided(*i);
            }

        }
    }
}

