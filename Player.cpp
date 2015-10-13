#include "Player.h"

Player::Player(float fpXCoordinate, float fpYCoordinate, float fpZCoordinate)
: GameObject(fpXCoordinate, fpYCoordinate, fpZCoordinate, "../Models/cube.obj"){}

void Player::Draw()
{
	glPushMatrix();
	glTranslatef(m_fpXCoordinate, m_fpYCoordinate, m_fpZCoordinate);
	//glRotatef(-40, 0, 1, 0);
	glColor4f(1, 1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	m_mesh.InitTexturing("../Texture/paper.jpeg");
	GameObject::Draw();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
