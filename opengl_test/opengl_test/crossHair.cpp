#include "crossHair.h"
#include "Shader.h"
#include "texture.h"
//#include "texture-cizi.cpp"
//poloha vybraneho miridla v texture crosshairs64.tga, pocitano od 0
#define ROW 5	
#define  COLUMN 0
void crossHair::init(std::string path)
{
	if(this->texture==0){
		this->texture = loadTexture2d(path.c_str(), &this->height, &this->height);
		glGenBuffers(1, &this->UVbuffer);
		glGenBuffers(1, &this->VertexBuffer);
		this->shader = LoadShaders("crossHair.vertexShader", "crossHair.fragmentShader");
		this->uniformID = glGetUniformLocation(this->shader, "texture_sampler");
	}
}

void crossHair::buffer()
{
	std::vector<glm::vec2> ver;
	std::vector<glm::vec2> uv;
	int half_width = WIDTH / 2;
	int half_height = HEIGHT / 2;

	glm::vec2 Vup_left = glm::vec2(half_width - 50, half_height + 50);
	glm::vec2 Vdown_left = glm::vec2(half_width - 50, half_height - 50);
	glm::vec2 Vup_right = glm::vec2(half_width + 50, half_height + 50);
	glm::vec2 Vdown_right = glm::vec2(half_width + 50, half_height - 50);
	
	ver.push_back(Vup_left);
	ver.push_back(Vdown_left);
	ver.push_back(Vup_right);

	ver.push_back(Vdown_right);
	ver.push_back(Vup_right);
	ver.push_back(Vdown_left);
		
	
	//levy horni roh
	float x = (COLUMN/8.0f);
	float y = (ROW/8.0f);


	glm::vec2 Uup_left = glm::vec2(x,y);
	glm::vec2 Udown_left = glm::vec2(x,y+1.0f/8.0f);
	glm::vec2 Uup_right = glm::vec2(x+1.0f/8.0f,y);
	glm::vec2 Udown_right = glm::vec2(x + 1.0f / 8.0f, y + 1.0f / 8.0f);

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

void crossHair::draw()
{	

	//std::cerr << "TEXTUREA" << this->texture << std::endl;
	glUseProgram(this->shader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,this->texture);
	glUniform1i(this->uniformID,0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->VertexBuffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);


	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->UVbuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisable(GL_BLEND);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

}

crossHair::crossHair(std::string path)
{
	this->texture = loadTexture2d(path.c_str(),&this->height,&this->height);
	glGenBuffers(1, &this->UVbuffer);
	glGenBuffers(1, &this->VertexBuffer);
	this->shader = LoadShaders("crossHair.vertexShader", "crossHair.fragmentShader");
	this->uniformID = glGetUniformLocation(this->shader,"");
}
crossHair::crossHair()
{
}

crossHair::~crossHair()
{
	glDeleteBuffers(1, &this->VertexBuffer);
	glDeleteBuffers(1, &this->UVbuffer);
	glDeleteTextures(1,&this->texture);
	glDeleteProgram(this->shader);
}
