#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <math.h>


const int WIDTH = 640;
const int HEIGHT = 480;

enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE};
enum ID{PLAYER, ENEMY, BULLET, WEAPON, MISC};
enum WEAPON_TYPE{WEAPON_TYPE_ASSLT, WEAPON_TYPE_RCKT, WEAPON_TYPE_FLME};
enum BULLET_TYPE{BULLET_TYPE_DEF, BULLET_TYPE_ASSLT, BULLET_TYPE_RCKT, BULLET_TYPE_FLME};
enum ENEMY_TYPE{ENEMY_TYPE_ZOMBIE, ENEMY_TYPE_SUB, ENEMY_TYPE_BOSS};
enum POWER_TYPE{POWER_TYPE_TIME, POWER_TYPE_HEALTH, POWER_TYPE_ARMOR};
enum ENEMYSTATES{IDLE, CHASE};
enum GAMESTATES{MENU, PLAY, WARP, GAMEOVER};
enum DIRECTION{NORTH, SOUTH, EAST, WEST, NORTHWEST, NORTHEAST, SOUTHWEST, SOUTHEAST};
enum WEAPON{DEFAULT, ASSAULT, ROCKET, FLAME};
enum POWER{TIME, HEALTH, ARMOR};
