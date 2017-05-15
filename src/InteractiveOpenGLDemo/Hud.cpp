#include "Hud.h"
#include "texture.h"
#include "Shader.h"

///Set left up corner of hud element on x,y position on screen, x and y are in pixels
GLuint Hud::shader = 0;
void Hud::setShader(std::string VectorPath, std::string FargmentPath)
{
	shader = LoadShaders(VectorPath, FargmentPath);
}

void Hud::setPosition(int x, int y, int sizex, int sizey)
{
	this->PositionX = x;
	this->PositionY = y;
	this->sizeX = sizex;
	this->sizeY = sizey;

}

void Hud::setRowAColumn(float r, float c, float maxR, float maxC)
{
	this->MaxRow = maxR;
	this->MaxColumn = maxC;
	if (r < this->MaxRow && c < this->MaxColumn) {
		this->Row = r;
		this->Column = c;
	}
	else {
		this->Row = this->MaxRow;
		this->Column = this->MaxColumn;
	}

	this->buffer();
}


void Hud::init(std::string path)
{
	if (this->texture == 0) {
		this->texture = loadTexture2d(path.c_str(), &this->height, &this->height, GL_RGBA);
		glGenBuffers(1, &this->UVbuffer);
		glGenBuffers(1, &this->VertexBuffer);
		this->textureID = glGetUniformLocation(shader, "texture_sampler");
		this->half_width_ID = glGetUniformLocation(shader, "half_width");
		this->half_height_ID = glGetUniformLocation(shader, "half_height");
	}
}

void Hud::buffer()
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
	float x = (this->Column / this->MaxColumn);
	float y = (this->Row / this->MaxRow);
	float partX = 1 / this->MaxColumn;
	float partY = 1 / this->MaxRow;

	glm::vec2 Uup_left = glm::vec2(x, y);
	glm::vec2 Udown_left = glm::vec2(x, y + partY);
	glm::vec2 Uup_right = glm::vec2(x + partX, y);
	glm::vec2 Udown_right = glm::vec2(x + partX, y + partY);

	uv.push_back(Uup_left);
	uv.push_back(Udown_left);
	uv.push_back(Uup_right);

	uv.push_back(Udown_right);
	uv.push_back(Uup_right);
	uv.push_back(Udown_left);

	glBindBuffer(GL_ARRAY_BUFFER, this->VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, ver.size() * sizeof(glm::vec2), &ver[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, this->UVbuffer);
	glBufferData(GL_ARRAY_BUFFER, uv.size() * sizeof(glm::vec2), &uv[0], GL_STATIC_DRAW);
	this->sizeOfBuffer = ver.size();
}

void Hud::draw()
{
	//std::cerr << "TEXTUREA" << this->texture << std::endl;
	if (!this->visible) {
		return;
	}
	glUseProgram(shader);
	glUniform1i(this->half_width_ID, WIDTH/2);
	glUniform1i(this->half_height_ID, HEIGHT/2);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture);
	glUniform1i(this->textureID, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->VertexBuffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);


	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->UVbuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
	glDrawArrays(GL_TRIANGLES, 0, sizeOfBuffer);
	glDisable(GL_BLEND);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

Hud::Hud(std::string path)
{
	this->texture = loadTexture2d(path.c_str(), &this->height, &this->height, GL_RGBA);
	glGenBuffers(1, &this->UVbuffer);
	glGenBuffers(1, &this->VertexBuffer);
	this->textureID = glGetUniformLocation(shader, "texture_sampler");
	this->half_width_ID = glGetUniformLocation(shader, "half_width");
	this->half_height_ID = glGetUniformLocation(shader, "half_height");
}

Hud::Hud()
{
	this->ClassID = HUD;
}


Hud::~Hud()
{
	std::cerr << "hud delete\n";
	glDeleteBuffers(1, &this->VertexBuffer);
	glDeleteBuffers(1, &this->UVbuffer);
	glDeleteTextures(1, &this->texture);
	glDeleteProgram(shader);
}
