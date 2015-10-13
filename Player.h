#ifndef PORTALGUN_H
#define PORTALGUN_H

#include "GameObject.h"

class Player : public GameObject
{
public:
	Player(float fpXCoordinate, float fpYCoordinate, float fpZCoordinate);
	void Draw();

};

#endif