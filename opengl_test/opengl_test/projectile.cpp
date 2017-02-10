#include "projectile.h"



int projectile::hitted(model* byWho)
{
	if(this->dmgCoeficient==1){
		std::cerr << "PROJECTIL HITTEd" << std::endl;
		this->dmgCoeficient = 0;
	}
	return DESTROY;
}

void projectile::setDmgCoeficient(double coe)
{
	this->dmgCoeficient = coe;
}

double projectile::getDmg()
{

	return this->dmgCoeficient*glm::length(this->velocity);
}

projectile::projectile()
{
	this->classID = PROJECTIL;
}


projectile::~projectile()
{
}
