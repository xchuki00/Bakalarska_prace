#pragma once
#include "model.h"
class projectile :
	public model
{
	double dmgCoeficient = 1;
public:
	int hitted(model *byWho);
	void setDmgCoeficient(double coe);
	double getDmg();
	projectile();
	~projectile();
};

