#pragma once
#include "BaseObject.h"

class Player: public BaseObject
{
private:
	int lives;
	float health;
	int ammo;
	float armor;
	int powerUp;
	int bulletCount;
	int bulletDelay;
	int warpCount;
	int warpDelay;
	int direction;
	int weapon;
public:
	Player();
	void Init(ALLEGRO_BITMAP *image);

	int GetLives() {return Player::lives;}
	void SetLives(int lives) {Player::lives = lives;}
	void LoseLife();

	int GetAmmo() {return Player::ammo;}
	int DecrementAmmo() {return Player::ammo--;}
	void SetAmmo(int ammo) {Player::ammo = ammo;}

	int GetPowerUp() {return Player::powerUp;}
	void SetPowerUp(int powerUp) {Player::powerUp = powerUp;}

	int GetBulletCount() {return Player::bulletCount;}
	int IncrementBulletCount() {return Player::bulletCount++;}
	void SetBulletCount(int bulletCount) {Player::bulletCount = bulletCount;}

	int GetBulletDelay() {return Player::bulletDelay;}
	void SetBulletDelay(int bulletDelay) {Player::bulletDelay = bulletDelay;}

	int GetWarpCount() {return Player::warpCount;}
	int IncrementWarpCount() {return Player::warpCount++;}
	void SetWarpCount(int warpCount) {Player::warpCount = warpCount;}

	int GetWarpDelay() {return Player::warpDelay;}
	void SetWarpDelay(int warpDelay) {Player::warpDelay = warpDelay;}

	int GetDirection() {return Player::direction;}
	void SetDirection(int direction) {Player::direction = direction;}

	int GetWeapon() {return Player::weapon;}
	void SetWeapon(int weapon) {Player::weapon = weapon;}

	void MoveRight();
	void MoveLeft();
	void MoveDown();
	void MoveUp();

	void Update();
	void Render();

	bool CheckCollisions(BaseObject *target);
	void Collided(BaseObject *target);

	float GetHealth() {return health;}
	void SetHealth(float health) {Player::health = health;}

};