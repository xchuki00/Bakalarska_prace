#pragma once
#include "includes.h"
class crossHair
{
	GLuint shader;
	GLuint UVbuffer;
	GLuint VertexBuffer;
	GLuint texture=0;
	GLuint textureID;
	GLuint half_height_ID;
	GLuint half_width_ID;

	int width, height;
public:
	void init(std::string path);
	void buffer();
	void draw();
	crossHair(std::string path);
	crossHair();
	virtual ~crossHair();
};

