#pragma once
#include "model.h"
class target :
	public model
{
	int countOfHit = 0;
public:
	void hit(double dmg);
	int getCountOfHit();
	int hittted(model* byWho);
	target();
	~target();
};

