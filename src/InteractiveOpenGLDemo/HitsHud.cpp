#include "HitsHud.h"



void HitsHud::setPrefix(std::string s)
{
	this->prefix = s;
}

void HitsHud::setPostFix(std::string s)
{
	this->postfix = s;
}

void HitsHud::setContains(int i)
{
	std::ostringstream ss;
	ss << i;
	this->contains = ss.str();
	this->buffer();

}

void HitsHud::setContains(float f)
{
	std::ostringstream ss;
	ss << f;
	this->contains = ss.str();
	this->buffer();
}

void HitsHud::setContains(std::string s)
{
	this->contains = s;
	this->buffer();
}

void HitsHud::setContains(char c)
{
	this->contains = c;
	this->buffer();

}

void HitsHud::buffer()
{
	std::vector<glm::vec2> ver;
	std::vector<glm::vec2> uv;
	int posX = this->PositionX;
	int posY = this->PositionY;
	int sizeOfOneX = this->sizeX;
	int sizeOfOneY = this->sizeY;
	if (this->contains.size() <= 0) {
		this->visible = false;
		return;
	}
	std::string complet = this->prefix + this->contains + this->postfix;
	for (int i = 0; i < complet.size(); i++) {
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
		posX += sizeOfOneX;

		int ascii = (int)(complet[i]);
		ascii = (ascii > 122)? 48:ascii;
		float x = (ascii % (int)(this->MaxColumn));
		float y = 15 - (ascii / (int)(this->MaxRow));
		x /=this->MaxColumn;
		y/=this->MaxRow;

		float partX = 1 / this->MaxColumn;
		float partY = 1 / this->MaxRow;

		glm::vec2 Uup_left = glm::vec2(x, y+partY);
		glm::vec2 Udown_left = glm::vec2(x, y);
		glm::vec2 Uup_right = glm::vec2(x + partX, y + partY);
		glm::vec2 Udown_right = glm::vec2(x + partX, y);

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


HitsHud::HitsHud()
{
	this->ClassID == HITSHUD;
}


HitsHud::~HitsHud()
{
}
