#include "Main.h"

#include <stdlib.h>
#include <iostream>
#include <string.h>

#ifdef _WIN32
#include <glew.h>
#include <glut.h>
#include <Windows.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#include <sys/time.h>
#include <unistd.h>
#include <math.h>
#endif

#include "Camera.h"
#include "ObjectLoader.h"
#include "NormalCalculators.h"
#include "shader.h"

#include "Player.h"
#include "Grass.h"
#include "Tile.h"

#include "stb_image.h"

#define GLEW_STATIC

using namespace std;

bool *keyStates = new bool[KEYSTATE_SIZE];
bool *specialKeyStates = new bool[KEYSTATE_SIZE];

float fpWidth = SCREEN_WIDTH;
float fpHeight = SCREEN_HEIGHT;
float fpTime = 0.0;
long lLastDraw = 0;

Grass grass(-20, -45, 0);
Player player(-0, -1.3, -4);

GLuint uirgFrameBufferObjectID[2];
GLuint uirgFrameBufferObjectTextureID[2];

unsigned int uiShaderID;

void initShader(char *fileName)
{
	fprintf(stderr, "loading %s shaders", fileName);
	GLint result;

	uiShaderID = glCreateProgram();

	char filePath[50];
	sprintf(filePath, "%s%s%s", "../Data/", fileName, ".vp");
	shaderAttachFromFile(uiShaderID, GL_VERTEX_SHADER, filePath);

	sprintf(filePath, "%s%s%s", "../Data/", fileName, ".fp");
	shaderAttachFromFile(uiShaderID, GL_FRAGMENT_SHADER, filePath);

	glLinkProgram(uiShaderID);
	glGetProgramiv(uiShaderID, GL_LINK_STATUS, &result);
	if (result == GL_FALSE) {
		GLint length;
		char *log;

		/* get the program info log */
		glGetProgramiv(uiShaderID, GL_INFO_LOG_LENGTH, &length);
		log = (char *)malloc(length);
		glGetProgramInfoLog(uiShaderID, length, &result, log);

		/* print an error message and the info log */
		fprintf(stderr, "aInit(): Program linking failed: %s\n", log);
		free(log);

		/* delete the program */
		glDeleteProgram(uiShaderID);
		uiShaderID = 0;
	}
	if (uiShaderID != 0)
		grass.grassShaderID = uiShaderID;
}
void initRendering() {
	glClearColor(0, 0, 0, 0);
}

void initScene()
{
	scene.push_back(Tile(-50, 20, -50, UPPER, 100));
	scene.push_back(Tile(-50, -5, -50, LOWER, 100, 0.54, 0.6, 0.35));
	scene.push_back(Tile(-50, -5, -50, BACK, 100));
	scene.push_back(Tile(-50, -5, 50, BACK, 100));
	scene.push_back(Tile(50, -5, -50, RIGHT, 100));
	scene.push_back(Tile(-50, -5, -50, LEFT, 100));
}

void drawScene()
{

	for (std::vector<Tile>::iterator pSceneIt = scene.begin(); pSceneIt != scene.end(); pSceneIt++)
	{
		glColor4f(0, 0.5, 1.0, 1.0);
		pSceneIt->Draw();
	}
	glPopMatrix();
}

void render(int perspective)
{

	const float LightPosition[4] = { 0.0f, 20.0f, 0.0f, 1.0f };

	glEnable(GL_DEPTH_TEST);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLdouble)fpWidth / (GLdouble)fpHeight, 1.0, 200);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (perspective == 2)
		player.Draw();
	InitCamera();


	//Position light
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

	//Draw PortalItems
	grass.Draw();

	//Draw Room
	drawScene();

	//Draw particles
	//DrawParticleEmitters();

	glFlush();
}

/*
* 	Function:  Display
* 	--------------------
* 	Draws the content of this function to the screen every frame
*
*  returns: void
*/
void Display() {

	for (int i = 0; i < 2; i++)
	{

		// bind a framebuffer object
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, uirgFrameBufferObjectID[i]);

		// Set Drawing buffers
		GLuint attachments[1] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, attachments);

		render(i);
	}

	// get back to the default framebuffer
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	render(2);

	glutSwapBuffers();
}

/*void initFrameBufferObjectAndTexture(int w, int h) {
	for (int i = 0; i < 2; i++)
	{
		// Generate one frame buffer
		glGenFramebuffers(1, &uirgFrameBufferObjectID[i]);

		// bind it
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, uirgFrameBufferObjectID[i]);

		// attach texture for colors
		glGenTextures(1, &uirgFrameBufferObjectTextureID[i]);

		glBindTexture(GL_TEXTURE_2D, uirgFrameBufferObjectTextureID[i]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
			w,
			h,
			0, GL_RGBA, GL_UNSIGNED_BYTE,
			NULL);

		glBindTexture(GL_TEXTURE_2D, 0);

		glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, uirgFrameBufferObjectTextureID[i], 0);

		// attach renderbuffer for depth
		GLuint fb;
		glGenRenderbuffers(1, &fb);
		glBindRenderbuffer(GL_RENDERBUFFER, fb);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, w, h);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, fb);

		// unbind uiFrameBufferObjectID
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}
}*/

/*
* 	Function:  Reshape
* 	--------------------
* 	Called every time the screen has been resized.
*   Updates the width, height and buffer sizes of opengl
*
*	w: The width of the resized screen
*	h: The height of the resized screen
*
*  returns: void
*/
void Reshape(int w, int h) {
	fpWidth = w;
	fpHeight = h;
	glViewport(0, 0, w, h);

	glDeleteFramebuffersEXT(1, &uirgFrameBufferObjectID[0]);
	glDeleteFramebuffersEXT(1, &uirgFrameBufferObjectID[1]);
	glDeleteFramebuffersEXT(1, &uirgFrameBufferObjectTextureID[0]);
	glDeleteFramebuffersEXT(1, &uirgFrameBufferObjectTextureID[1]);
	//initFrameBufferObjectAndTexture(w, h);
}

/*
* 	Function:  KeyboardUp
* 	--------------------
* 	Sets false at the pressed key's index in the keyState buffer
*
*	key: The key being pushed
*	x: The x-coordinate of the mouse position at the time of key press
*	y: The y-coordinate of the mouse position at the time of key press
*
*  returns: void
*/
void KeyboardUp(unsigned char key, int x, int y)
{
	keyStates[key] = false;
}

/*
* 	Function:  KeyboardDown
* 	--------------------
* 	Sets true at the pressed key's index in the keyState buffer
*
*	key: The key being pushed
*	x: The x-coordinate of the mouse position at the time of key press
*	y: The y-coordinate of the mouse position at the time of key press
*
*  returns: void
*/
void KeyboardDown(unsigned char key, int x, int y)
{
	keyStates[key] = true;
}

/*
* 	Function:  KeyboardSpecialUp
* 	--------------------
* 	Sets false at the pressed key's index in the keyState buffer
*
*	key: The key being pushed
*	x: The x-coordinate of the mouse position at the time of key press
*	y: The y-coordinate of the mouse position at the time of key press
*
*  returns: void
*/
void KeyboardSpecialUp(int key, int x, int y)
{
	specialKeyStates[key] = false;
}

/*
* 	Function:  KeyboardSpecial
* 	--------------------
* 	Sets true at the pressed key's index in the specialKeyState buffer
*
*	key: The key being pushed
*	x: The x-coordinate of the mouse position at the time of key press
*	y: The y-coordinate of the mouse position at the time of key press
*
*  returns: void
*/
void KeyboardSpecial(int key, int x, int y)
{
	specialKeyStates[key] = true;
}

/*
* 	Function:  keyOperations
* 	--------------------
* 	Handles all pushed keys every update
*
*  returns: void
*/
void keyOperations()
{
	if (keyStates[27])
		exit(0);

	if (keyStates['1'])
	{
		keyStates['1'] = false;	//REPEAT_OFF
	}

	if (keyStates['2'])
	{
		keyStates['2'] = false;	//REPEAT_OFF
		//card.Enable();
	}

	if (keyStates['3'])
	{
		keyStates['3'] = false;	//REPEAT_OFF
		//card.Disable();
	}

	if (keyStates['4'])
	{
		keyStates['4'] = false;	//REPEAT_OFF
		initShader("grass");
	}

	if (keyStates['5'])
	{
		keyStates['5'] = false;	//REPEAT_OFF
		initShader("water");
	}

	if (keyStates['6'])
	{
		keyStates['6'] = false;	//REPEAT_OFF
		initShader("lava");
	}

	if (keyStates['d'])
		MoveRight();

	if (keyStates['a'])
		MoveLeft();

	if (keyStates['w'])
		MoveForward();


	if (keyStates['s'])
		MoveBackward();

	if (keyStates['e'])
		MoveUpward();

	if (keyStates['q'])
		MoveDownward();

	if (specialKeyStates[GLUT_KEY_RIGHT])
		RotateRight();

	if (specialKeyStates[GLUT_KEY_LEFT])
		RotateLeft();

	if (specialKeyStates[GLUT_KEY_UP])
		RotateUp();

	if (specialKeyStates[GLUT_KEY_DOWN])
		RotateDown();

	if (keyStates['z'])
	{
		//BluePortalBeam.Fire(fpCameraXCoordinate, fpCameraYCoordinate, fpCameraZCoordinate, fpXAngle, fpYAngle);
		keyStates['z'] = false;
	}

	if (keyStates['x'])
	{
		//OrangePortalBeam.Fire(fpCameraXCoordinate, fpCameraYCoordinate, fpCameraZCoordinate, fpXAngle, fpYAngle);
		keyStates['x'] = false;
	}

	if (keyStates['c'])
	{
		float fpXRotationInRadians = (fpXAngle / 180 * PI);
		float fpYRotationInRadians = (fpYAngle / 180 * PI);
		for (float i = 0; i < 100; ++i)
		{
			float fpCurrentTrackingX = float(-sin(fpXRotationInRadians)) / 10;
			float fpCurrentTrackingY = float(cos(fpYRotationInRadians) * sin(fpYRotationInRadians)) / 10;
			float fpCurrentTrackingZ = float(-cos(fpXRotationInRadians)) / 10;

			//for each (GameObject gObject in gameObjectList)
			//{
			//	if (gObject.isPortable && gObject.doesCollide())
			//	{
			//		//holdingobject = gObject;
			//	}
			//}
		}

		//fpCameraXCoordinate += float(-sin(fpXRotationInRadians)) * CAMERA_SPEED;
		//fpCameraYCoordinate += cos(fpYRotationInRadians) * sin(fpYRotationInRadians) * CAMERA_SPEED;
		//fpCameraZCoordinate += float(-cos(fpXRotationInRadians)) * CAMERA_SPEED;
		keyStates['c'] = false;
	}
	
}

/*
* 	Function:  Timer
* 	--------------------
* 	Updates all the content being drawn at 30 fps.
*
*  returns: void
*/
static void Timer(int value){

	long lStartTime;
#ifdef _WIN32
	lStartTime = timeGetTime();
#else
	struct timeval tp;
	gettimeofday(&tp, NULL);
	lStartTime =( tp.tv_sec * 100 + tp.tv_usec / 1000) /100000;
#endif

	keyOperations();
	fpTime += 0.05; 

	long lEndTime;
#ifdef _WIN32
	lEndTime = timeGetTime();
#else
	struct timeval tp1;
	gettimeofday(&tp1, NULL);
	lEndTime = (tp1.tv_sec * 100 + tp1.tv_usec / 1000) / 100000;
#endif

	glutTimerFunc((1000 / 30) - (lEndTime - lStartTime), Timer, 0);
}

/*
* 	Function:  Idle
* 	--------------------
* 	When opengl has time left, this will update the screen.
*
*  returns: void
*/
void Idle()
{
	long now;
#ifdef _WIN32
	now = timeGetTime();
#else
	struct timeval tp;
	gettimeofday(&tp, NULL);
	now = tp.tv_sec * 1000 + tp.tv_usec / 1000;
#endif

	if (now - lLastDraw < (1000 / 30))
		return;


	lLastDraw = now;
	glutPostRedisplay();
}

void sceneInit(void)
{
	GLint result;

	glDeleteProgram(uiShaderID);

	uiShaderID = glCreateProgram();

	glLinkProgram(uiShaderID);
	glGetProgramiv(uiShaderID, GL_LINK_STATUS, &result);

	if (result == GL_FALSE) 
	{
		glDeleteProgram(uiShaderID);
		uiShaderID = 0;
	}
}

void initLighting()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_NORMALIZE);
	const float amb = 0.2;
	const float LightAmbient[4] = { amb, amb, amb, 1.0f };
	const float LightDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const float whiteSpecularLight[] = { 1.0, 1.0, 1.0 };
	const GLfloat shiny = 60.0;
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteSpecularLight);
	glLightfv(GL_LIGHT0, GL_SHININESS, &shiny);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}

/*
* 	Function:  main
* 	--------------------
* 	The entry point of this application
*
*	argc: The amount of string pointed to by argv
*	argv: A pointer to the command line arguments given to this application
*
*  returns: void
*/
int main(int argc, char* argv[]) {
#ifndef _WIN32
	glutInit(&argc, argv);
#endif

	memset(keyStates, 0, KEYSTATE_SIZE);
	memset(specialKeyStates, 0, KEYSTATE_SIZE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	
	glutCreateWindow("Grass");
	glewInit();

	//glutFullScreen();

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);		
	
	//initFrameBufferObjectAndTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
	initLighting();
	initScene();
	initRendering();

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutIdleFunc(Idle);

	glutKeyboardFunc(KeyboardDown); 
	glutKeyboardUpFunc(KeyboardUp);
	glutSpecialFunc(KeyboardSpecial);
	glutSpecialUpFunc(KeyboardSpecialUp);

	Timer(0);

	glutMainLoop();
	return 0;
}
