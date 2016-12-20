#pragma once
#include "loader.h"
#include "includes.h"
#include "texture.h"
class model
{
protected:
	static int counter;

	int index;
	std::vector <glm::vec2> uv;
	std::vector <glm::vec3> ver;
	std::vector <glm::vec3> nor;
	int RigidBodyIndex;

	int textureHeight;
	int textureWidth;
public:
	glm::mat4 matrix;
	GLfloat speed = 0;
	glm::vec3 direction = glm::vec3(0.0f);

	GLuint vertexBuffer;
	GLuint uvBuffer;
	GLuint textur;

	int load_3DModel(std::string path);
	int load_texture(const char *path);
	int buffer();

	int setSpeed(GLfloat s);
	int setDirection(glm::vec3 dir);
	void setPosition(glm::mat4 mat);

	GLvoid * getVer();
	GLvoid * getUv();
	GLvoid* getNor();

	int getSizeofVer();
	int getSizeofUv();
	int getSizeofNor();
	int getCountOfVertex();
	glm::mat4 getMatrix();
	
	//void rotate(glm::vec3 angle);
	void scale(glm::vec3 vector);
	void translate(glm::vec3 vector);

	void setRigidBodyIndex(int i);
	int getRigidBodyIndex();
	void setIndex(int i);
	int getIndex();
	void hitted();
	model();
	virtual ~model();
};

