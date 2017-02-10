#include "target.h"
#include "projectile.h"


void target::hit(double dmg)
{
	this->countOfHit+=dmg;
}

int target::getCountOfHit()
{
	return this->countOfHit;
}

int target::hittted(model* byWho)
{
	if (byWho->classID != GROUND) {
		if (this->getCountOfHit() == 0) {
			this->textur = loadTexture2d("red.bmp", &this->textureHeight, &this->textureWidth);
			std::cerr << this->getCountOfHit() << std::endl;
		}

		this->hit(byWho->getDmg()+1);
	}
	if (this->getCountOfHit() > 1) {
		return DESTROY
	}
	return NOTHING;
}

target::target()
{
	this->classID = 4;
}


target::~target()
{
}
