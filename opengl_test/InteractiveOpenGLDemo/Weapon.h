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
public:
	void triggered();
	Model* getPlayer();
	void setPlayer(Model* p);
	void init(Projectil* p);
	void reload(Projectil *p);
	void fire(Projectil* load, btCollisionObject *obj);
	void calc();
	glm::mat4 getPosition();
	Projectil* getProjectil();
	Weapon();
	~Weapon();
};

