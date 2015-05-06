#include "Globals.h"

float CheckDistance(int x1, int y1, int x2, int y2)
{
	return sqrt(pow((float)x1 - x2, 2) + pow((float)y1 - y2, 2));
}

float AngleToTarget(int x1, int y1, int x2, int y2)
{
	float deltaX = (x2 - x1);
	float deltaY = (y2 - y1);
	return atan2(deltaY, deltaX);
}