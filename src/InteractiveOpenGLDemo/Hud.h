#pragma once
#include "includes.h"
class Hud
{
protected:
	int PositionX = 0;
	int PositionY = 0;
	float Row = 0;
	float Column = 0;
	int sizeX = 0;
	int sizeY = 0;
	float MaxRow = 1;
	float MaxColumn = 1;
	static GLuint shader;
	GLuint UVbuffer;
	GLuint VertexBuffer;
	unsigned int sizeOfBuffer = 0;
	GLuint texture = 0;
	GLuint textureID;
	GLuint half_height_ID;
	GLuint half_width_ID;
	int ClassID = 0;
	bool visible = true;
public:
	static void setShader(std::string VectorPath, std::string FargmentPath);
	int width, height;
	virtual void setPosition(int x, int y,int sizex, int sizey);
	virtual void setRowAColumn(float r, float c, float maxR, float maxC);
	virtual void init(std::string path);
	virtual void buffer();
	virtual void draw();
	Hud(std::string path);
	Hud();
	virtual~Hud();
};

