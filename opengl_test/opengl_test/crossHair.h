#pragma once
#include "includes.h"
class crossHair
{
	GLuint shader;
	GLuint UVbuffer;
	GLuint VertexBuffer;
	GLuint texture=0;
	GLuint uniformID;

	int width, height;
public:
	void init(std::string path);
	void buffer();
	void draw();
	crossHair(std::string path);
	crossHair();
	virtual ~crossHair();
};

