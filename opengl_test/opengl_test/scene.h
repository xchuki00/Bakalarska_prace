#pragma once
#include "model.h"
#include "bulletC.h"
#include "skybox.h"
#include "ground.h"
#include "crossHair.h"
#include "modelXbullet.h"
#include "shadowmap.h"
#include "player.h"
class scene
{
	
	bulletC bulletWord;
	skybox Skybox;
	ground Ground;
	
public:
	std::vector <model*> models;
	std::vector <modelXbullet*> modelsXbullets;
	//std::vector<lights> ligths;
	glm::vec3 light=glm::vec3(0.5f,2,2);
	GLFWwindow* window;
	GLuint shader;
	GLuint depthShader;
	player * Player;

	GLuint shadowBuffer = 0;
	GLuint depthTexture;
	GLuint VertexArrayID;
	crossHair CrossHair;
//////////////////ID TO SHADERS////////////
	GLuint textureID;
	GLuint MVPID;
	GLuint viewID;
	GLuint modelID;
	GLuint DepthBiasID;
	GLuint shadowMapID;
	GLuint depthMVPID;
	GLuint lightInvDirID;
	////////////GROUND/////////////
	int addGround(std::string pathOfObj, std::string pathOfTexture);
	int drawGround();
	void print();
	///////////////SKYBOX////////////////////
	int addSkybox(
		std::string left,
		std::string front,
		std::string right,
		std::string back,
		std::string top,
		std::string bottom,
		std::string vertexShader,
		std::string fragmentShader
		);
	int drawSkybox();
	////////////////MODEL//////////////
	int addModel(
		int clas,
		std::string pathOfObj,
		std::string pathOfTexture,
		glm::mat4 position,
		glm::vec3 velocity,
		float mass
	);
	int addModel(model *mod, float mass);
	int removeModel(std::vector <int> destructionQueue);
	int addShader(std::string vertexShader, std::string fragmentShader);
	int addDepthShader(std::string vertexShader, std::string fragmentShader);
	int drawAllModels();
	int bufferCrossHair(std::string path);
	int drawCrossHair();
	int getModelsSize();
	////////////INIT///////////
	void calculate();
	int initShadowBuffer();
	int initWindow();
	scene();
	virtual ~scene();
};

