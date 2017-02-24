#pragma once
#include "Model.h"
#include "Target.h"
#include "crossHair.h"
#include "BulletWorld.h"
class Scene
{
protected:
	//////////////////shaders///////////////
	GLuint shader;
	GLuint depthShader;
	GLuint shadowBuffer = 0;
	GLuint depthTexture;
	GLuint textureID;
	GLuint MVPID;
	GLuint viewID;
	GLuint modelID;
	GLuint DepthBiasID;
	GLuint shadowMapID;
	GLuint depthMVPID;
	GLuint lightInvDirID;
	GLuint VertexArrayID;
	/////////////crosshair/////////////
	crossHair CrossHair;
	////////////bullet////////////
	BulletWorld bulletWorld;

public:
	GLFWwindow* window;
	std::vector <Model*> models;
	Model *player;
	int addModel(
		int clas,
		std::string pathOfObj,
		std::string pathOfTexture,
		glm::mat4 position,
		glm::vec3 velocity,
		float mass
	);
	int removeModels(std::vector <int> destructionQueue);
	int addShader(std::string vertexShader, std::string fragmentShader);
	int addDepthShader(std::string vertexShader, std::string fragmentShader);
	int drawAllModels();
	//////////////////////crosshair///////////
	int addCrossHair(std::string path);
	int drawCrossHair();
	///////////////skybox////////
	int addSkybox(const char* left,
		const char* front,
		const char* right,
		const char* back,
		const char* top,
		const char* bottom);
	////////////INIT///////////
	void calculate();
	int initShadowBuffer();

	int initWindow();
	Scene();
	~Scene();
};

