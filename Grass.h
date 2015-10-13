#ifndef PORTALTURRET_H
#define PORTALTURRET_H

#include "GameObject.h"



class Grass : public GameObject
{
public:
	Grass(float fpXCoordinate, float fpYCoordinate, float fpZCoordinate);
	void Draw();
	GLint grassShaderID = 0;
	float warp = 0;
private:


};

#endif
