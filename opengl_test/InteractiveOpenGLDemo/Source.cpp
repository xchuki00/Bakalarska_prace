//#include "includes.h"
#include "loader.h"
#include "Shader.h"
#include "glm\ext.hpp"
#include "texture.h"
#include "controls.h"
#include "scene.h"
#include "misc.h"

using namespace glm;

//GLOBAL VARIABLES
scene sc;

void loop() {	

	//sc.bufferModels();
	std::cerr << "buffer data ok" << std::endl;
	bool release=false;
	bool release2 = true;
	//glm::mat4 mat = glm::translate(getMyPosition(), glm::vec3(0, 2.0f, -1.0f));
	double pressT = glfwGetTime();
	double releaseT;
	do {

		//getworldtransform()
		sc.calculate();
		computeMatrices();//prepocitava moji polohu

		if (glfwGetKey(sc.window, GLFW_KEY_E) == GLFW_PRESS &&!release) {
			pressT = glfwGetTime();
			release = true;
		}
		//vypocitat matice pro aktu8lni snimek
		if (glfwGetKey(sc.window, GLFW_KEY_E) == GLFW_RELEASE&&release) {
			releaseT = glfwGetTime();
			release = false;
			double speed=3;
			if ((releaseT - pressT) < 5) {
				speed = (releaseT - pressT)*3;
			}
			glm::mat4 mat;
			mat4Copy(getMyPosition(), &mat);
			mat = glm::translate(mat, 3 * getDir());
			//mat = glm::translate(mat, getRight());
			mat4Rotate(&mat, getDir(),getUp());
			sc.addModel(PROJECTIL,"arrow.obj", "bricks.bmp",mat, speed*getDir(),10);
			sc.print();
			//printMat4(sc.models[sc.models.size() - 1].matrix);
		//	printMat4(getView());
			//vec3Copy(getDir(), sc.models[sc.models.size() - 1].direction);
		}

	

		sc.drawAllModels();
	} while (glfwGetKey(sc.window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(sc.window) == 0);


	
}
int main() {
	sc.initWindow();
	int k,h;
	glm::mat4 mat = glm::mat4(1.0f);
	sc.addShader("vertex.gls","fragment.gls");
	//sc.addShader("ShadowMapping.vertexshader", "ShadowMapping.fragmentshader");
	sc.addDepthShader("DepthRTT.vertexshader","DepthRTT.fragmentshader");
	sc.addSkybox(
		"left.tga",
		"front.tga",
		"right.tga",
		"back.tga",
		"top.tga",	
		"bottom.tga",
		"skybox.vertexShader",
		"skybox.fragmentShader"
	);
	sc.addGround("untitled.obj", "uvtemplate.tga");
	//sc.addModel();
	sc.addModel(TARGET,
		"cube.obj",
		"uvtemplate.tga",
		glm::translate(mat, glm::vec3(0.0f, 5.0f, -5.0f)),
		glm::vec3(0,0,0),
		50
	);
	sc.bufferCrossHair("crosshairs64.tga");
	//mat = glm::translate(mat, glm::vec3(-2.0f, 8.0f, 0.0f));
	//sc.addModel("tank.obj", "uvtemplate.tga", mat,glm::vec3(0.0f),100);

	mat = glm::translate(mat, glm::vec3(5.0f, 4.0f, 0.5f));
	sc.addModel(TARGET, "cube.obj", "red.bmp", mat, glm::vec3(0.0f, 0.0f, 0.0f),0);
	mat = glm::translate(mat, glm::vec3(4.0f, 5.0f, 0.0f));
	//sc.addModel(MODEL,"cube2.obj", "red.bmp", mat, glm::vec3(0.0f,0.0f,0.0f),100);
	mat = glm::mat4(1.0f);
	mat = glm::translate(mat, glm::vec3(0,2,0));
	//sc.addModel(MODEL,"cube2.obj", "bricks.bmp", getMyPosition(),glm::vec3(0.0f, 0.0f, 0.0f), 100);
	sc.addModel(PLAYER, "bullet.obj", "green.bmp", getMyPosition(), glm::vec3(0.0f), 10);
	sc.addModel(WEAPON, "bow.obj", "green.bmp",mat, glm::vec3(0.0f), 10);
//	sc.addModel(WEAPON, "bow_final.dae", "green.bmp", mat, glm::vec3(0.0f), 10);
	//sc.print();
	loop();
	
	return 1;
}
