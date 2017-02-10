#pragma once
#include "model.h"
class player :
	public model
{
	bool onground = true;
public:
	glm::mat4 getPosition();
	void draw();
	int hitted(model *byWho);
	void jump();
	bool landed();
	player();
	~player();
};

