#pragma once
#include "Model.h"
class Ground :
	public Model
{
	btCollisionObject *plane;
public:
	void setPlane(btCollisionObject *bt);
	btCollisionObject* getPlane();
	Ground();
	~Ground();
};

