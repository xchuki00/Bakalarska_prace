#pragma once
#include "model.h"

class skybox: public model
{
private:

public:
	GLuint shader;
	GLuint textureID;
	GLuint MVID;
	int init();
	int load_texture(
		const char* left, 
		const char* front,
		const char* right,
		const char* back,
		const char* top, 
		const char* bottom
	);
	int buffer();
	int addShader(std::string vertexShader, std::string fragmentShader);
	skybox();
	~skybox();
};

