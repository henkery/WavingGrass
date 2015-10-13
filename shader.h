#ifndef SHADER_H
#define SHADER_H

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

static char *
shaderLoadSource(const char *filePath);

static GLuint
shaderCompileFromFile(GLenum type, const char *filePath);

void
shaderAttachFromFile(GLuint program, GLenum type, const char *filePath);

#endif