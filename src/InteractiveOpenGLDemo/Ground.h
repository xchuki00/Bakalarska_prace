#pragma once
#include "Model.h"
class Ground :
	public Model
{
	btCollisionObject *plane;
public:
	void setPlane(btCollisionObject *bt);
	btCollisionObject* getPlane();
	glm::mat4 getPosition();
	float getDmg();
	Ground();
	~Ground();
};

