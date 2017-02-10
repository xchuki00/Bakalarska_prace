#include "modelXbullet.h"



btCollisionObject * modelXbullet::getObj()
{
	return this->obj;
}

model * modelXbullet::getModel()
{
	return this->mod;
}

void modelXbullet::setModel(model * mod)
{
	this->mod = mod;
}

void modelXbullet::setObj(btCollisionObject* obj)
{
	this->obj = obj;
}

modelXbullet::modelXbullet()
{
}


modelXbullet::~modelXbullet()
{
}
