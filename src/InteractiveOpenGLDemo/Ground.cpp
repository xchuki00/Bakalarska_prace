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
	return this->modelMatrix;
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
