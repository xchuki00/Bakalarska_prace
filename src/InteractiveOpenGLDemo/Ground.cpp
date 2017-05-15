#include "Ground.h"



void Ground::setPlane(btCollisionObject *bt)
{
	this->plane = bt;
}

btCollisionObject * Ground::getPlane()
{
	return this->plane;
}

glm::mat4 Ground::getPosition()
{
	return glm::translate(this->modelMatrix, glm::vec3(0,0.1,0));
}

float Ground::getDmg()
{
	return 0.0f;
}

Ground::Ground()
{
	this->classID = GROUND;

}


Ground::~Ground()
{
}
