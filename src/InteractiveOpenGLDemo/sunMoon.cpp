#include "sunMoon.h"
#include "controls.h"
#include "Shader.h"

glm::mat4 SunMoon::getPosition()
{
	static int lastTime = 0;
	float angle = ((2 * glm::pi<float>()) / this->period)*((*time) - lastTime);
	this->modelMatrix = glm::rotate(this->modelMatrix,angle,this->axis);
	
	this->transalteVec = glm::rotate(this->transalteVec, angle, this->axis);
	glm::vec3 trans = this->transalteVec + getVectorOfPosition();
	this->modelMatrix[3][0] = trans.x;
	this->modelMatrix[3][1] = trans.y;
	this->modelMatrix[3][2] = trans.z;
	this->light->dir = (-1)*trans;
	lastTime = *time;
	return this->modelMatrix;
}

void SunMoon::draw(std::vector<DirectionLight> lights)
{
	glm::mat4 Projection = getProject();
	glm::mat4 View = getView();
	glm::mat4 MVP = Projection * View * this->getPosition();
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glUseProgram(this->shader);
	glUniformMatrix4fv(this->MVPID, 1, GL_FALSE, &MVP[0][0]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->textur);
	glUniform1i(this->textureID, 0);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MyVertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(MyVertex), (const GLvoid*)sizeof(glm::vec3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(MyVertex), (const GLvoid*)(sizeof(glm::vec2) + sizeof(glm::vec3)));
	//std::cerr << this->classID << "vertexpoitn\n";
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);
	glDrawElements(GL_TRIANGLES, this->countOfIndex, GL_UNSIGNED_SHORT, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void SunMoon::DrawToShadowMap(glm::vec3 orthoDir)
{
}

void SunMoon::setOffset(float o)
{
	this->offset = o;
	this->modelMatrix = glm::rotate(this->modelMatrix, this->offset, this->axis);

	this->transalteVec = glm::rotate(this->transalteVec, this->offset, this->axis);
	glm::vec3 trans = this->transalteVec + getVectorOfPosition();
	this->modelMatrix[3][0] = trans.x;
	this->modelMatrix[3][1] = trans.y;
	this->modelMatrix[3][2] = trans.z;
	if(this->light != NULL)
		this->light->dir = (-1)*trans;

}

void SunMoon::setPeriod(float p)
{
	this->period = p;
}

void SunMoon::setLightSource(DirectionLight * l)
{
	this->light = l;
}

void SunMoon::setRefToTime(double * timeI)
{
	this->time = timeI;
}

void SunMoon::setCircle(float r, float angle)
{
	this->axis = glm::rotate(glm::vec3(0, 0, 1),angle, glm::vec3(1, 0, 0));
	this->transalteVec = glm::vec3(r, 0, 0);
}

SunMoon::SunMoon()
{
	this->classID = SUNMOON;
	this->modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(10, 0, 0));
	this->axis = glm::rotate(glm::vec3(0, 0, 1), glm::pi<float>() / 36, glm::vec3(1, 0, 0));
	this->shader = LoadShaders("SunMoon.vs", "SunMoon.fs");
	this->textureID = glGetUniformLocation(this->shader, "myTextureSampler");

	this->MVPID = glGetUniformLocation(this->shader, "MV");
}


SunMoon::~SunMoon()
{
}
