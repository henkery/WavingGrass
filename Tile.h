#ifndef TILE_H
#define TILE_H

#include "GameObject.h"

typedef enum Direction
{
	FRONT,
	BACK,
	RIGHT,
	LEFT,
	UPPER,
	LOWER,
	NOTHING
} Direction;

class Tile : public GameObject
{
public:
	Tile(float fpXCoordinate, float fpYCoordinate, float fpZCoordinate, Direction direction);
	Tile(float fpXCoordinate, float fpYCoordinate, float fpZCoordinate, Direction direction, double size);
	Tile(float fpXCoordinate, float fpYCoordinate, float fpZCoordinate, Direction direction, double size, float r, float g, float b);
	void Draw();
	Direction DoesCollide(float xCoordinate, float yCoordinte, float zCoordinate, float margin);

private:
	double size;
	Direction m_Direction;
	void drawQuad();
	float r;
	float g;
	float b;
	bool coldef = false;
};

extern std::vector<Tile> scene;

#endif
