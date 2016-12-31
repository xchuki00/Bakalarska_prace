#pragma once
#include "model.h"
#include "bulletC.h"
#include "skybox.h"
#include "ground.h"
#include "crossHair.h"
class scene
{
	
	bulletC bulletWord;
	skybox Skybox;
	ground Ground;
	
public:
	std::vector <model*> models;
	GLFWwindow* window;
	GLuint shader;
	GLuint textureID;
	GLuint MVPID;
	GLuint VertexArrayID;
	crossHair CrossHair;
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
		std::string pathOfObj,
		std::string pathOfTexture, 
		glm::mat4 position,
		glm::vec3 velocity,
		float mass
	);
	int addPlayer(
		std::string pathOfObj,
		std::string pathOfTexture,
		glm::mat4 position,
		glm::vec3 velocity,
		float mass
	);
	int addModel(model *mod, float mass);
	int removeModel(std::vector <model*> destructionQueue);
	int addShader(std::string vertexShader, std::string fragmentShader);
	int drawAllModels();
	int bufferCrossHair(std::string path);
	int drawCrossHair();
	int getModelsSize();
	////////////INIT///////////
	void calculate();

	int initWindow();
	scene();
	virtual ~scene();
};

