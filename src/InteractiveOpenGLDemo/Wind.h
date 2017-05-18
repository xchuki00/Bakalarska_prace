#pragma once
#include "includes.h"
#include "PerlinNoise.h"
class Wind
{
	glm::vec3 dir;
	float strength;
	PerlinNoise * noise;

public:
	GLuint ShadowShader;
	GLuint shadowBuffer = 0;
	GLuint shadowTexture;
	glm::vec3 getDir();
	void setDirection(glm::vec3 dir, float str);
	void init(glm::vec3 dir,float str);
	void drawWindMap();
	glm::vec3 getLocalWind(glm::vec3 pos);
	Wind();
	virtual~Wind();
};

