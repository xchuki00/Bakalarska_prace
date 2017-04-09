#pragma once
#include "Hud.h"
class HitsHud :
	public Hud
{
	std::string prefix = "";
	std::string postfix = "";
	std::string contains = "5.0";
public:
	void setPrefix(std::string s);
	void setPostFix(std::string s);
	void setContains(int i);
	void setContains(float f);
	void setContains(std::string s);
	void setContains(char c);
	void buffer();
	HitsHud();
	~HitsHud();
};

