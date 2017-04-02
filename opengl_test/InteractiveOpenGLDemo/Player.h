#pragma once
#include "Model.h"
#include "Weapon.h"
class Player :
	public Model
{
protected:
	//glm::mat4 WeaponSlot;

	Weapon *w = NULL;
	bool landed = true;
public:
	void triggered();
	void fire(Projectil* load,btCollisionObject *obj);
	void Angles();
	void setWeapon(Weapon *ww);
	void calc();
	Weapon* getWeapon();
	glm::mat4 getPosition();
	Player();
	bool land();
	int hitted(Model* byWho);
	void jump();
	~Player();
};

