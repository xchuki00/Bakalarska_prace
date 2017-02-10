#include "player.h"
#include "controls.h"


glm::mat4 player::getPosition()
{
	return this->matrix;

}

void player::draw()
{
	glUseProgram(this->shader);
	glm::mat4 Projection = getProject();
	glm::mat4 View = getView();
	glm::mat4 MVP = Projection * View * this->getPosition();
	//std::cerr << glm::to_string(MVP) << std::endl;
	glUniformMatrix4fv(this->MVPID, 1, GL_FALSE, &MVP[0][0]);
	//nahraju texturu do shaderu
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->textur);
	glUniform1i(this->textureID, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->uvBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_TRIANGLES, 0, this->ver.size());
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	setMyPosition(glm::vec3(this->matrix[3][0], this->matrix[3][1], this->matrix[3][2]));
	
}

int player::hitted(model * byWho)
{
	std::cerr <<this->classID<<" "<<byWho->classID <<"PLAYE\n";
	if (byWho->classID == GROUND) {
		this->onground = true;
	}
	return 0;
}

void player::jump()
{
	this->onground = false;
}

bool player::landed()
{
	return this->onground;
}

player::player()
{
	this->classID = PLAYER;
}


player::~player()
{
}
