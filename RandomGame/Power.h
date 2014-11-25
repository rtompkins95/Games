#include "Globals.h"
#include "BaseObject.h"

class Power: public BaseObject
{
public:
	Power();
	void Init(int type, float x, float y);

	void Update();
	void Render();
	bool CheckCollisions(BaseObject *target);
	void Collided(BaseObject *target);

};