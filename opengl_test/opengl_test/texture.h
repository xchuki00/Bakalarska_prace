#pragma once
#include "includes.h"

GLuint loadTexture2d(const char * path,int *height, int *width);
GLuint loadTextureCube(const char * path, GLenum side,GLuint *texture);