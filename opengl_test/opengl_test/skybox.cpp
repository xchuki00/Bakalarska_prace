#include "skybox.h"
#include "texture.h"
#include "Shader.h"
#include "controls.h"
float points[] = {
	-10.0f,  10.0f, -10.0f,
	-10.0f, -10.0f, -10.0f,
	10.0f, -10.0f, -10.0f,
	10.0f, -10.0f, -10.0f,
	10.0f,  10.0f, -10.0f,
	-10.0f,  10.0f, -10.0f,

	-10.0f, -10.0f,  10.0f,
	-10.0f, -10.0f, -10.0f,
	-10.0f,  10.0f, -10.0f,
	-10.0f,  10.0f, -10.0f,
	-10.0f,  10.0f,  10.0f,
	-10.0f, -10.0f,  10.0f,

	10.0f, -10.0f, -10.0f,
	10.0f, -10.0f,  10.0f,
	10.0f,  10.0f,  10.0f,
	10.0f,  10.0f,  10.0f,
	10.0f,  10.0f, -10.0f,
	10.0f, -10.0f, -10.0f,

	-10.0f, -10.0f,  10.0f,
	-10.0f,  10.0f,  10.0f,
	10.0f,  10.0f,  10.0f,
	10.0f,  10.0f,  10.0f,
	10.0f, -10.0f,  10.0f,
	-10.0f, -10.0f,  10.0f,

	-10.0f,  10.0f, -10.0f,
	10.0f,  10.0f, -10.0f,
	10.0f,  10.0f,  10.0f,
	10.0f,  10.0f,  10.0f,
	-10.0f,  10.0f,  10.0f,
	-10.0f,  10.0f, -10.0f,

	-10.0f, -10.0f, -10.0f,
	-10.0f, -10.0f,  10.0f,
	10.0f, -10.0f, -10.0f,
	10.0f, -10.0f, -10.0f,
	-10.0f, -10.0f,  10.0f,
	10.0f, -10.0f,  10.0f
};

int skybox::init()
{

	loadObj("skybox.obj",this->ver,this->uv,this->nor);
	std::cerr << "skybox init" << std::endl;
	return 0;
}

int skybox::load_texture( const char* left, const char* front, const char* right, const char* back, const char* top, const char* bottom)
{
	//this->textur = new GLuint;
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &this->textur);
	loadTextureCube(left, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, &this->textur);
	loadTextureCube(right, GL_TEXTURE_CUBE_MAP_POSITIVE_X, &this->textur);
	loadTextureCube(front, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, &this->textur);
	loadTextureCube(back, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, &this->textur);
	loadTextureCube(bottom, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, &this->textur);
	loadTextureCube(top, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, &this->textur);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	std::cerr << "skybox textury nacteny" << std::endl;
	return 0;
}

int skybox::buffer()
{
/*
	glGenBuffers(1, &(this->vertexBuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
	*/
	glGenBuffers(1, &(this->vertexBuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->getSizeofVer(), this->getVer(), GL_STATIC_DRAW);

	/*
	glGenBuffers(1, &this->uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
	*/
	return 0;
}



int skybox::addShader(std::string vertexShader, std::string fragmentShader)
{
	this->shader = LoadShaders(vertexShader, fragmentShader);
	this->textureID = glGetUniformLocation(this->shader, "textureSampler");
	this->MVID = glGetUniformLocation(this->shader, "MV");
	return 0;

	return 0;
}


skybox::skybox()
{
}


skybox::~skybox()
{
	glDeleteBuffers(1, &this->vertexBuffer);
	glDeleteBuffers(1, &this->uvBuffer);
	glDeleteProgram(this->shader);
}