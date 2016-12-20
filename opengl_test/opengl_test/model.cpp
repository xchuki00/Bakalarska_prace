#include "model.h"
#include "misc.h"
int model::counter = 0;


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
int model::setSpeed(GLfloat s)
{
	this->speed = s;
	return 0;
}
int model::setDirection(glm::vec3 dir)
{
	vec3Copy(dir, &this->direction);
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

//prace s polohou
glm::mat4 model::getMatrix()
{
	return this->matrix;
}

void model::scale(glm::vec3 vector)
{
	//this->matrix = glm::scale(2.0f, 2.0f, 2.0f);
}
void model::translate(glm::vec3 vector)
{
}
void model::setRigidBodyIndex(int i)
{
	this->RigidBodyIndex = i;
}
int model::getRigidBodyIndex()
{
	return this->RigidBodyIndex;
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
void model::hitted()
{
	//this->textur = loadTexture2d("red.bmp", &this->textureHeight, &this->textureWidth);
	std::cerr << "object " << this->RigidBodyIndex << "zasazen\n";
}
model::model()
{

}
model::~model()
{
	glDeleteBuffers(1, &this->vertexBuffer);
	glDeleteBuffers(1, &this->uvBuffer);
}
