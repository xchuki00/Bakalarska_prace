#pragma once
#include "includes.h"
class shadowmap
{
	GLuint framebuffer;
	GLuint depthTexture;
	glm::mat4 MVP;
	GLuint shader;
	GLuint MVPID;
public:
	int init();
	int draw();
	shadowmap();
	~shadowmap();
};

