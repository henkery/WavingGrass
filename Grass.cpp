#include "Grass.h"

#define amount 250
#define spacing 30


Grass::Grass(float fpXCoordinate, float fpYCoordinate, float fpZCoordinate)
: GameObject(fpXCoordinate, fpYCoordinate, fpZCoordinate, "../Models/grass.obj"){}

void Grass::Draw()
{
	glPushMatrix();

	glScalef(0.1, 0.1, 0.1);
	GLfloat time;

	if (grassShaderID != 0) {
		glUseProgram(grassShaderID);
		GLfloat time = glGetUniformLocation(grassShaderID, "time");

	}
	warp++;
	for (int i=0; i< amount; i+=spacing) {

		for (int j=0; j<amount; j+= spacing) {
			glPushMatrix();
			glTranslatef(m_fpXCoordinate + i, m_fpYCoordinate, m_fpZCoordinate+j);
		//	glRotatef(90, 0.0, 0.0, 1.0);
			if (grassShaderID != 0) {
				glColor4f( 0.46, 0.97, 0.0, 1);
				glUniform1f(time, warp);
			}
			GameObject::Draw();
			glPopMatrix();

		}
	}
	glUseProgram(0);

	glPopMatrix();
}
