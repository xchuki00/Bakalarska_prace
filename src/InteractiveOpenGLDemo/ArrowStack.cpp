#include "ArrowStack.h"



void ArrowStack::minus()
{
	this->countOfArrow--;
	this->buffer();
}

void ArrowStack::setCountOfArrows(int count)
{
	this->countOfArrow = count;
	this->initialCount = count;
}

int ArrowStack::getCountofArrows()
{

	return this->countOfArrow;
}
void ArrowStack::buffer()
{
	std::vector<glm::vec2> ver;
	std::vector<glm::vec2> uv;
	int posX = this->PositionX;
	int posY = this->PositionY;
	int sizeOfOneX = this->sizeX;
	int sizeOfOneY = this->sizeY/this->initialCount;
	if (this->countOfArrow <= 0) {
		this->visible = false;
		return;
	}
	for (int i = 0; i < this->countOfArrow; i++) {
		glm::vec2 Vup_left = glm::vec2(posX, posY);
		glm::vec2 Vdown_left = glm::vec2(posX, posY - sizeOfOneY);
		glm::vec2 Vup_right = glm::vec2(posX + sizeOfOneX, posY);
		glm::vec2 Vdown_right = glm::vec2(posX + sizeOfOneX, posY - sizeOfOneY);

		ver.push_back(Vup_left);
		ver.push_back(Vdown_left);
		ver.push_back(Vup_right);

		ver.push_back(Vdown_right);
		ver.push_back(Vup_right);
		ver.push_back(Vdown_left);
		posY -= sizeOfOneY;

		glm::vec2 Uup_left = glm::vec2(0, 0);
		glm::vec2 Udown_left = glm::vec2(0, 1);
		glm::vec2 Uup_right = glm::vec2(1, 0);
		glm::vec2 Udown_right = glm::vec2(1, 1);

		uv.push_back(Uup_left);
		uv.push_back(Udown_left);
		uv.push_back(Uup_right);

		uv.push_back(Udown_right);
		uv.push_back(Uup_right);
		uv.push_back(Udown_left);
	}
	glBindBuffer(GL_ARRAY_BUFFER, this->VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, ver.size() * sizeof(glm::vec2), &ver[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, this->UVbuffer);
	glBufferData(GL_ARRAY_BUFFER, uv.size() * sizeof(glm::vec2), &uv[0], GL_STATIC_DRAW);
	this->sizeOfBuffer = ver.size();
}

ArrowStack::ArrowStack()
{
	this->ClassID = ARROWSTACK;
}


ArrowStack::~ArrowStack()
{
}
