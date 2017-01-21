#pragma once
#include "loader.h"
#include "includes.h"
#include "texture.h"
//#include "bulletC.h"
class model
{
protected:
	static int counter;
	
	std::vector <glm::vec2> uv;
	std::vector <glm::vec3> ver;
	std::vector <glm::vec3> nor;
	std::vector<unsigned short> indices;
	int rigidBodyIndex;
	int textureHeight;
	int textureWidth;
	GLuint shader;
	GLuint depthShader;

	GLuint textureID;
	GLuint MVPID;
	GLuint viewID;
	GLuint modelID;
	GLuint DepthBiasID;
	GLuint shadowMapID;
	GLuint depthMVPID;
	GLuint lightInvDirID;
public:
	int classID = 0;
	glm::mat4 matrix;
	glm::mat4 depthMVP;
	glm::vec3 velocity = glm::vec3(0.0f);
	GLuint vertexBuffer;
	GLuint uvBuffer;
	GLuint normalBuffer;
	GLuint elementBuffer;
	GLuint textur;
	


	int load_3DModel(std::string path);
	int load_texture(const char *path);
	int buffer();
	void setShader(
		GLuint sh,
		GLuint texturID,
		GLuint MVPID,
		GLuint v,
		GLuint m,
		GLuint db,
		GLuint shadowMap,
		GLuint lightInvDir,
		GLuint depthSh,
		GLuint depthID
	);

	void setRigidBodyIndex(int id);
	int getRigidBodyIndex();
	int hitted(model* byWho);
	double getDmg();

	int setVelocity (glm::vec3 dir);
	void setPosition(glm::mat4 mat);
	glm::mat4 getPosition();
	glm::vec3 getVelocity();
	void calculateVelocity();

	GLvoid * getVer();
	std::vector<glm::vec3> getVertices();
	int getSizeofVer();
	int getCountOfVertex();

	GLvoid * getUv();
	int getSizeofUv();

	GLvoid* getNor();
	int getSizeofNor();
	
	GLvoid * getIndices();
	int getSizeofInd();

	//void rotate(glm::vec3 angle);
	void scale(glm::vec3 vector);
	void translate(glm::vec3 vector);
	void draw(GLuint dephtTexture);
	void depthDraw();
	model();
	virtual ~model();
};

