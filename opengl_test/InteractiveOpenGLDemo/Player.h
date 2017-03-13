#pragma once
#include "Model.h"
#include "Weapon.h"
class Player :
	public Model
{
protected:
	//glm::mat4 WeaponSlot;

	Weapon *w = NULL;
public:
	void triggered();
	void fire(Projectil* load,btCollisionObject *obj);
	void Angles();
	void setWeapon(Weapon *ww);
	void calc();
	Weapon* getWeapon();
	glm::mat4 getPosition();
	Player();
	~Player();
};

