#include "Mesh.h"

#ifdef _WIN32
#include <glut.h>
#include <Windows.h>
#else
#include <GL/glut.h>
#include <sys/time.h>
#include <unistd.h>
#include <math.h>
#endif

#include "Vector3F.h"
#include "stb_image.h"
#include <iostream>

Mesh::Mesh() 
{
	this->m_pFaces = nullptr;
	this->m_pNormals = nullptr;
	this->m_pVertices = nullptr;
	this->m_pTextures = nullptr;
}

//Mesh::~Mesh() 
//{ 
//	if (m_pVertices != nullptr)
//		free(m_pVertices);
//
//	if (m_pNormals != nullptr)
//		free(m_pNormals);
//
//	if (m_pTextures != nullptr)
//		free(m_pTextures);
//
//	if (m_pFaces != nullptr)
//		free(m_pFaces);
//}

Mesh::Mesh(Vector3F *pVertices, Vector3F *pNormals, Vector3F *pTextures, Vector3F *pFaces, int iVerticeSize, int iNormalSize, int iTextureSize, int iFaceSize, int iMaxAmountOfVerticesPerFace)
{
	this->m_pVertices = pVertices;
	this->m_pNormals = pNormals;
	this->m_pTextures = pTextures;
	this->m_pFaces = pFaces;
	this->m_iVerticeSize = iVerticeSize;
	this->m_iNormalSize = iNormalSize;
	this->m_iTextureSize = iTextureSize;
	this->m_iFaceSize = iFaceSize;
	this->m_iMaxAmountOfVerticesPerFace = iMaxAmountOfVerticesPerFace;
}

void Mesh::Draw(){
	//glColor4f(1.0, 1.0, 1.0, 1.0);

	if (m_iMaxAmountOfVerticesPerFace == 3)
		glBegin(GL_TRIANGLES);
	else if (m_iMaxAmountOfVerticesPerFace == 4)
		glBegin(GL_QUADS);
	else
		glBegin(GL_POLYGON);

	for (int i = 0; i < m_iFaceSize; i++)
	{
		for (int j = 0; j < m_iMaxAmountOfVerticesPerFace; j++)
		{
			Vector3F face = m_pFaces[i * m_iMaxAmountOfVerticesPerFace + j];

			if (m_iNormalSize > 0)
			{
				Vector3F normal = m_pNormals[(int)(face.z) - 1];
				glNormal3f(normal.x, normal.y, normal.z);
			}
			else
				glNormal3f(0, 0, 0);

			if (m_iTextureSize > 0)
			{
				Vector3F texture = m_pTextures[(int)(face.y) - 1];
				glTexCoord2f(texture.x, texture.y);
			}

			Vector3F vertice = m_pVertices[(int)(face.x) - 1];
			glVertex3f(vertice.x, vertice.y, vertice.z);
		}
	}
	glEnd();
}

void Mesh::InitTexturing(char *texturePath)
{
	if (m_textureID == 0)
	{
		glGenTextures(1, &m_textureID);
		glBindTexture(GL_TEXTURE_2D, m_textureID);

		int width = 64, height = 64, bpp = 32;
		char finalTexturePath[50];
		sprintf(finalTexturePath, "../Texture/%s", texturePath);
		unsigned char* imgData = stbi_load(finalTexturePath, &width, &height, &bpp, 4);
		glTexImage2D(GL_TEXTURE_2D,
			0,					//level
			GL_RGBA,			//internal format
			width,				//width
			height,				//height
			0,					//border
			GL_RGBA,			//data format
			GL_UNSIGNED_BYTE,	//data type
			imgData);			//data

		stbi_image_free(imgData);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, m_textureID);
	}
}