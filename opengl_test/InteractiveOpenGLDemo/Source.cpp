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
	bool release = false;
	bool release2 = true;
	//glm::mat4 mat = glm::translate(getMyPosition(), glm::vec3(0, 2.0f, -1.0f));
	double pressT = glfwGetTime();
	double releaseT;
	do {
		if (glfwGetKey(sc.window,GLFW_MOUSE_BUTTON_1)==GLFW_PRESS) {

		}

		//getworldtransform()
		sc.calculate();
		computeMatrices();//prepocitava moji polohu
		sc.drawAllModels();
	} while (glfwGetKey(sc.window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(sc.window) == 0);

	
}
int main() {
	sc.initWindow();
	glm::mat4 mat = glm::mat4(1.0f);
	mat = glm::translate(mat, glm::vec3(1.0f, 8.0f, -1.0f));
	sc.addShader("simple.vertexshader","simple.fragmentshader");

	sc.addModel(GROUND, "./icons/hill.obj", "./icons/grass.jpg", glm::mat4(1.0f), glm::vec3(0, 0, 0), 0);
	sc.addModel(MODEL,"./icons/cube.obj","./icons/bricks.bmp",mat,glm::vec3(0,0,0),100);
	sc.addCrossHair("./icons/crosshairs64.tga");
	sc.addSkybox(
		"./icons/left.tga",
		"./icons/front.tga",
		"./icons/right.tga",
		"./icons/back.tga",
		"./icons/top.tga",
		"./icons/bottom.tga"
	);
	sc.addModel(PLAYER, "./icons/cube.obj", "./icons/bricks.bmp", getMyPosition(), glm::vec3(0, 0, 0), 1);
	/*
	Model * m = new Model();
	Target *t = new Target();
	m->draw();
	t->draw();
	std::vector<Model *> ms;
	ms.push_back(m);
	ms.push_back(t);
	for (int i = 0; i < ms.size(); i++) {
		ms[i]->draw();
	}*/

	loop();
	return 1;
}
