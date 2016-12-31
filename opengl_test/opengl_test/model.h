#pragma once
#include "loader.h"
#include "includes.h"
#include "texture.h"
//#include "bulletC.h"
class model
{
protected:
	static int counter;
	
	int index;
	std::vector <glm::vec2> uv;
	std::vector <glm::vec3> ver;
	std::vector <glm::vec3> nor;
	int rigidBodyIndex;
	int textureHeight;
	int textureWidth;
	GLuint shader;
	GLuint textureID;
	GLuint MVPID;
public:
	int classID = 0;
	glm::mat4 matrix;
	glm::vec3 velocity = glm::vec3(0.0f);
	GLuint vertexBuffer;
	GLuint uvBuffer;
	GLuint textur;

	int load_3DModel(std::string path);
	int load_texture(const char *path);
	int buffer();

	int setVelocity (glm::vec3 dir);
	void setPosition(glm::mat4 mat);
	glm::mat4 getPosition();
	glm::vec3 getVelocity();

	GLvoid * getVer();
	GLvoid * getUv();
	GLvoid* getNor();
	std::vector<glm::vec3> getVertices();
	int getSizeofVer();
	int getSizeofUv();
	int getSizeofNor();
	int getCountOfVertex();
	void setShader(GLuint sh, GLuint texturID, GLuint MVPID);
	void calculateVelocity();
	//void rotate(glm::vec3 angle);
	void scale(glm::vec3 vector);
	void translate(glm::vec3 vector);
	void draw();
	void setRigidBodyIndex(int id);
	int getRigidBodyIndex();
	void setIndex(int i);
	int getIndex();
	int hitted(int byWho);
	model();
	virtual ~model();
};

///////////enum pro navratove hodnoty funkce hitted
#define DESTROY -1;
#define NOTHING 0;