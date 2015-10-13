#include "Tile.h"

#define tilesize 1

Tile::Tile(float fpXCoordinate, float fpYCoordinate, float fpZCoordinate, Direction direction) : GameObject(fpXCoordinate,fpYCoordinate,fpZCoordinate, "")
{
	this->m_Direction = direction;
}

Tile::Tile(float fpXCoordinate, float fpYCoordinate, float fpZCoordinate, Direction direction, double size) : GameObject(fpXCoordinate,fpYCoordinate,fpZCoordinate, "")
{
	this->m_Direction = direction;
	this->size = size;
}

Tile::Tile(float fpXCoordinate, float fpYCoordinate, float fpZCoordinate, Direction direction, double size, float r, float g, float b) : GameObject(fpXCoordinate,fpYCoordinate,fpZCoordinate, "")
{
	this->m_Direction = direction;
	this->size = size;
	this->r = r;
	this->g = g;
	this->b = b;
	this->coldef = true;
}

void Tile::Draw()
{
	glPushMatrix();

	glTranslatef(m_fpXCoordinate, m_fpYCoordinate, m_fpZCoordinate);

	switch (m_Direction)
	{
	case FRONT:
		glNormal3f(0.0, 1.0, 0.0);
		break;
	case BACK:
		glNormal3f(0.0, 1.0, 0.0);
		break;
	case RIGHT:
		glNormal3f(0.0, 1.0, 0.0);
		glRotatef(-90.0, 0.0, 1.0, 0.0);
		break;
	case LEFT:
		glNormal3f(0.0, 1.0, 0.0);
		glRotatef(-90.0, 0.0, 1.0, 0.0);
		break;
	case UPPER:
		glNormal3f(0, 0, -1);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		break;
	case LOWER:
		glNormal3f(0, 0, -1);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		break;
	}

	drawQuad();

	glPopMatrix();
}

/*
* 	Function:  drawQuad
* 	--------------------
* 	Uses glBegin(GL_QUADS), draws a quad and ends with a glEnd()
*
*  returns: void
*/
void Tile::drawQuad()
{
	glBegin(GL_QUADS);
	if (coldef) {
		glColor4f(r, g, b, 1.0);
		//printf("colors are: %f, %f, %f", r, g, b);
	}
	for (int i =0; i<(int)size; i+=tilesize)
	{
		for (int j=0;j<size;j+=tilesize)
		{
			glVertex3f(i, tilesize+j, 0.0);
			glVertex3f(i, j, 0.0);
			glVertex3f(tilesize+i, j, 0.0);
			glVertex3f(tilesize+i, tilesize+j, 0.0);
		}
	}
	glEnd();
}

Direction Tile::DoesCollide(float fpXCoordinate, float fpYCoordinate, float fpZCoordinate, float fpMargin)
{
	switch (m_Direction)
	{
	case FRONT:
	case BACK:
		if (fpZCoordinate >= m_fpZCoordinate - fpMargin && fpZCoordinate <= m_fpZCoordinate + fpMargin &&
			fpXCoordinate >= m_fpXCoordinate && fpXCoordinate <= m_fpXCoordinate + 1 &&
			fpYCoordinate >= m_fpYCoordinate && fpYCoordinate <= m_fpYCoordinate + 1)
			return m_Direction;
		break;
	case RIGHT:
	case LEFT:
		if (fpXCoordinate > m_fpXCoordinate - fpMargin && fpXCoordinate < m_fpXCoordinate + fpMargin &&
			fpZCoordinate >= m_fpZCoordinate && fpZCoordinate <= m_fpZCoordinate + 1 &&
			fpYCoordinate >= m_fpYCoordinate && fpYCoordinate <= m_fpYCoordinate + 1)
			return m_Direction;
		break;
	case UPPER:
	case LOWER:
		if (fpYCoordinate > m_fpYCoordinate - fpMargin && fpYCoordinate < m_fpYCoordinate + fpMargin &&
			fpXCoordinate >= m_fpXCoordinate && fpXCoordinate <= m_fpXCoordinate + 1 &&
			fpZCoordinate >= m_fpZCoordinate && fpZCoordinate <= m_fpZCoordinate + 1)
			return m_Direction;
		break;
	}
	return NOTHING;
}

std::vector<Tile> scene;
