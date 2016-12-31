#include "ground.h"
#include "controls.h"
void ground::draw()
{
	glUseProgram(this->shader);
	glm::mat4 Projection = getProject();
	glm::mat4 View = getView();
	//glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Projection * View*this->getPosition();
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
	//std::cerr << sizeof(this->Skybox.vertexBuffer) << std::endl;
	//std::cerr << sizeof(this->models[i].vertexBuffer) << std::endl;
	glDrawArrays(GL_TRIANGLES, 0, this->getCountOfVertex());
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

ground::ground()
{
	this->classID = 1;
}


ground::~ground()
{
}
