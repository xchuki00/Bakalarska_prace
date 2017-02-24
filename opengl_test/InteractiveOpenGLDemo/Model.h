#pragma once
#include "loader.h"

class Model
{
protected:
	///////////vrcholy a buffry//////////
	GLuint vertexBuffer;
	GLuint indexBuffer;
	unsigned int countOfIndex;
	///////////Odkazy do shaderu///////////
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
	////////////bullet///////////
	btCollisionObject *bt;
	////////textura
	GLuint textur;
	int textureHeight;
	int textureWidth;

	int buffer();
public:
	std::vector<MyVertex> vertices;
	std::vector<unsigned short> indices;
	int classID = MODEL;
	glm::mat4 modelMatrix;
	glm::mat4 depthMVP;

	////////////funkce pro init////////////
	virtual int load_3DModel(std::string path);
	virtual int load_texture(const char *path);
	
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
	virtual void setShader(GLuint sh);
	void setRigidBodyIndex(int id);
	virtual void setPosition(glm::mat4 mat);
	////////////kolize//////////////
	btCollisionObject * getObj();
	void setObj(btCollisionObject* obj);
	virtual int hitted(Model* byWho);
	virtual double getDmg();
	//////////DRAW////////////////////
	virtual void draw();
	virtual void depthDraw();
	Model();
	~Model();
};

