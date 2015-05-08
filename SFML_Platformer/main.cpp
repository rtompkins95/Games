#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Player.h"
#include "Tile.h"
#include "Level.h"
#include "Enemy.h"
#include <iostream>

const int CENTER_X = SCREEN_WIDTH / 2;
const int CENTER_Y = SCREEN_HEIGHT / 2;

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "My Window");
    Player player;
    BaseObject *p = &player;
    p->InitObject(1, true, 0, 5, 0, 0, 5, 0, 32, 32, 0, 0, 0, 0, 0, 0, 0, 0);
    player.SetJumpCounter(25);
    p->SetSpeedX(5);
    p->SetSpeedY(5);
    sf::View view = window.getDefaultView();
    player.Init("", &view, 0, 0, 32, 32);
    player.SetJumpCounter(25);
    Level l;
    l.Init("ex.txt");
    l.AddObject(p);
    std::cout << "pid: " << p << "\n";
    sf::Clock clock;
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            switch(event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Escape)
                        window.close();
                    if(event.key.code == sf::Keyboard::L)
                        l.Init("ex.txt");
                    break;
                default:
                    break;
            }
            l.HandleEvent(event);
        }
        l.Update();
        l.CheckCollisions();
        l.Render(&window);
        window.display();
        window.clear(sf::Color::Black); 
    } 
    return 0;
}
