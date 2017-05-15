#pragma once
//#include "loader.h"
#include "structures.h"
#include "animation.h"
#include "ImportModel.h"
#include "Sound.h"
#include "Wind.h"
class Model
{
protected:
	static int idCount;
	
	///////////vrcholy a buffry//////////
	GLuint vertexBuffer;
	GLuint indexBuffer;
	unsigned int countOfIndex;
	int buffer();
	///////////Odkazy do shaderu///////////
	///udelat structur shader
	GLuint shader;
	GLuint shadowShader;
	GLuint BonesID;
	GLuint ModelID;
	GLuint textureID;
	GLuint MVPID;
	GLuint ShadowMVPID;
	GLuint LVPID;
	////////////bullet///////////
	btCollisionObject *bt;
	btDiscreteDynamicsWorld* bulletWorld;
	Wind* wind;
	////////textura
	GLuint textur;
	int textureHeight;
	int textureWidth;
	////////Sound//////
	Sound* sounds;
public:
	int id;
	std::vector<MyVertex> vertices;
	std::vector<unsigned short> indices;
	std::vector<aiMatrix4x4> finalTransform;
	double AnimationTime=0;
	animation *animation = nullptr;
	int classID = MODEL;
	glm::mat4 modelMatrix;
	glm::mat4 depthMVP;
	////////////funkce pro init////////////
	virtual int load_3DModel(std::string path);
	virtual int load_texture(const char *path);
	virtual int set3DModel(ImportModel* importmodel);
	virtual int setTexture(GLuint t);
	virtual void initFinalTransformation();
	virtual void setFinalTransformation();
	virtual void setShader(GLuint sh);
	virtual void setShadowShader(GLuint sh);
	virtual void setAnimatonShaderID();
	void setRigidBodyIndex(int id);
	virtual void setPosition(glm::mat4 mat);
	////////////kolize//////////////
	void setBulletWorld(btDiscreteDynamicsWorld* bw);
	btDiscreteDynamicsWorld* getBulletWorld();
	btCollisionObject * getObj();
	void setObj(btCollisionObject* obj);
	virtual int hitted(Model* byWho);
	virtual float getDmg();
	//////////DRAW////////////////////
	virtual glm::mat4 getPosition();
	virtual void CalcBones(double time);
	virtual void calc();
	virtual void draw(std::vector<DirectionLight> lights);
	virtual void DrawToShadowMap(glm::vec3 orthoDir);
	virtual double getTime();
	/////////Sound/////////
	virtual void setSoundEngine(ISoundEngine* engine);
	virtual void addSound(std::string key,std::string path);
	////////enviroment//////////
	virtual void setWind(Wind* w);
	Model();
	~Model();


};

