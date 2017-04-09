#pragma once
#include "includes.h"
#include "Hud.h"
class crossHair :
	public Hud
{

public:
	void print();
	void buffer();
	crossHair();
	virtual ~crossHair();
};

