#pragma once
//#include "loader.h"
#include "structures.h"
#include "animation.h"
class Model
{
protected:
	static int idCount;
	
	///////////vrcholy a buffry//////////
	GLuint vertexBuffer;
	GLuint indexBuffer;
	unsigned int countOfIndex;
	///////////Odkazy do shaderu///////////
	///udelat structur shader
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
	btDiscreteDynamicsWorld* bulletWorld;
	////////textura
	GLuint textur;
	int textureHeight;
	int textureWidth;

	int buffer();
public:
	int id;
	std::vector<MyVertex> vertices;
	std::vector<unsigned short> indices;

	double AnimationTime=0;
	int classID = MODEL;
	glm::mat4 modelMatrix;
	glm::mat4 depthMVP;

	////////////funkce pro init////////////
	virtual int load_3DModel(std::string path);
	virtual int load_texture(const char *path);
	virtual int set3DModel(std::vector<MyVertex>v);
	virtual int setIndices(std::vector<unsigned short>i);
	virtual int setTexture(GLuint t);
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
	void setBulletWorld(btDiscreteDynamicsWorld* bw);
	btDiscreteDynamicsWorld* getBulletWorld();
	btCollisionObject * getObj();
	void setObj(btCollisionObject* obj);
	virtual int hitted(Model* byWho);
	virtual double getDmg();
	//////////DRAW////////////////////
	virtual glm::mat4 getPosition();
	virtual void CalcBones(double time);
	virtual void calc();
	virtual void draw();
	virtual void depthDraw();
	virtual double getTime();
	Model();
	~Model();
	animation *animation;
	//////////POUZE DOCASNE////////////////
//presunout do vlastni tridy Animation
	//GLuint boneBuffer;
	aiMatrix4x4 inverseGlobalMartix;
	std::vector<bone> bones;
	std::vector<aiMatrix4x4> finalTransform;
	std::map<std::string, unsigned int> bonesMap;
	GLuint BonesID;
	Assimp::Importer *imp;
	const aiNode* nodes = nullptr;
	const aiAnimation* animations = nullptr;
	virtual void updateNode(const aiNode* Node, aiMatrix4x4 ParentTransform, double time);
	virtual const aiNodeAnim* findAnimNode(const aiAnimation *anim,std::string nodeName);
	virtual void getNodeRotation(aiQuaternion* vec, double time,const aiNodeAnim* animNode);
	virtual void getNodeScale(aiVector3D* vec,double time,const aiNodeAnim* animNode);
	virtual void getNodePosition(aiVector3D* vec, double time,const aiNodeAnim* animNode);

};

