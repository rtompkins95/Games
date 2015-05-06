#include "Enemy.h"

Enemy::Enemy()
{
	state = -1;
	type = -1;
	aggroZone = 0;
}

void Enemy::Init(int type, float x, float y)
{
	Enemy::type = type;
	health = 100;
	state = -1;
	aggroZone = 500;

	if(type == ENEMY_TYPE_ZOMBIE)
	{
		health = 100;
		BaseObject::InitObject(ENEMY, true, true, x, 3, 1, y, 3, 1, 10, 10, 0, 0, 0, 0, 0, 0, 0, 0, NULL); 
	}
	if(type == ENEMY_TYPE_SUB)
	{
		health = 150;
		BaseObject::InitObject(ENEMY, true, true, x, 3, 1, y, 3, 1, 15, 15, 0, 0, 0, 0, 0, 0, 0, 0, NULL);
	}
	if(type == ENEMY_TYPE_BOSS)
	{
		health = 500;
		BaseObject::InitObject(ENEMY, true, true, x, 3, 1, y, 3, 1, 20, 20, 0, 0, 0, 0, 0, 0, 0, 0, NULL);
	}

}

void Enemy::StartEnemy()
{
	alive = true;
}

void Enemy::Update(float angle)
{
	if(state == IDLE)
	{

	}

	if(state == CHASE)
	{
		if(alive)
		{
			x += (speedX * cos(angle)) / 2;
			y += (speedY * sin(angle)) / 2;
		}
	}
	if(health <= 0)
		alive = false;
}

void Enemy::Render()
{
	switch(type)
	{
	case ENEMY_TYPE_ZOMBIE:
		al_draw_filled_rectangle(x - boundX, y - boundY, x + boundX, y + boundY, al_map_rgb(health + 155, 0, 0));
		break;
	case ENEMY_TYPE_SUB:
		al_draw_filled_rectangle(x - boundX, y - boundY, x + boundX, y + boundY, al_map_rgb(health + 155, 0, 0));
		break;
	case ENEMY_TYPE_BOSS:
		al_draw_filled_rectangle(x - boundX, y - boundY, x + boundX, y + boundY, al_map_rgb(255 - health / 2, 0, 0));
		break;
	}
}

void Enemy::RenderAggro()
{
	if(alive)
	al_draw_circle(x, y, aggroZone, al_map_rgb(255, 0, 255), 5);
}

bool Enemy::CheckCollisions(BaseObject *target)
{
	return BaseObject::CheckCollisions(target);
}

void Enemy::Collided(BaseObject *target)
{
	if(target->GetID() == BULLET)
	{
		switch(target->GetType())
		{
		case BULLET_TYPE_DEF:
			health -= 20;
			break;
		case BULLET_TYPE_ASSLT:
			health -= 40;
			break;
		case BULLET_TYPE_RCKT:
			health -= 100;
			break;
		case BULLET_TYPE_FLME:
			health -= 50;
			break;
		}

	}
}

