#pragma once
#include "crossHair.h"
#include "Shader.h"
#include "texture.h"
//#include "texture-cizi.cpp"
//poloha vybraneho miridla v texture crosshairs64.tga, pocitano od 0


void crossHair::print()
{


	std::cerr << "RC" <<this->PositionX <<"," <<this->sizeX << " " << this->PositionY << "," << this->sizeY << "\n";
	std::cerr << "RC" << this->Column << "," << this->MaxColumn << " " << this->Row << "," << this->MaxRow << "\n";
}

void crossHair::buffer()
{
	std::vector<glm::vec2> ver;
	std::vector<glm::vec2> uv;
	glm::vec2 Vup_left = glm::vec2(this->PositionX, this->PositionY);
	glm::vec2 Vdown_left = glm::vec2(this->PositionX, this->PositionY - this->sizeY);
	glm::vec2 Vup_right = glm::vec2(this->PositionX + this->sizeX, this->PositionY);
	glm::vec2 Vdown_right = glm::vec2(this->PositionX + this->sizeX, this->PositionY - this->sizeY);
	
	ver.push_back(Vup_left);
	ver.push_back(Vdown_left);
	ver.push_back(Vup_right);

	ver.push_back(Vdown_right);
	ver.push_back(Vup_right);
	ver.push_back(Vdown_left);
		
	
	//levy horni roh
	float x = (this->Column/this->MaxColumn);
	float y = (this->Row/this->MaxRow);
	float partX = 1 / this->MaxColumn;
	float partY = 1 / this->MaxRow;

	glm::vec2 Uup_left = glm::vec2(x,y);
	glm::vec2 Udown_left = glm::vec2(x,y+partY);
	glm::vec2 Uup_right = glm::vec2(x+partX,y);
	glm::vec2 Udown_right = glm::vec2(x +partX, y+partY);

	uv.push_back(Uup_left);
	uv.push_back(Udown_left);
	uv.push_back(Uup_right);

	uv.push_back(Udown_right);
	uv.push_back(Uup_right);
	uv.push_back(Udown_left);

	glBindBuffer(GL_ARRAY_BUFFER,this->VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, ver.size() * sizeof(glm::vec2), &ver[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, this->UVbuffer);
	glBufferData(GL_ARRAY_BUFFER, uv.size() * sizeof(glm::vec2), &uv[0], GL_STATIC_DRAW);
}

crossHair::crossHair()
{
}

crossHair::~crossHair()
{
}
