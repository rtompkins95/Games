/*

		Allegro 5 Shell Application v1.1
			by Mike Geig

		This code is provided for education purposes and comes with no warantee
		either implicit or explicit.

		This code is free to use however you see fit.
*/

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <list> 
#include <math.h>
#include "Globals.h"
#include "BaseObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Weapon.h"
#include "Power.h"


bool keys[] = {false, false, false, false, false};
float CheckDistance(float x1, float y1, float x2, float y2);
float AngleToTarget(float x1, float y1, float x2, float y2);
void ChangeState(int &state, int newState);
std::list <BaseObject *> objects;
std::list <BaseObject *>:: iterator iter;
std::list <BaseObject *>:: iterator iter2;
std::list <Enemy *> enemies;
std::list <Enemy *>::iterator enemyIter;

int main(int argc, char **argv)
{
	//==============================================
	//SHELL VARIABLES
	//==============================================
	bool done = false;
	bool render = false;

	float gameTime = 0;
	int frames = 0;
	int gameFPS = 0;

	//==============================================
	//PROJECT VARIABLES
	//==============================================
		Player *player = new Player();		
		int state = -1;
		

	//==============================================
	//ALLEGRO VARIABLES
	//==============================================
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer;
	ALLEGRO_FONT *font18;
	ALLEGRO_BITMAP *playerImage = NULL;
	ALLEGRO_BITMAP *bgImage = NULL;
	ALLEGRO_BITMAP *menuScreen = NULL;
	ALLEGRO_BITMAP *gameOverScreen = NULL;
	
	//==============================================
	//ALLEGRO INIT FUNCTIONS
	//==============================================
	if(!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(WIDTH, HEIGHT);			//create our display object

	if(!display)										//test display object
		return -1;

	//==============================================
	//ADDON INSTALL
	//==============================================
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();


	//==============================================
	//PROJECT INIT
	//==============================================
	font18 = al_load_font("arial.ttf", 18, 0);

	playerImage = al_load_bitmap("ZombiePlayerSpriteSheet.png");
	al_convert_mask_to_alpha(playerImage, al_map_rgb(0, 0, 248));

	player->Init(playerImage);	
	objects.push_back(player);

	bgImage = al_load_bitmap("RandomGame.png");
	menuScreen = al_load_bitmap("ZombieArena.png");
	gameOverScreen = al_load_bitmap("GameOver.png");
	
	//==============================================
	//TIMER INIT AND STARTUP
	//==============================================
	srand(time(NULL));
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);
	gameTime = al_current_time();
	ChangeState(state, MENU);
	
	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//==============================================
		//INPUT
		//==============================================
		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{						
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_R:
				if(state == PLAY)
					ChangeState(state, WARP);
				break;
			case ALLEGRO_KEY_Y:
				ChangeState(state, PLAY);
				break;			
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;				
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;				
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				if(state == MENU)
				{
					ChangeState(state, PLAY);
				}
				if(state == PLAY)
				{
					if(player->GetWeapon() == DEFAULT) // && player->GetAmmo() > 0)
					{						
						player->SetBulletDelay(15);
						Bullet *bullet = new Bullet(BULLET_TYPE_DEF, player->GetX(), player->GetY(), player->GetDirection()); 
						bullet->FireBullet();
						objects.push_back(bullet);
					}
					if(player->GetWeapon() == ASSAULT && player->GetAmmo() > 0)
					{
						player->DecrementAmmo();
						player->SetBulletDelay(10);
						Bullet *bullet = new Bullet(BULLET_TYPE_ASSLT, player->GetX(), player->GetY(), player->GetDirection()); 
						bullet->FireBullet();
						objects.push_back(bullet);
					}
					if(player->GetWeapon() == FLAME)
					{
						Bullet *bullet = new Bullet(BULLET_TYPE_FLME, player->GetX(), player->GetY(), player->GetDirection()); 
						bullet->FireBullet();
						objects.push_back(bullet);
					}
					if(player->GetWeapon() == ROCKET)
					{
						Bullet *bullet = new Bullet(BULLET_TYPE_RCKT, player->GetX(), player->GetY(), player->GetDirection()); 
						bullet->FireBullet();
						objects.push_back(bullet);
					}

				}
				if(state == WARP)
				{
					if(player->GetWeapon() == DEFAULT)
					{
						player->SetBulletDelay(15);
						Bullet *bullet = new Bullet(BULLET_TYPE_DEF, player->GetX(), player->GetY(), player->GetDirection()); 
						bullet->FireBullet();
						objects.push_back(bullet);
					}
					else if(player->GetWeapon() == ASSAULT)
					{
						player->SetBulletDelay(10);
						Bullet *bullet = new Bullet(BULLET_TYPE_ASSLT, player->GetX(), player->GetY(), player->GetDirection()); 
						bullet->FireBullet();
						objects.push_back(bullet);
					}
				}
				if(state == GAMEOVER)
				{
					player->SetLives(3);
					player->Init(playerImage);
					ChangeState(state, PLAY);
				}
				break;				
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			}
		}
		//==============================================
		//GAME UPDATE
		//==============================================
		else if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			render = true;

			//UPDATE FPS===========
			frames++;
			if(al_current_time() - gameTime >= 1)
			{
				gameTime = al_current_time();
				gameFPS = frames;
				frames = 0;
			}
			//=====================
			if(state == MENU)
			{

			}
			
			if(state == PLAY)
			{
				if(rand() % 100 == 0)
				{
					Enemy *enemy = new Enemy();
					enemy->Init(ENEMY_TYPE_ZOMBIE, (rand() * 1.0 / RAND_MAX * WIDTH), (rand() * 1.0 / RAND_MAX * HEIGHT));
					enemy->StartEnemy();
					enemies.push_back(enemy);
				}
				else if(rand() % 1500 == 0)
				{
					Enemy *enemy = new Enemy();
					enemy->Init(ENEMY_TYPE_BOSS, (rand() * 1.0 / RAND_MAX * WIDTH), (rand() * 1.0 / RAND_MAX * HEIGHT));
					enemy->StartEnemy();
					enemies.push_back(enemy);
				}
				else if(rand() % 2000 == 0)
				{
					Weapon *weapon = new Weapon();
					weapon->Init(WEAPON_TYPE_ASSLT, (rand() * 1.0 / RAND_MAX * WIDTH), (rand() * 1.0 / RAND_MAX * HEIGHT));
					objects.push_back(weapon);
				}
				else if(rand() % 3000 == 0)
				{
					Power *power = new Power();
					power->Init(TIME, (rand() * 1.0 / RAND_MAX * WIDTH), (rand() * 1.0 / RAND_MAX * HEIGHT));
					objects.push_back(power);
				}
				
				if(keys[UP])
				{
					player->MoveUp();			
					player->SetDirection(NORTH);
				}
				else if(keys[DOWN])
				{
					player->MoveDown();
					player->SetDirection(SOUTH);
				}
				if(keys[LEFT])
				{
					player->MoveLeft();
					player->SetDirection(WEST);
				}
				else if(keys[RIGHT])								
				{	
					player->MoveRight();
					player->SetDirection(EAST);
				}
				if(keys[SPACE])
				{
					switch(player->GetWeapon())
					{
					case DEFAULT:
						if(player->IncrementBulletCount() >= player->GetBulletDelay())
						{
							player->SetBulletCount(0);
							Bullet *bullet = new Bullet(BULLET_TYPE_DEF, player->GetX(), player->GetY(), player->GetDirection());
							bullet->Init();
							bullet->FireBullet();
							objects.push_back(bullet);
						}				
						break;	
					case ASSAULT:						
						if(player->IncrementBulletCount() >= player->GetBulletDelay() && player->GetAmmo() > 0)
						{
							player->DecrementAmmo();
							player->SetBulletCount(0);
							Bullet *bullet = new Bullet(BULLET_TYPE_ASSLT, player->GetX(), player->GetY(), player->GetDirection());
							bullet->Init();
							bullet->FireBullet();
							objects.push_back(bullet);
						}						
						break;
					}
					if(player->GetAmmo() <= 0 && player->GetWeapon() != DEFAULT)
						player->SetWeapon(DEFAULT);
					
				}

			// ************************
			// OBJECTS AND LISTS UPDATE
			//************************	

				for(iter = objects.begin(); iter != objects.end(); iter++)
				{
					(*iter)->Update();
				}

				for(enemyIter = enemies.begin(); enemyIter != enemies.end(); enemyIter++)
				{
					if((*enemyIter)->GetAggroZone() >= CheckDistance(player->GetX(), player->GetY(), (*enemyIter)->GetX(), (*enemyIter)->GetY()))
						(*enemyIter)->SetState(CHASE);
					else (*enemyIter)->SetState(IDLE);
				
					(*enemyIter)->Update(AngleToTarget((*enemyIter)->GetX(), (*enemyIter)->GetY(), player->GetX(), player->GetY())); // Update
				} 
				if(player->GetPowerUp() == TIME)
					{
						player->SetPowerUp(-1);
						ChangeState(state, WARP);
					}
			} 

			if(state == WARP)
			{
				if(keys[UP])
				{
					player->MoveUp();			
					player->SetDirection(NORTH);
				}
				else if(keys[DOWN])
				{
					player->MoveDown();
					player->SetDirection(SOUTH);
				}
				if(keys[LEFT])
				{
					player->MoveLeft();
					player->SetDirection(WEST);
				}
				else if(keys[RIGHT])								
				{	
					player->MoveRight();
					player->SetDirection(EAST);
				}
				if(keys[SPACE])
				{
					switch(player->GetWeapon())
					{
					case DEFAULT:
						{
							/*Bullet *bullet = new Bullet(BULLET_TYPE_DEF, player->GetX(), player->GetY(), player->GetDirection());
							bullet->Init();
							bullet->FireBullet();
							objects.push_back(bullet);*/
						}
						break;
					case ASSAULT:
						{
							/*Bullet *bullet = new Bullet(BULLET_TYPE_ASSLT, player->GetX(), player->GetY(), player->GetDirection());
							bullet->Init();
							bullet->FireBullet();
							objects.push_back(bullet);*/
						}
						break;						
					}
				}
				player->Update();
				if(player->IncrementWarpCount() >= player->GetWarpDelay())
				{
					player->SetWarpCount(0);
					ChangeState(state, PLAY);
				}
			}	

			if(state == GAMEOVER)
			{
				for(iter = objects.begin(); iter != objects.end(); ++iter)
				{
					if( (*iter)->GetID() != PLAYER)
						(*iter)->SetAlive(false); 
				}
				for(enemyIter = enemies.begin(); enemyIter != enemies.end(); ++enemyIter)
				{
					(*enemyIter)->SetAlive(false);
				}

			}		

			// COLLISSION DETECTIONS
			for(iter = objects.begin(); iter != objects.end(); ++iter)
			{
					if( ! (*iter)->Collidable() ) continue;
					if( (*iter)->GetID() == BULLET || (*iter)->GetID() == PLAYER)
					{
						for(enemyIter = enemies.begin(); enemyIter != enemies.end(); enemyIter++)
						{
							if( (*iter)->CheckCollisions( (*enemyIter)))
							{
								(*iter)->Collided( (*enemyIter) );
								(*enemyIter)->Collided( (*iter) );
							}

						}
					}

					for(iter2 = iter; iter2 != objects.end(); ++iter2)
					{
						if( !(*iter2)->Collidable() ) continue;
						if( (*iter)->GetID() == (*iter2)->GetID()) continue;

						if( (*iter)->CheckCollisions( (*iter2)))
						{
							(*iter)->Collided( (*iter2) );
							(*iter2)->Collided( (*iter) );
						}
					}

			}

			//CULL THE DEAD
			for(iter = objects.begin(); iter != objects.end();)
			{
				if(! (*iter)->GetAlive())
				{
					delete (*iter);
					iter = objects.erase(iter);
				}
				else
					iter++;
			}

			for(enemyIter = enemies.begin(); enemyIter != enemies.end();)
			{
				if(! (*enemyIter)->GetAlive())
				{
					delete (*enemyIter);
					enemyIter = enemies.erase(enemyIter);
				}
				else
					enemyIter++;
			}

		}
		if(player->GetHealth() <= 0)
		{
			player->LoseLife();
			player->Init(playerImage);
			if(player->GetLives() <= 0)
				ChangeState(state, GAMEOVER);
		}
		//==============================================
		//RENDER
		//==============================================
		if(render && al_is_event_queue_empty(event_queue))
		{
			render = false;
		//	al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 5, 0, "FPS: %i", gameFPS);	//display FPS on screen gameFPS			

			//BEGIN PROJECT RENDER================

			if(state == MENU)
			{
				al_draw_bitmap(menuScreen, 0, 0, 0);
			}

			if(state == PLAY)
			{
				al_draw_bitmap(bgImage, 0, 0, 0);
				al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 5, 0, "Health: %f", player->GetHealth());
				al_draw_textf(font18, al_map_rgb(255, 0, 255), WIDTH / 2, 5, 0, "Lives: %i", player->GetLives());

				if(player->GetWeapon() != DEFAULT)
					al_draw_textf(font18, al_map_rgb(255, 0, 255), WIDTH  - 100, 5, 0, "Ammo: %i", player->GetAmmo());
				else al_draw_textf(font18, al_map_rgb(255, 0, 255), WIDTH  - 100, 5, 0, "Ammo: INF");
			
				for(iter = objects.begin(); iter != objects.end(); iter++)
					(*iter)->Render();

				for(enemyIter = enemies.begin(); enemyIter != enemies.end(); enemyIter++)
					(*enemyIter)->Render();
			}

			if(state == WARP)
			{
				al_draw_bitmap(bgImage, 0, 0, 0);
				al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 5, 0, "Health: %f", player->GetHealth());
				al_draw_textf(font18, al_map_rgb(255, 0, 255), WIDTH / 2, 5, 0, "Lives: %i", player->GetLives());
				al_draw_textf(font18, al_map_rgb(255, 0, 255), WIDTH  - 100, 5, 0, "Ammo: %i", player->GetAmmo());
				//al_draw_textf(font18, al_map_rgb(255, 0, 255), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, "TIME WARP: EVERYTHING IS FROZEN.");
			
				for(iter = objects.begin(); iter != objects.end(); iter++)
					(*iter)->Render();

				for(enemyIter = enemies.begin(); enemyIter != enemies.end(); enemyIter++)
					(*enemyIter)->Render();

			}

			if(state == GAMEOVER)
			{
				al_draw_bitmap(gameOverScreen, 0, 0, 0);
			}			

			//FLIP BUFFERS========================
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}

	//==============================================
	//DESTROY PROJECT OBJECTS
	//==============================================

	//SHELL OBJECTS=================================
	for(iter = objects.begin(); iter != objects.end(); )
	{
		//(*iter)->Destroy();
		delete (*iter);
		iter = objects.erase(iter);
	}
	for(enemyIter = enemies.begin(); enemyIter != enemies.end(); )
	{
		delete(*enemyIter);
		enemyIter = enemies.erase(enemyIter);
	}
	//delete player;
	//delete enemy;
	al_destroy_bitmap(playerImage);
	al_destroy_bitmap(bgImage);
	al_destroy_bitmap(menuScreen);
	al_destroy_bitmap(gameOverScreen);
	al_destroy_font(font18);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);

	return 0;
}
float CheckDistance(float x1, float y1, float x2, float y2)
{
	return sqrt(pow((float)x1 - x2, 2) + pow((float)y1 - y2, 2));
}

float AngleToTarget(float x1, float y1, float x2, float y2)
{
	float deltaX = (x2 - x1);
	float deltaY = (y2 - y1);
	return atan2(deltaY, deltaX);
}

void ChangeState(int &state, int newState)
{
	/*if(state == MENU)
	{

	}
	
	if(state == PLAY)
	{

	}

	if (state == WARP)
	{

	}

	if(state == GAMEOVER)
	{

	}*/

	state = newState;

	/*if(state == MENU)
	{

	}
	
	if(state == PLAY)
	{

	}

	if (state == WARP)
	{

	}

	if(state == GAMEOVER)
	{

	}*/

}