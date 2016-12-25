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
	int addModel(std::string pathOfObj, std::string pathOfTexture);
	int addModel(std::string pathOfObj, std::string pathOfTexture, glm::mat4 position);
	int addModel(
		std::string pathOfObj,
		std::string pathOfTexture, 
		glm::mat4 position,
		GLfloat speed,
		glm::vec3 direction,
		btCollisionShape *shape,
		float mass
	);
	int removeModel(int id);
	int addShader(std::string vertexShader, std::string fragmentShader);
	int bufferModels();
	int drawAllModels();
	int bufferCrossHair(std::string path);
	int drawCrossHair();
	
	////////////INIT///////////
	void calculate();
	void initCrossHair();
	int initWindow();
	scene();
	virtual ~scene();
};

