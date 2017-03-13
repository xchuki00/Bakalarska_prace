#include "Model.h"
#include "loader.h"
#include "texture.h"
#include "controls.h"
#include "misc.h"
/////////////MATRIX FOR TRANSFORM [-1,1] to [0,1]///////
glm::mat4 coordiationTransformMatrix(
	0.5, 0.0, 0.0, 0.0,
	0.0, 0.5, 0.0, 0.0,
	0.0, 0.0, 0.5, 0.0,
	0.5, 0.5, 0.5, 1.0
);
glm::vec3 light(5, 5, 0);
btCollisionObject * Model::getObj()
{
	return this->bt;
}
void Model::setObj(btCollisionObject * obj)
{
	this->bt = obj;
}
int Model::hitted(Model * byWho)
{
	return 0;
}
double Model::getDmg()
{
	return 0.0;
}
glm::mat4 Model::getPosition()
{
	return this->modelMatrix;
}
void Model::calc()
{
}
void Model::draw()
{


//	std::cerr << glm::to_string(getMyPosition()) << std::endl;
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glUseProgram(this->shader);
	glm::mat4 Projection = getProject();
	glm::mat4 View = getView();
	glm::mat4 MVP = Projection * View * this->getPosition();
	glUniformMatrix4fv(this->MVPID, 1, GL_FALSE, &MVP[0][0]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->textur);
	glUniform1i(this->textureID, 0);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MyVertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(MyVertex), (const GLvoid*)sizeof(glm::vec3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(MyVertex), (const GLvoid*)(sizeof(glm::vec2) + sizeof(glm::vec3)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);

	glDrawElements(GL_TRIANGLES, this->countOfIndex, GL_UNSIGNED_SHORT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

}

void Model::depthDraw()
{
}

Model::Model()
{
	this->classID = MODEL;
}


Model::~Model()
{
	glDeleteBuffers(1, &this->vertexBuffer);
	glDeleteBuffers(1, &this->indexBuffer);
	glDeleteProgram(this->shader);
}

int Model::load_3DModel(std::string path)
{
	this->countOfIndex = loadObjAss(path,this->vertices,this->indices);
	this->buffer();
	std::cerr << "model " << path << " nacten a nabufrovan." << std::endl;
	return 0;
}

int Model::load_texture(const char * path)
{
	this->textur = loadTexture2d(path, &this->textureHeight, &this->textureWidth);

	return 0;
}

int Model::set3DModel(std::vector<MyVertex> v)
{
	this->vertices = v;

	return 0;
}

int Model::setIndices(std::vector<unsigned short> i)
{
	this->indices = i;
	return 0;
}

int Model::setTexture(GLuint t)
{
	this->textur = t;
	return 0;
}

int Model::buffer()
{
	std::cerr << "VERTEX" << this->vertices.size()<<this->indices.size() << std::endl;
/*	for (int i = 0; i < this->vertices.size(); i++) {
		std::cerr << glm::to_string(this->vertices[i]->pos)<<"\n";
	}
	for (int i = 0; i < this->indices.size(); i++) {
		std::cerr << this->indices[i] << "\t";
	}*/
	//std::cerr << glm::to_string(this->modelMatrix) << std::endl;
	glGenBuffers(1, &this->vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MyVertex) * this->vertices.size(), &this->vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &this->indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * this->indices.size(), &this->indices[0], GL_STATIC_DRAW);
	//std::cerr << "prdel";
	return 0;
}

void Model::setShader(GLuint sh, GLuint texturID, GLuint MVPID, GLuint v, GLuint m, GLuint db, GLuint shadowMap, GLuint lightInvDir, GLuint depthSh, GLuint depthID)
{
	this->shader = sh;
	this->MVPID = MVPID;
	this->textureID = texturID;
}

void Model::setShader(GLuint sh)
{
	this->shader = sh;
	this->textureID = glGetUniformLocation(this->shader, "myTextureSampler");
	this->MVPID = glGetUniformLocation(this->shader, "MVP");
}

void Model::setRigidBodyIndex(int id)
{
}

void Model::setPosition(glm::mat4 mat)
{
	mat4Copy(mat, &this->modelMatrix);
}

