//#include "includes.h"
#pragma once
#include "loader.h"
#include "Shader.h"
#include "glm\ext.hpp"
#include "texture.h"
#include "controls.h"
#include "scene.h"
#include "misc.h"
using namespace glm;

//GLOBAL VARIABLES
Scene sc;

void loop() {	
	bool release = true;
	bool release2 = true;
	//glm::mat4 mat = glm::translate(getMyPosition(), glm::vec3(0, 2.0f, -1.0f));
	double pressT = glfwGetTime();
	double releaseT;
	do {
		sc.calculate();
		computeMatrices();
		
		if (glfwGetMouseButton(sc.window,GLFW_MOUSE_BUTTON_1)==GLFW_PRESS && release) {
			release = false;
			sc.player->triggered();
			//std::cerr << "PRDEL";
		}
		if (glfwGetMouseButton(sc.window, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE && !release) {
			//std::cerr << "PRDEL";
			release = true;
			Projectil *p = sc.player->getWeapon()->getProjectil();
			btCollisionObject *obj=sc.bulletWorld.addCollisionObject(p->getPosition(), glm::vec3(0, 0, 0), 1,p);
			p = (Projectil*)sc.addProjectil("./icons/arrow.obj", "./icons/bricks.bmp", 1);

			sc.player->fire(p,obj);
			
			std::cerr << "DIR" << glm::to_string((getDir() + glm::vec3(1, 1, 1)) / 2) << std::endl;
		}
		

		//sc.CalculatePositionOfAddicted();
			//prepocitava moji polohu
		sc.drawAllModels();
	} while (glfwGetKey(sc.window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(sc.window) == 0);

	
}
int main() {
	sc.initWindow();
	glm::mat4 mat = glm::mat4(1.0f);
	mat = glm::translate(mat, glm::vec3(5.0f, 8.0f, -5.0f));
	sc.addShader("simple.vertexshader","simple.fragmentshader");

	sc.addModel(GROUND, "./icons/ground.obj", "./icons/grass.jpg", glm::mat4(1.0f), glm::vec3(0, 0, 0), 0);
	sc.addModel(MODEL,"./icons/cube.obj","./icons/bricks.bmp",mat,glm::vec3(0,0,0),100);
	mat = glm::translate(mat, glm::vec3(-2.0f, 0.0f, 0.0f));
	sc.addModel(MODEL, "./icons/cube.obj", "./icons/bricks.bmp", mat, glm::vec3(0, 0, 0), 1);
	//sc.addModel(MODEL, "./icons/arrow.obj", "./icons/bricks.bmp",glm::translate(mat,glm::vec3(0,5,0)), glm::vec3(0, 0, 0), 100);

	sc.addCrossHair("./icons/crosshairs64.tga");
	sc.addSkybox(
		"./icons/left.tga",
		"./icons/front.tga",
		"./icons/right.tga",
		"./icons/back.tga",
		"./icons/top.tga",
		"./icons/bottom.tga"
	);
	Projectil *p = (Projectil*)sc.addProjectil("./icons/arrow.obj", "./icons/bricks.bmp", 5);
//	Projectil *p = NULL;
	Weapon *w = (Weapon*)sc.addWeapon("./icons/bow_final.dae", "./icons/bricks.bmp", p);
	sc.addPlayer("./icons/bullet.obj", "./icons/bricks.bmp", getMyPosition(), glm::vec3(0, 0, 0), w,1.7);
	//sc.addModel(PLAYER, "./icons/cube.obj", "./icons/bricks.bmp", getMyPosition(), glm::vec3(0, 0, 0), 3);
	//sc.addWeapon("./icons/bow_final2.dae", "./icons/bricks.bmp", (Player *)sc.addModel(PLAYER, "./icons/bullet.obj", "./icons/bricks.bmp", getMyPosition(), glm::vec3(0, 0, 0), 1.7));
	//std::cerr << "PLAYER" << sc.player->classID << std::endl;

	loop();
	mat = glm::rotate(mat, PI, glm::vec3(0, 1, 0));
	std::cerr << "PRVNI" << glm::to_string(mat) << std::endl;
	mat = glm::rotate(mat, PI, glm::vec3(1, 0, 0));
	std::cerr << "Druhga" << glm::to_string(mat) << std::endl;







	std::string s;
	std::cin >> s;
		

	return 0;
}
