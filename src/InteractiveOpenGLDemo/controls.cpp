#pragma once
#include "controls.h"
#include "scene.h"
#include "misc.h"
#include <limits>
extern Scene sc;
glm::mat4 ViewC;
glm::mat4 ProjectionC;
glm::vec3 position(10, 2.0f, 5.0f);
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
float initialFoV = glm::half_pi<float>()/2;
bool space = true;
float speed = 2.0f; // 3 units / second
float mouseSpeed = 0.005f;

glm::mat4 getProject() {
	return ProjectionC;
}

glm::mat4 getOrthoProject(glm::vec3 dir)
{
	float l = std::numeric_limits<float>::infinity();
	float r = -l;
	float b = std::numeric_limits<float>::infinity();
	float t = -b;
	float n = -1000;
	float f = 1000;
	glm::mat4 iVP = getOrthoView(dir)*glm::inverse(getProject() *getView());
	for (int i = 0; i < 8; i++) {
		glm::vec4 v;
		for (int j = 0; j < 3; j++) {
			v[j] = (-1.f + 2.f*((i >> j) & 1));
		}
		v[3] = 1.0f;
		v = iVP*v;
		v.x /= v.w;
		v.y /= v.w;
		l = glm::min(l, v.x);
		r = glm::max(r, v.x);
		b = glm::min(b, v.y);
		t = glm::max(t, v.y);
		n = glm::min(n, v.z);
		f = glm::max(f, v.z);
	}
	return glm::ortho(l, r, b, t, n, f);
}

glm::mat4 getView() {

	return ViewC;
}
glm::mat4 getOrthoView(glm::vec3 dir)
{

	glm::vec3 pos = glm::vec3(0, 0, 0);
	glm::vec3 up = glm::vec3(0, 1, 0);
	return glm::lookAt(pos,dir,up);
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
	////std::cerr << glm::to_string(position) << std::endl;
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
	if (glfwGetKey(sc.window, GLFW_KEY_SPACE) == GLFW_PRESS&&sc.player->land()&&space) {
		space = false;
		sc.player->jump();
		position += glm::vec3(0,1,0) *0.3* speed; 
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
	rb->applyCentralForce(btVector3(70*force.x, 100*force.y,70*force.z));
	rb->activate();
	btTransform t;
	rb->getMotionState()->getWorldTransform(t);
	glm::mat4 mat;
	t.getOpenGLMatrix(glm::value_ptr(mat));
	position.x = mat[3][0];
	position.y = mat[3][1];
	position.z = mat[3][2];
	MyPosition = glm::translate(glm::mat4(1.0f), position);
	////std::cerr << "FORCE" << glm::to_string(position) <<"\n"<<glm::to_string(oldPos)<< std::endl;
	ProjectionC = glm::perspective(Fov, 4.0f / 3.0f, 0.1f, 100.0f);
	ViewC = glm::lookAt(position, position+dirV,upV);
	lastT = current;
	sc.addToWindDirection(getDir(), 0);
	////////////////wind////////////
	///strenght
	if (glfwGetKey(sc.window, GLFW_KEY_L) == GLFW_PRESS) {
		sc.addToWindStrength(delta); //vektor posunu doprava, doba drzeni, rychlost
	}
	if (glfwGetKey(sc.window, GLFW_KEY_K) == GLFW_PRESS) {
		sc.addToWindStrength(-delta); //vektor posunu doprava, doba drzeni, rychlost
	}
	///direction
	if (glfwGetKey(sc.window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		sc.addToWindDirection(glm::vec3(0,1,0),-delta); //vektor posunu doprava, doba drzeni, rychlost
	}
	if (glfwGetKey(sc.window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		sc.addToWindDirection(glm::vec3(0, 1, 0), delta); //vektor posunu doprava, doba drzeni, rychlost
	}
	return 0;
}

