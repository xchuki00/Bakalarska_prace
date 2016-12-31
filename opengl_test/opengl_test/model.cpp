#include "model.h"
#include "misc.h"
#include "controls.h"



int model::load_3DModel(std::string path) {
	loadObj(path, this->ver,this->uv,this->nor);
	
	return 0;
}
int model::load_texture(const char * path) {

	this->textur=loadTexture2d(path,&this->textureHeight,&this->textureWidth);

	/*for (int i = 0; i < this->uv.size(); i++) {
		this->uv[i][0] = this->uv[i][0] * this->textureWidth;
		this->uv[i][1] = this->uv[i][1] * this->textureHeight;
	}*/
	return 0;
}
int model::buffer()
{
	//std::cout << "buffer::"<<this->getSizeofVer()<<"\t"<<this->getCountOfVertex()<<"*"<<sizeof(glm::vec3)<< std::endl;
	glGenBuffers(1, &(this->vertexBuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->getSizeofVer(), this->getVer(), GL_STATIC_DRAW);
	
	glGenBuffers(1, &(this->uvBuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this->uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->getSizeofUv(), this->getUv(), GL_STATIC_DRAW);
	//std::cerr << "textura" << ":" << this->textur << std::endl;
	return 0;
}

int model::setVelocity(glm::vec3 dir)
{
	vec3Copy(dir, &this->velocity);
		return 0;
}

//navrati ukazatel na pole vrcholu/jejich uv ci normal
GLvoid* model::getVer()
{
	return &(this->ver)[0][0];
}
GLvoid* model::getUv()
{
	return &(this->uv)[0][0];
}
GLvoid* model::getNor()
{
	return &(this->nor)[0][0];
}

std::vector<glm::vec3> model::getVertices()
{
	return this->ver;
}

//vrati velikost techto poli
int model::getSizeofVer()
{
	return this->ver.size()*sizeof(glm::vec3);
}
int model::getSizeofUv()
{
	return this->uv.size() * sizeof(glm::vec2);
}
int model::getSizeofNor()
{
	return this->nor.size() * sizeof(glm::vec3);
}

int model::getCountOfVertex()
{
	return this->ver.size();
}

void model::setShader(GLuint sh, GLuint textureid, GLuint mvpid)
{
	this->shader = sh;
	this->textureID = textureid;
	this->MVPID = mvpid;
}
void model::calculateVelocity()
{
	//this->velocity = glm::vec3(0,0,0);
}
//prace s polohou


void model::scale(glm::vec3 vector)
{
	//this->matrix = glm::scale(2.0f, 2.0f, 2.0f);
}
void model::translate(glm::vec3 vector)
{
}
void model::draw()
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
	this->calculateVelocity();

}
void model::setRigidBodyIndex(int id)
{
	this->rigidBodyIndex = id;
}

int model::getRigidBodyIndex()
{
	return this->rigidBodyIndex;
}



void model::setIndex(int i)
{
	this->index = i;
}
int model::getIndex()
{
	return this->index;
}
void model::setPosition(glm::mat4 mat)
{
	mat4Copy(mat, &this->matrix);
}
glm::mat4 model::getPosition()
{
	return this->matrix;
}
glm::vec3 model::getVelocity()
{
	return this->velocity;
}
int model::hitted(int byWho)
{/*
	if (byWho->classID != -1) {
		this->textur = loadTexture2d("red.bmp", &this->textureHeight, &this->textureWidth);
	}
	btRigidBody* body = btRigidBody::upcast(this->obj);
	btVector3 vec = body->getLinearVelocity();
	btVector3 vec2(this->velocity[0], this->velocity[1], this->velocity[2]);
	vec += vec2;
	vec /= 2;
	body->setLinearVelocity(vec);
	//std::cerr << "object " << this->RigidBodyIndex << "zasazen\n";
	*/
	return NOTHING;
}
model::model()
{
	this->classID = 0;
}
model::~model()
{
	glDeleteBuffers(1, &this->vertexBuffer);
	glDeleteBuffers(1, &this->uvBuffer);
}
