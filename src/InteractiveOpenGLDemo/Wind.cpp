#include "Wind.h"
#include "Shader.h"
#include "controls.h"
#include "misc.h"
glm::vec3 Wind::getDir()
{
	return this->dir;
}

void Wind::setDirection(glm::vec3 dir, float str)
{
	this->dir = dir;
	this->strength = str;
}

void Wind::init(glm::vec3 dir, float str)
{
	this->ShadowShader = LoadShaders("./shaders/shadowMap.vs", "./shaders/shadowMap.fs");
	glGenFramebuffers(1, &this->shadowBuffer);

	glGenTextures(1, &this->shadowTexture);
	glBindTexture(GL_TEXTURE_2D, this->shadowTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, WIDTH * 5, HEIGHT * 5, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindFramebuffer(GL_FRAMEBUFFER, this->shadowBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->shadowTexture, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	this->setDirection(dir, str);
}

void Wind::drawWindMap()
{
}

glm::vec3 Wind::getLocalWind(glm::vec3 pos)
{

	float x,y,z;
	float s;
	glm::mat4 Projection = getOrthoProject(this->dir);
	glm::mat4 View = getOrthoView(this->dir);
	glm::mat4 VP = Projection*View*glm::translate(glm::mat4(1.0f),pos);
	glm::vec4 lightPos = VP*glm::vec4(1.0f);
	x = lightPos.x*0.5 + 0.5;
	y = lightPos.y*0.5 + 0.5;
	z = lightPos.z*0.5 + 0.5;
	z = (z < 0) ? 0 : z;
	z = (z > 1) ? 1 : z;
	int ix=x * WIDTH;
	int iy = y * HEIGHT;

	ix = (x <= 0) ? 0 : x;
	ix = (x >= WIDTH) ? WIDTH-1 : x;
	iy = (y <= 0) ? 0 : y;
	iy = (y >= HEIGHT) ? HEIGHT-1 : y;
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->shadowBuffer);
	glReadPixels(ix,iy , 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &s);
	////std::cerr << "VITR: " << ix << ";"<< iy << ";" << s << "\n";
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	if (s < z - 0.0001) {
		s = 0.5;
		////std::cerr << "VITR: " << ix << ";" << iy << ";" << s << "\n";
	}
	else {
		s = 1;
	}
	return glm::rotateY(this->dir,(float)this->noise->perlinNoise2D(x*WIDTH,y*HEIGHT)/10)*s*this->strength*this->noise->perlinNoise2D(x*WIDTH, y*HEIGHT);
}

Wind::Wind()
{
	this->noise = new PerlinNoise();
}


Wind::~Wind()
{
	glDeleteBuffers(1, &this->shadowBuffer);
	glDeleteTextures(1, &this->shadowTexture);
	glDeleteProgram(this->ShadowShader);
}
