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
int Skybox::load_DayNighttexture(bool day,const char * left, const char * front, const char * right, const char * back, const char * top, const char * bottom)
{
	glActiveTexture(GL_TEXTURE0);
	GLuint *texture;
	if (day) {
		texture = &dayTextur;
	}
	else {
		texture = &nightTextur;
	}
	glGenTextures(1, texture);
	loadTextureCube(left, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, texture);
	loadTextureCube(right, GL_TEXTURE_CUBE_MAP_POSITIVE_X, texture);
	loadTextureCube(front, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, texture);
	loadTextureCube(back, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, texture);
	loadTextureCube(bottom, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, texture);
	loadTextureCube(top, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, texture);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	std::cerr << "skybox textury nacteny" << std::endl;
	return 0;
}
static float lastAngle = glm::pi<float>() / 4;
void Skybox::calcAxis()
{
	glm::vec3 pos = getVectorOfPosition();
	float pi = glm::pi<float>();
	float angle = ((4 * pi) / dayLenght* (*time)) - pi / 4;
	if (axis.empty()) {
		axis.push_back(glm::vec3(1, 0, 0));
		axis.push_back(glm::vec3(0, 1, 0));
	}
	pos.y -= 1.25;
	//glm::pi<float>()/dayLenght* (*time)
	axis.data()[0] = glm::rotate(glm::vec3(1, 0, 0), angle, glm::vec3(0, 0, 1));
	axis.data()[1] = glm::rotate(glm::vec3(0, 1, 0.1), angle, glm::vec3(0, 0, 1));
	float angleB = AngleBetween(this->axis[0],glm::vec3(1, 0, 0));

	std::cerr << "DATAE" << this->dayPart << "    " << angleB << "      " << lastAngle <<"     "<< glm::to_string(this->axis[0]) << std::endl;
	if (angleB > (pi / 4) && angleB < (3 * pi / 4)&& AngleBetween(glm::vec3(1, 0, 0), this->axis[1])>(3 * pi / 4)) {
		angle *= 3;
	}
	else {
		angle += angle/18;
	}
	
	if ((this->dayPart == 0 || this->dayPart == 4) && angleB > lastAngle) {
		this->dayPart++;
	}
	else if ((this->dayPart == 1 || this->dayPart == 5) && angleB > pi/2&& lastAngle< pi/2) {
		this->dayPart++;
	}
	else if ((this->dayPart == 2 || this->dayPart == 6) && angleB < lastAngle) {
		this->dayPart++;
	}
	else if ((this->dayPart == 3 || this->dayPart == 7) && angleB < pi/2 && lastAngle>pi/2) {
		this->dayPart++;
		this->dayPart = this->dayPart % 8;
	}
	lastAngle = angleB;

}


void Skybox::draw()
{
	glm::mat4 Projection = getProject();
	glm::mat4 View = getView();
	glm::mat4 mat=glm::scale(getMyPosition(),glm::vec3(2,2,2));
	
	mat = glm::translate(mat, glm::vec3(0, -1.25, 0));
	//mat = glm::rotate(mat, ((4 * glm::pi<float>()) / dayLenght* (*time)), glm::vec3(0, 0, 1));
	glm::mat4 MV = Projection * View*mat;

	glUseProgram(this->shader);
	glUniformMatrix4fv(this->MVPID, 1, GL_FALSE, &MV[0][0]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->dayTextur);
	glUniform1i(this->dayTextureID, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->nightTextur);
	//std::cerr << "SKY time: " << *this->time << std::endl;
	glUniform1i(this->nightTextureID, 1);
	this->calcAxis();
	//glm::vec3 middle = getVectorOfPosition();
	//middle.y -= 1.25;
	//int day = *time / (1440/8);

	glUniform1i(this->dayID, this->dayPart);
	glUniform3fv(this->axisID,2 , &this->axis[0][0]);
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
/*	axis.push_back(glm::vec3(1, 0, 0) - getVectorOfPosition());
	axis.push_back(glm::vec3(0, 1, 0));
	*/

	return 0;
}

int Skybox::addShader(std::string vertexShader, std::string fragmentShader)
{
	this->shader = LoadShaders(vertexShader, fragmentShader);
	this->dayTextureID = glGetUniformLocation(this->shader, "DaytextureSampler");
	this->nightTextureID = glGetUniformLocation(this->shader, "NighttextureSampler");
	this->dayID = glGetUniformLocation(this->shader, "day");
	this->axisID = glGetUniformLocation(this->shader, "axis");
	this->MVPID = glGetUniformLocation(this->shader, "MV");
	return 0;
}

void Skybox::setRefToTime(double * t)
{
	time = t;
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
