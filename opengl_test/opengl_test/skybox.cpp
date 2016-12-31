#include "skybox.h"
#include "texture.h"
#include "Shader.h"
#include "controls.h"
float points[] = {
	//front
	-10.0f,  10.0f, -10.0f, //levy hroni zadni
	-10.0f, -10.0f, -10.0f, //levy dolni zadni
	10.0f, -10.0f, -10.0f,	//pravy dolni zadni
	10.0f, -10.0f, -10.0f,
	10.0f,  10.0f, -10.0f,
	-10.0f,  10.0f, -10.0f,
	//left
	-10.0f, -10.0f,  10.0f, //levy dolni predni 
	-10.0f, -10.0f, -10.0f,	//levy dolni zadni
	-10.0f,  10.0f, -10.0f,	//levy horni zadni
	-10.0f,  10.0f, -10.0f,
	-10.0f,  10.0f,  10.0f,
	-10.0f, -10.0f,  10.0f,
	//right
	10.0f, -10.0f, -10.0f,
	10.0f, -10.0f,  10.0f,
	10.0f,  10.0f,  10.0f,
	10.0f,  10.0f,  10.0f,
	10.0f,  10.0f, -10.0f,
	10.0f, -10.0f, -10.0f,
	//back
	-10.0f, -10.0f,  10.0f,
	-10.0f,  10.0f,  10.0f,
	10.0f,  10.0f,  10.0f,
	10.0f,  10.0f,  10.0f,
	10.0f, -10.0f,  10.0f,
	-10.0f, -10.0f,  10.0f,
	//top
	-10.0f,  10.0f, -10.0f,
	10.0f,  10.0f, -10.0f,
	10.0f,  10.0f,  10.0f,
	10.0f,  10.0f,  10.0f,
	-10.0f,  10.0f,  10.0f,
	-10.0f,  10.0f, -10.0f,
	//bottom
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

void skybox::draw()
{
	
	glm::mat4 Projection = getProject();
	glm::mat4 View = getView();
	glm::mat4 mat(1.0f);
	glm::mat4 MV = Projection * View*getMyPosition();

	glUseProgram(this->shader);
	glUniformMatrix4fv(this->MVID, 1, GL_FALSE, &MV[0][0]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->textur);
	glUniform1i(this->textureID, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDisableVertexAttribArray(0);
	
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
	this->classID = 2;
}


skybox::~skybox()
{
	glDeleteBuffers(1, &this->vertexBuffer);
	glDeleteBuffers(1, &this->uvBuffer);
	glDeleteProgram(this->shader);
}
