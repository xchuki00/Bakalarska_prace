#include "Ground.h"



void Ground::setPlane(btCollisionObject *bt)
{
	this->plane = bt;
}

btCollisionObject * Ground::getPlane()
{
	return this->plane;
}

Ground::Ground()
{
	this->classID = GROUND;

}


Ground::~Ground()
{
}
