#pragma once
#include "Model.h"
class Projectil :
	public Model
{
	double timeOfTriggered;
	Model* weapon;
	glm::mat4 oldOfTarget;
	bool firedAtr = false;
	bool inTargetAtr = false;
	int mass=1;
public:
	void setMass(int m);
	void setWeapon(Model *w);
	Projectil();
	~Projectil();
	glm::mat4 getPosition();
	int init();
	void triggered();
	int fire(btCollisionObject *obj); // uvolni projektil ze zbrane
	bool fired();
	bool inTarget();
	int hitted(Model* byWho);
};

