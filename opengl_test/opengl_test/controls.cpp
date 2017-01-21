#include "controls.h"
#include "scene.h"
#include "misc.h"
extern scene sc;
glm::mat4 ViewC;
glm::mat4 ProjectionC;
glm::vec3 position(0, 1, 5);
glm::vec3 dirV;
glm::mat4 MyPosition(1.0f);
glm::vec3 upV(0, 1, 0);
// horizontal angle : toward -Z
float hAngle = 3.14f;
// vertical angle : 0, look at the horizon
float vAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;
bool space = true;
float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.005f;
glm::mat4 getProject() {
	return ProjectionC;
}

glm::mat4 getView() {
	return ViewC;
}
glm::vec3 getDir() {
	return dirV;
}
glm::vec3 getUp() {
	return upV;
}
glm::mat4 getMyPosition() {
	return MyPosition;
}
void setMyPosition(glm::vec3 pos)
{
	position = pos;
}
int computeMatrices()
{

	glm::vec3 oldPos;
	vec3Copy(position, &oldPos);
	static double lastT = glfwGetTime();
	double current = glfwGetTime();
	double delta = double(current - lastT); // doba od posledn9 prepo4itani

	double x, y;
	glfwGetCursorPos(sc.window, &x, &y);
	glfwSetCursorPos(sc.window,HEIGHT / 2, WIDTH / 2);

	//smery posunu z aktualni pozice
	hAngle += mouseSpeed * float(HEIGHT / 2 - x);
	vAngle += mouseSpeed * float(WIDTH / 2 - y);

	dirV=glm::vec3(cos(vAngle)*sin(hAngle),sin(vAngle), cos(vAngle)*cos(hAngle));
	glm::vec3 rightV(sin(hAngle-3.14f/2.0f),0,cos(hAngle - 3.14f / 2.0f));
	upV=glm::cross(rightV,dirV);
	bool pressAD=false;
	bool pressW = false;
	bool pressS = false;
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
	if (glfwGetKey(sc.window, GLFW_KEY_SPACE) == GLFW_PRESS&&space&&sc.Player->landed()) {

		std::cerr << sc.Player->classID << " PRDE\n";
		sc.Player->jump();
		space = false;
		position += glm::vec3(0,1,0) * 0.1* speed; //vektor posunu doprava, doba drzeni, rychlost
	}
	if (glfwGetKey(sc.window,GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		position -= glm::vec3(0, 1, 0) * delta*speed; //vektor posunu doprava, doba drzeni, rychlost
	}
	float Fov = initialFoV;
	glm::vec3 force=position - oldPos;
	if (pressAD && pressW) {
		force.x *= 0.77;
		force.z *= 0.77;
	}
	if (pressAD && pressS) {
		force.x *= 0.77;
		force.y *= 0.77;
	}
	pressAD = false;
	pressS = false;
	pressW = false;
	btCollisionObject *pl=sc.modelsXbullets.data()[sc.Player->getRigidBodyIndex()]->getObj();
	btRigidBody *rb = btRigidBody::upcast(pl);
	rb->clearForces();
	//force=glm::normalize(force);
	//std::cerr << "GLM"<<glm::to_string(force) << "\n";
	rb->applyCentralForce(btVector3(70*force.x, 1000*force.y,70*force.z));
	btVector3 f= rb->getTotalForce();
	//std::cerr << "BULLET" << f.x() << "  " << f.y() << "  " << f.z() << std::endl;
	rb->activate();
	btTransform t;
	rb->getMotionState()->getWorldTransform(t);
	glm::mat4 mat;
	t.getOpenGLMatrix(glm::value_ptr(mat));
	position.x = mat[3][0];
	position.y = mat[3][1];
	position.z = mat[3][2];
	//std::cerr << "FORCE" << glm::to_string(position) <<"\n"<<glm::to_string(oldPos)<< std::endl;
	ProjectionC = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	ViewC = glm::lookAt(position, position+dirV,upV);
	lastT = current;
	MyPosition = glm::translate(glm::mat4(1.0f), position);
	return 0;
}

