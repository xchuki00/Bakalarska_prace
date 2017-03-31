#pragma once
#include "Model.h"
#include "misc.h"
#include "Projectil.h"
class Weapon :
	public Model
{
	
	Model* player;
	Projectil *p = NULL;
	void Angles();
	double triggeredTime=0;
	Projectil* toLoad = NULL;
	glm::vec3 shift=glm::vec3(0.0f);
public:
	void triggered();
	Model* getPlayer();
	void setPlayer(Model* p);
	void init(Projectil* p);
	void reload(Projectil *p);
	void fire(Projectil* load, btCollisionObject *obj);
	void calc();
	double getTime();

	glm::mat4 getPosition();
	Projectil* getProjectil();
	Weapon();
	~Weapon();
};

