#pragma once
#include "bulletC.h"
#include "model.h"
class modelXbullet
{
	model *mod=NULL;
	btCollisionObject *obj=NULL;
public:
	btCollisionObject * getObj();
	model * getModel();
	void setModel(model* mod);
	void setObj(btCollisionObject* obj);
	modelXbullet();
	~modelXbullet();
};

