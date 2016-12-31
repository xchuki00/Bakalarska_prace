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
	bool release=true;
	bool release2 = true;
	//glm::mat4 mat = glm::translate(getMyPosition(), glm::vec3(0, 2.0f, -1.0f));
	
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (glfwGetKey(sc.window, GLFW_KEY_E) == GLFW_RELEASE) {
			release = true;
		}

		//vypocitat matice pro aktu8lni snimek
		if (glfwGetKey(sc.window, GLFW_KEY_E) == GLFW_PRESS&&release) {

			release = false;
			sc.addModel("bullet.obj", "bricks.bmp",getMyPosition(), 10*getDir(),10);
			//sc.addModel(mod, 10);
			
			//printMat4(sc.models[sc.models.size() - 1].matrix);
		//	printMat4(getView());
			//vec3Copy(getDir(), sc.models[sc.models.size() - 1].direction);
		}

	

		//getworldtransform()
		sc.calculate();
		computeMatrices();//prepocitava moji polohu
		sc.drawGround();
		std::cerr << "dadwa\n";
		sc.drawSkybox();
		sc.drawAllModels();
		sc.drawCrossHair();
		glfwSwapBuffers(sc.window);
		glfwPollEvents();


	} while (glfwGetKey(sc.window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(sc.window) == 0);


	
}
int main() {
	sc.initWindow();
	int k,h;
	glm::mat4 mat = glm::mat4(1.0f);
	sc.addShader("vertex.gls", "fragment.gls");
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
	sc.addGround("untitled.obj", "bricks.bmp");
	//sc.addModel();
	sc.addModel(
		"cube.obj",
		"uvtemplate.tga",
		glm::translate(mat, glm::vec3(0.0f, 5.0f, -5.0f)),
		glm::vec3(0,0,0),
		0
	);
	sc.bufferCrossHair("crosshairs64.tga");
	mat = glm::translate(mat, glm::vec3(-2.0f, 8.0f, 0.0f));
	//sc.addModel("tank.obj", "uvtemplate.tga", mat,glm::vec3(0.0f),100);
	mat = glm::translate(mat, glm::vec3(4.0f, 5.0f, 0.0f));
	sc.addModel("cube2.obj", "red.bmp", mat, glm::vec3(0.0f,0.0f,0.0f),100);
	mat = glm::translate(mat, glm::vec3(6.0f, 0.0f, -4.0f));
	sc.addPlayer("cube2.obj", "bricks.bmp", getMyPosition(),glm::vec3(0.0f, 0.0f, 0.0f), 100);

	
	//sc.print();
	loop();
	
	return 1;
}
