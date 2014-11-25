#include "Player.h"

Player::Player()
{
	lives = 3;
}

void Player::Init(ALLEGRO_BITMAP *image)
{
	health = 100;
	ammo = 100;
	armor = 1.1;
	powerUp = -1;
	bulletDelay = 10;
	bulletCount = 0;
	warpDelay = 300;
	warpCount = 0;
	direction = EAST;
	weapon = DEFAULT;
	BaseObject::InitObject(PLAYER, true, true, WIDTH / 2, 5, 1, HEIGHT / 2, 7, 1, 7, 7, 0, 0, 5, al_get_bitmap_width(image) / 4, 
		al_get_bitmap_height(image), 12, 12, 0, image);
}

void Player::LoseLife()
{
	lives--;
}

void Player::MoveLeft()
{
	x -= speedX * dirX;
}

void Player::MoveRight()
{
	x += speedX * dirX;
}

void Player::MoveUp()
{
	y -= speedY * dirY;
}

void Player::MoveDown()
{
	y += speedY * dirY;
}

void Player::Update()
{
	/*if(++frameCount >= frameDelay)
	{
		if(++curFrame >= maxFrame)
			curFrame = 0;
		frameCount = 0;
	}*/
	if(x + boundX > WIDTH)
		x = WIDTH - boundX;
	else if(x - boundX < 0)
		x = boundX;
	if(y + boundY > HEIGHT)
		y = HEIGHT - boundY;
	else if(y - boundY < 0)
		y = boundY;
}

void Player::Render()
{
	int fx = curFrame * frameWidth;
	int fy = 0;

	al_draw_bitmap_region(image, 0, 0, frameWidth, frameHeight, x - boundX / 2, y - boundY / 2, 0);

	//al_draw_filled_rectangle(x - boundX, y - boundY, x + boundX, y + boundY, al_map_rgb(255, 0, 255));
	/*switch(direction)
	{
	case NORTH:
		al_draw_rotated_bitmap_region(image, 0, 0, x - boundX / 2, y - boundY / 2, 3.1415, 0);
		break;
	case SOUTH:
		al_draw_rotated_bitmap(image, x, y, x - boundX / 2, y - boundY / 2, 3.14159, 0);
		break;
	case EAST:
		al_draw_rotated_bitmap(image, x, y, x - boundX / 2, y - boundY / 2, 3.14159 / 2, 0);
		break;
	case WEST:
		al_draw_rotated_bitmap(image, x, y, x - boundX / 2, y - boundY / 2, 3.14159 * 1.5, 0);
		break; 
	}*/
}

bool Player::CheckCollisions(BaseObject *target)
{
	return BaseObject::CheckCollisions(target);
}

void Player::Collided(BaseObject *target)
{
	if(target->GetID() == WEAPON)
	{
		switch(target->GetType())
		{
		case WEAPON_TYPE_ASSLT:
			weapon = ASSAULT;
			ammo = 100;
			break;
		case WEAPON_TYPE_RCKT:
			weapon = ROCKET;
			ammo = 100;
			break;
		case WEAPON_TYPE_FLME:
			weapon = FLAME;
			ammo = 100;
			break;
		}
	}

	if(target->GetID() == ENEMY)
	{
		health -= 1 / armor;
	}

	if(target->GetID() == MISC)
		powerUp = TIME;
}