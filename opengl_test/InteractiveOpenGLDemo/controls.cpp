#pragma once
#include "controls.h"
#include "scene.h"
#include "misc.h"
extern Scene sc;
glm::mat4 ViewC;
glm::mat4 ProjectionC;
glm::vec3 position(0, 1.0f, 2.0f);
glm::vec3 dirV(0,0,0.5f);
glm::mat4 MyPosition = glm::translate(glm::mat4(1.0f), position);
glm::vec3 upV(0, 1, 0);
glm::vec3 force(0, 0, 0);
glm::vec3 rightV(1, 0, 0);
// horizontal angle : toward -Z
float hAngle = PI;
float oldHAngle = PI;
// vertical angle : 0, look at the horizon
float vAngle = 0.0f;
float oldVAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;
bool space = true;
float speed = 2.0f; // 3 units / second
float mouseSpeed = 0.005f;

glm::mat4 getProject() {
	return ProjectionC;
}

glm::mat4 getView() {
	return ViewC;
}
glm::vec3 getDir() {
	return glm::normalize(dirV);
}
glm::vec3 getUp() {
	return glm::normalize(upV);
}
glm::mat4 getMyPosition() {
	return MyPosition;
}
glm::vec3 getVectorOfPosition() {
	return position;
}
void setMyPosition(glm::vec3 pos)
{
	position = pos;
}
glm::vec3 getRight() {
	return glm::normalize(rightV);
}
float getVAngle() {
	return vAngle;
}
float getHAngle() {
	return hAngle;
}
glm::vec3 getChange() {
	return force;
}
int computeMatrices()
{
	//std::cerr << glm::to_string(position) << std::endl;
	glm::vec3 oldPos;
	vec3Copy(position, &oldPos);
	static double lastT = glfwGetTime();
	double current = glfwGetTime();
	double delta = double(current - lastT); // doba od posledn9 prepo4itani

	double x, y;
	glfwGetCursorPos(sc.window, &x, &y);
	glfwSetCursorPos(sc.window,WIDTH / 2, HEIGHT / 2);

	//smery posunu z aktualni pozice
	hAngle += mouseSpeed * float(WIDTH / 2 - x);
	vAngle += mouseSpeed * float(HEIGHT / 2 - y);

	dirV=glm::vec3(cos(vAngle)*sin(hAngle),sin(vAngle), cos(vAngle)*cos(hAngle));
	rightV=glm::vec3(sin(hAngle-3.14f/2.0f),0,cos(hAngle - 3.14f / 2.0f));
	upV=glm::cross(rightV,dirV);
	static bool pressAD=false;
	static bool pressW = false;
	static bool pressS = false;
	if (glfwGetKey(sc.window, GLFW_KEY_A) == GLFW_PRESS) {
		pressAD = true;
		std::cerr << "SA";
		position -= glm::vec3(rightV.x,0,rightV.z) * delta*speed; //vektor posunu doprava, doba drzeni, rychlost
	}

	if (glfwGetKey(sc.window, GLFW_KEY_D) == GLFW_PRESS) {
		pressAD = true;
		position += glm::vec3(rightV.x, 0, rightV.z) * delta*speed; //vektor posunu doprava, doba drzeni, rychlost
	}

	if (glfwGetKey(sc.window, GLFW_KEY_W) == GLFW_PRESS) {
		pressW = true;

		position += glm::vec3(dirV.x,0,dirV.z) * delta*speed*1.25; //vektor posunu doprava, doba drzeni, rychlost
	}

	if (glfwGetKey(sc.window, GLFW_KEY_S) == GLFW_PRESS) {
		pressS = true;
		position -= glm::vec3(dirV.x, 0, dirV.z) * delta*speed*0.75; //vektor posunu doprava, doba drzeni, rychlost
	}
	
	if (glfwGetKey(sc.window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
		space = true;
		
	}
	if (glfwGetKey(sc.window, GLFW_KEY_SPACE) == GLFW_PRESS) {

		//std::cerr << sc.Player->classID << " PRDE\n";
		//sc.player->jump();
		space = false;
		position += glm::vec3(0,1,0) * 0.1* speed; //vektor posunu doprava, doba drzeni, rychlost
	}
	if (glfwGetKey(sc.window,GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		position -= glm::vec3(0, 1, 0) * delta*speed; //vektor posunu doprava, doba drzeni, rychlost
	}
	float Fov = initialFoV;
	force.x=position.x - oldPos.x;
	force.y = position.y - oldPos.y;
	force.z= position.z - oldPos.z;
	if (pressAD && (pressW || pressS)) {
	//	force.x *= 0.5;
		//force.z *= 0.5;
	}

	pressAD = false;
	pressS = false;
	pressW = false;
	btCollisionObject *pl = sc.player->getObj();
	btRigidBody *rb = btRigidBody::upcast(pl);
	rb->clearForces();
	rb->applyCentralForce(btVector3(70*force.x, 1000*force.y,70*force.z));
	rb->activate();
	btTransform t;
	rb->getMotionState()->getWorldTransform(t);
	glm::mat4 mat;
	t.getOpenGLMatrix(glm::value_ptr(mat));
	position.x = mat[3][0];
	position.y = mat[3][1];
	position.z = mat[3][2];
	MyPosition = glm::translate(glm::mat4(1.0f), position);
	//std::cerr << "FORCE" << glm::to_string(position) <<"\n"<<glm::to_string(oldPos)<< std::endl;
	ProjectionC = glm::perspective(Fov, 4.0f / 3.0f, 0.1f, 100.0f);
	ViewC = glm::lookAt(position, position+dirV,upV);
	lastT = current;

	return 0;
}

