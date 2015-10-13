#ifndef MESH_H
#define MESH_H

#include "vector"
#include "Vector3F.h"

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

class Mesh
{
public:
	Mesh();
	GLuint m_textureID = 0;

	Mesh(Vector3F *pVertices, Vector3F *pNormals, Vector3F *pTextures, Vector3F *pFaces, int iVerticeSize, int iNormalSize, int iTextureSize, int iFaceSize, int iMaxAmountOfVerticesPerFace);
	//~Mesh();
	Vector3F *m_pVertices;
	Vector3F *m_pNormals;
	Vector3F *m_pTextures;
	Vector3F *m_pFaces;
	int m_iVerticeSize;
	int m_iNormalSize;
	int m_iTextureSize;
	int m_iFaceSize;
	int m_iMaxAmountOfVerticesPerFace;

	void Draw();
	void InitTexturing(char *texturePath);
};

#endif