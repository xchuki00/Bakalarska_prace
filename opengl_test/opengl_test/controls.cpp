#include "controls.h"
#include "scene.h"
extern scene sc;
glm::mat4 ViewC;
glm::mat4 ProjectionC;
glm::vec3 position(0, 0, 5);
glm::vec3 dirV;
glm::mat4 MyPosition(1.0f);
// horizontal angle : toward -Z
float hAngle = 3.14f;
// vertical angle : 0, look at the horizon
float vAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

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
glm::mat4 getMyPosition() {
	return MyPosition;
}
int computeMatrices()
{


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
	glm::vec3 upV=glm::cross(rightV,dirV);
	if (glfwGetKey(sc.window, GLFW_KEY_A) == GLFW_PRESS) {
		position -= rightV * delta*speed; //vektor posunu doprava, doba drzeni, rychlost
	}

	if (glfwGetKey(sc.window, GLFW_KEY_D) == GLFW_PRESS) {
		position += rightV * delta*speed; //vektor posunu doprava, doba drzeni, rychlost
	}

	if (glfwGetKey(sc.window, GLFW_KEY_W) == GLFW_PRESS) {
		position += dirV * delta*speed; //vektor posunu doprava, doba drzeni, rychlost
	}

	if (glfwGetKey(sc.window, GLFW_KEY_S) == GLFW_PRESS) {
		position -= dirV * delta*speed; //vektor posunu doprava, doba drzeni, rychlost
	}
	if (glfwGetKey(sc.window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		position += upV * delta*speed; //vektor posunu doprava, doba drzeni, rychlost
	}
	if (glfwGetKey(sc.window,GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		position -= upV * delta*speed; //vektor posunu doprava, doba drzeni, rychlost
	}
	float Fov = initialFoV;

	ProjectionC = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	ViewC = glm::lookAt(position, position+dirV,upV);
	lastT = current;
	MyPosition = glm::translate(glm::mat4(1.0f), position);
	return 0;
}

