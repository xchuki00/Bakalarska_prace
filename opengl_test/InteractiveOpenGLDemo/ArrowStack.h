#pragma once
#include "Hud.h"
class ArrowStack :
	public Hud
{
	int countOfArrow = 6;

public:
	void buffer();
	void minus();
	void setCountOfArrows(int count);
	int getCountofArrows();
	ArrowStack();
	~ArrowStack();
};

