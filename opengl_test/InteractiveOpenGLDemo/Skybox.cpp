#include "Skybox.h"
#include "texture.h"
#include "misc.h"
#include "controls.h"
#include "Shader.h"
#include "loader.h"

int Skybox::load_3DModel(std::string path) {
	 int ret=loadObj(path, this->ver, this->uv, this->nor);
	 this->buffer();
	 return ret;
}
int Skybox::load_texture(const char * left, const char * front, const char * right, const char * back, const char * top, const char * bottom)
{
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

void Skybox::draw()
{
	glm::mat4 Projection = getProject();
	glm::mat4 View = getView();
	glm::mat4 mat=glm::scale(getMyPosition(),glm::vec3(2,1,2));

	glm::mat4 MV = Projection * View*mat;

	glUseProgram(this->shader);
	glUniformMatrix4fv(this->MVPID, 1, GL_FALSE, &MV[0][0]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->textur);
	glUniform1i(this->textureID, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDisableVertexAttribArray(0);
}

int Skybox::buffer()
{
	/*
	glGenBuffers(1, &(this->vertexBuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
	*/
	glGenBuffers(1, &(this->vertexBuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->ver.size()*sizeof(glm::vec3), &this->ver[0], GL_STATIC_DRAW);
	return 0;
}

int Skybox::addShader(std::string vertexShader, std::string fragmentShader)
{
	this->shader = LoadShaders(vertexShader, fragmentShader);
	this->textureID = glGetUniformLocation(this->shader, "textureSampler");
	this->MVPID = glGetUniformLocation(this->shader, "MV");
	return 0;
}

Skybox::Skybox()
{
	this->classID = SKYBOX;

}


Skybox::~Skybox()
{
	glDeleteBuffers(1, &this->vertexBuffer);
	glDeleteBuffers(1, &this->indexBuffer);
	glDeleteProgram(this->shader);
}
