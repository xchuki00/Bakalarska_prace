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
	double releaseT = true;
	int t = 0;
	int c = 0;
	int b = 0;
	int s = 0;
	do {
		sc.calculate();
		computeMatrices();
		
		if (glfwGetMouseButton(sc.window,GLFW_MOUSE_BUTTON_1)==GLFW_PRESS && release) {
			release = false;
			sc.player->triggered();
			////std::cerr << "PRDEL";
		}
		if (glfwGetMouseButton(sc.window, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE && !release) {
			////std::cerr << "PRDEL";
			release = true;
			if (sc.player->hasArrows()>0) {
				Projectil *p = sc.player->getWeapon()->getProjectil();
				btCollisionObject *obj = sc.bulletWorld.addCollisionObject(p->getPosition(), glm::vec3(0, 0, 0), 1, p);
				Projectil* p2 = (Projectil*)sc.addProjectil(OBJ+"arrow.obj", TEXT+"wood2.tga", 1);
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
			////std::cerr << "DIR" << glm::to_string((getDir() + glm::vec3(1, 1, 1)) / 2) << std::endl;
		}
		if (glfwGetKey(sc.window, GLFW_KEY_M) == GLFW_PRESS && releaseT) {
			releaseT = false;
			////std::cerr << "PRDEL";
		}
		if (glfwGetKey(sc.window, GLFW_KEY_M) == GLFW_RELEASE && !releaseT) {
			releaseT = true;
			//sc.addModel(MODEL, OBJ + "cube.obj", TEXT + "grass2.tga", glm::translate(glm::mat4(1.0f),glm::vec3(0,3,t)), glm::vec3(0, 0, 0), 5);
			t+=3;
		}
		if (c < 10 && glfwGetKey(sc.window, GLFW_KEY_C) == GLFW_PRESS) {
			sc.addModel(MODEL, OBJ + "tank.obj", TEXT + "bricks.bmp", glm::translate(glm::mat4(1.0f), glm::vec3(0, 5, 0)), glm::vec3(0, 0, 0), 5);
			c++;
		}
		if (s < 100 && glfwGetKey(sc.window, GLFW_KEY_P) == GLFW_PRESS) {
			sc.addModel(MODEL, OBJ + "sphere.obj", TEXT + "sun06.tga", glm::translate(glm::mat4(1.0f), glm::vec3(0, 5, 0)), glm::vec3(0, 0, 0), 5);
			s++;
		}
		if (b < 100 && glfwGetKey(sc.window, GLFW_KEY_B) == GLFW_PRESS) {
			sc.addModel(MODEL, OBJ + "100krychly/cube - kopie ("+std::to_string(b)+").obj", TEXT + "100krychly/bricks - kopie (" + std::to_string(b) + ").bmp", glm::translate(glm::mat4(1.0f), glm::vec3(0, 5, 0)), glm::vec3(0, 0, 0), 5);
			b++;
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
	glm::mat4 mat = glm::rotate(glm::mat4(1.0f),glm::pi<float>()/2, glm::vec3(0, 1, 0));
	mat = glm::translate(mat, glm::vec3(-10.0f, 1.0f, -5.0f));
	sc.addShader("./shaders/diffuseLight.vs", "./shaders/diffuseLight.fs");
	sc.addDepthShader("./shaders/shadowMap.vs", "./shaders/shadowMap.fs");
	sc.setHudShaders("./shaders/crossHair.vertexShader", "./shaders/crossHair.fragmentShader");
	sc.addWind(1, glm::vec3(0, -1, -10));
	sc.addDirectionLight(glm::vec3(1, 1, 1), glm::vec3(-10, -10, 0), 1, 1);
	sc.addDirectionLight(glm::vec3(1, 1, 1), glm::vec3(10, -10, 0), 1, 1);
	sc.addModel(GROUND, OBJ + "ground.obj", TEXT + "grass2.tga", glm::translate(glm::mat4(1.0f),glm::vec3(0,0,0)), glm::vec3(0, 0, 0), 0);
	mat = glm::rotate(mat, PI, glm::vec3(0, -1, 0));
	sc.addModel(MODEL, OBJ + "target.obj", TEXT + "bricks.bmp", mat, glm::vec3(0, 0, 0), 100);
	mat = glm::translate(mat, glm::vec3(-5.0f, 0.0f, -4.0f));
	sc.addModel(MODEL, OBJ + "target.obj", TEXT + "bricks.bmp", mat, glm::vec3(0, 0, 0), 100);
	mat = glm::translate(mat, glm::vec3(-15.0f, 5.0f, -4.0f));
	sc.addModel(MODEL, OBJ + "target.obj", TEXT + "bricks.bmp", mat, glm::vec3(0, 0, 0), 0);
	mat = glm::translate(mat, glm::vec3(+35, -5, +4));
	sc.addModel(MODEL, OBJ + "post.obj", TEXT + "wood2.tga", mat, glm::vec3(0, 0, 0), 100);
	mat = glm::translate(mat, glm::vec3(+10, 0, -8));
	sc.addModel(MODEL, OBJ + "post.obj", TEXT + "wood2.tga", mat, glm::vec3(0, 0, 0), 100);
	sc.addHudElement(HUD, "crossHair", TEXT + "crosshairs64.tga", glm::vec4(WIDTH / 2 - 50, HEIGHT / 2 + 50, 100, 100), glm::vec4(5, 0, 8, 8));
	sc.addHudElement(ARROWSTACK, "playerArrowStack", TEXT + "arow.tga", glm::vec4(100, 300, 240, 240), glm::vec4(0, 0, 1, 1));
	sc.addHudElement(HITSHUD, "playerHitsHud", TEXT + "ascii.tga", glm::vec4(WIDTH / 2 - 45, 1000, 30, 50), glm::vec4(0, 0, 16, 16));
	sc.addHudElement(HITSHUD, "windHud", TEXT + "ascii.tga", glm::vec4(100, 1000, 30, 50), glm::vec4(0, 0, 16, 16));
	sc.addHudElement(HITSHUD, "fps", TEXT + "ascii.tga", glm::vec4(WIDTH - 200, 1000, 30, 50), glm::vec4(0, 0, 16, 16));
	sc.addSkybox(
		TEXT + "skyboxes/day/left.tga",
		TEXT + "skyboxes/day/front.tga",
		TEXT + "skyboxes/day/right.tga",
		TEXT + "skyboxes/day/back.tga",
		TEXT + "skyboxes/day/top.tga",
		TEXT + "skyboxes/day/bottom.tga"
	);
	/*sc.addSkybox(
		TEXT + "skyboxes/day/blue.tga",
		TEXT + "skyboxes/day/blue.tga",
		TEXT + "skyboxes/day/blue.tga",
		TEXT + "skyboxes/day/blue.tga",
		TEXT + "skyboxes/day/blue.tga",
		TEXT + "skyboxes/day/blue.tga"
	);*/
	sc.addSunMoon(OBJ + "sun.obj", TEXT + "sun06.tga", -glm::pi<float>() / 4, dayLenght, 45, glm::pi<float>() / 9, &sc.directionLights[0]);
	sc.addSunMoon(OBJ + "moon.obj", TEXT + "moon_texture.tga", 3*glm::pi<float>() / 4, dayLenght, 45, glm::pi<float>() / 9, NULL);
	Projectil *p = (Projectil*)sc.addProjectil(OBJ + "arrow.obj", TEXT + "wood2.tga", 5);
	//	Projectil *p = NULL;
	Weapon *w = (Weapon*)sc.addWeapon(DAE + "bow_final2.dae", TEXT + "wood2.tga", p);
	sc.addPlayer(OBJ + "bullet.obj", TEXT + "bricks.bmp", getMyPosition(), glm::vec3(0, 0, 0), w, 1.7);
	sc.player->addArrowStack((ArrowStack *)(sc.getHud("playerArrowStack")));
	sc.player->addHitsHud((HitsHud*)(sc.getHud("playerHitsHud")));
	sc.setWindHud((HitsHud*)(sc.getHud("windHud")));


	loop();
	std::string x;
	return 0;
}
