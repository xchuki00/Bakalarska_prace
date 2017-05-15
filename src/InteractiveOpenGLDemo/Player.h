#pragma once
#include "Model.h"
#include "Weapon.h"
#include "Hud.h"
#include "ArrowStack.h"
#include "HitsHud.h"
class Player :
	public Model
{
protected:
	//glm::mat4 WeaponSlot;

	Weapon *w = NULL;
	bool landed = true;
	float hits=0.0;
	int arrows=6;
	ArrowStack* arrowStack=nullptr;
	HitsHud* hitsHud = nullptr;
public:
	int hasArrows();
	void addArrowStack(ArrowStack* as);
	void addHitsHud(HitsHud * hh);
	void triggered();
	void fire(Projectil* load,btCollisionObject *obj);
	void Angles();
	void setWeapon(Weapon *ww);
	void calc();
	void reportDmg(float f);
	Weapon* getWeapon();
	glm::mat4 getPosition();
	Player();
	bool land();
	int hitted(Model* byWho);
	void jump();
	~Player();
};

