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
			if (sc.player->hasArrows()>0) {
				Projectil *p = sc.player->getWeapon()->getProjectil();
				btCollisionObject *obj = sc.bulletWorld.addCollisionObject(p->getPosition(), glm::vec3(0, 0, 0), 1, p);
				Projectil* p2 = (Projectil*)sc.addProjectil(OBJ+"arrow.obj", TEXT+"wood.jpg", 1);
				sc.player->fire(p2, obj);
			}
			else if (sc.player->hasArrows() == 0) {

				Projectil *p = sc.player->getWeapon()->getProjectil();
				btCollisionObject *obj = sc.bulletWorld.addCollisionObject(p->getPosition(), glm::vec3(0, 0, 0), 1, p);
				sc.player->fire(NULL, obj);
			}
			else {
				sc.player->fire(NULL, NULL);
			}
			//std::cerr << "DIR" << glm::to_string((getDir() + glm::vec3(1, 1, 1)) / 2) << std::endl;
		}
		

		//sc.CalculatePositionOfAddicted();
			//prepocitava moji polohu
		sc.drawAllModelToWindMap();
		sc.drawAllModelsToShadowMap();
		sc.drawAllModels();
	} while (glfwGetKey(sc.window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(sc.window) == 0);

	
}
int main() {
	sc.initWindow();
	glm::mat4 mat = glm::mat4(1.0f);
	mat = glm::translate(mat, glm::vec3(5.0f, 1.0f, -5.0f));
	sc.addShader("diffuseLight.vs","diffuseLight.fs");
	sc.addDepthShader("shadowMap.vs", "shadowMap.fs");
	sc.setHudShaders("crossHair.vertexShader", "crossHair.fragmentShader");
	sc.addWind(1,glm::vec3(0,-7,-10));
	sc.addDirectionLight(glm::vec3(1, 1, 1), glm::vec3(-10, -10, 0), 1, 1);
	sc.addDirectionLight(glm::vec3(1, 1, 1), glm::vec3(10, -10, 0), 1, 1);
	//sc.addDirectionLight(glm::vec3(1, 1, 1), glm::vec3(10, 0, 0), 1, 1);
	sc.addModel(GROUND, OBJ+"ground.obj", TEXT+"grass2.tga", glm::mat4(1.0f), glm::vec3(0, 0, 0), 0);
	mat = glm::rotate(mat, PI, glm::vec3(0, -1, 0));
	//sc.addModel(MODEL,"./icons/terc.obj","./icons/bricks.bmp",mat,glm::vec3(0,0,0),100);
	sc.addModel(MODEL,OBJ+"cube.obj",TEXT+"bricks.bmp",mat,glm::vec3(0,0,0),100);
	mat = glm::translate(mat, glm::vec3(-2.0f, 0.0f, -4.0f));
	//sc.addModel(MODEL, "./icons/terc.obj", "./icons/uvtemplate.tga", mat, glm::vec3(0, 0, 0), 10);
	sc.addModel(MODEL, OBJ+"cube.obj", OBJ+"uvtemplate.tga", mat, glm::vec3(0, 0, 0), 10);
	//sc.addModel(MODEL, "./icons/arrow.obj", "./icons/bricks.bmp",glm::translate(mat,glm::vec3(0,5,0)), glm::vec3(0, 0, 0), 100);
	sc.addHudElement(HUD,"crossHair",TEXT+"crosshairs64.tga",glm::vec4(WIDTH/2-50,HEIGHT/2+50,100,100),glm::vec4(5,0,8,8));
	sc.addHudElement(ARROWSTACK,"playerArrowStack",TEXT+"arow.tga",glm::vec4(100, 300, 240, 240),glm::vec4(0, 0, 1, 1));
	sc.addHudElement(HITSHUD, "playerHitsHud",TEXT+"ascii.tga", glm::vec4(WIDTH / 2 - 45, 1000, 30, 50), glm::vec4(0, 0,16, 16));
	sc.addHudElement(HITSHUD, "windHud", TEXT+"ascii.tga", glm::vec4(100, 1000, 30, 50), glm::vec4(0, 0, 16, 16));
	sc.addSkybox(
		TEXT + "skyboxes/day/left.tga",
		TEXT + "skyboxes/day/front.tga",
		TEXT + "skyboxes/day/right.tga",
		TEXT + "skyboxes/day/back.tga",
		TEXT + "skyboxes/day/top.tga",
		TEXT + "skyboxes/day/bottom.tga"
	);
	sc.addSunMoon(OBJ + "sun.obj", TEXT + "grass2.tga", -glm::pi<float>() / 8, dayLenght*3,40,-glm::pi<float>()/9,&sc.directionLights[0]);
	Projectil *p = (Projectil*)sc.addProjectil(OBJ+"arrow.obj", TEXT+"wood.tga", 5);
//	Projectil *p = NULL;
	Weapon *w = (Weapon*)sc.addWeapon(DAE+"bow_final2.dae", TEXT+"wood2.tga", p);
	sc.addPlayer(OBJ+"bullet.obj", TEXT+"bricks.bmp", getMyPosition(), glm::vec3(0, 0, 0), w,1.7);
	sc.player->addArrowStack((ArrowStack *)(sc.getHud("playerArrowStack")));
	sc.player->addHitsHud((HitsHud*)(sc.getHud("playerHitsHud")));
	sc.setWindHud((HitsHud*)(sc.getHud("windHud")));


	loop();
	return 0;
}
