#pragma once
#include "Model.h"
class Projectil :
	public Model
{
	double timeOfTriggered;
	Model* weapon;
	glm::mat4 oldOfTarget=glm::mat4(1.0f);
	bool firedAtr = false;
	bool inTargetAtr = false;
	int mass=1;
	glm::vec3 oldModel=glm::vec3(0,0,0);
	glm::vec3 translateVec;
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

