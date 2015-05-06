#include "Globals.h"
#include "BaseObject.h"

class Weapon: public BaseObject
{
public:
	Weapon();
	void Init(int type, float x, float y);

	void Update();
	void Render();
	bool CheckCollisions(BaseObject *target);
	void Collided(BaseObject *target);
};