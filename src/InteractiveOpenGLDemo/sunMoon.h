#pragma once
#include "Model.h"
class SunMoon :
	public Model
{
	float offset = 0;
	float period = 0;
	DirectionLight* light =NULL;
	double* time;
	float lastTime = 0;
	glm::vec3 axis;
	glm::vec3 transalteVec;
public:
	glm::mat4 getPosition();
	void draw(std::vector<DirectionLight> lights);
	void setOffset(float o);
	void setPeriod(float p);
	void setLightSource(DirectionLight* l);
	void setRefToTime(double* timeI);
	void setCircle(float r, float angle);
	SunMoon();
	virtual~SunMoon();
};

