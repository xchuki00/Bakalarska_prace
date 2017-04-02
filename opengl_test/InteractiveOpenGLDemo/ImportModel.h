#pragma once
#include "includes.h"
#include "structures.h"
#include "animation.h"
class ImportModel
{
	std::vector<MyVertex> vertices;
	std::vector<unsigned short> indices;
	animation * Animation=nullptr;
public:
	std::vector<MyVertex> getVertices();
	std::vector<unsigned short> getIndices();
	bool hasAnimation();
	animation* getAnimation();

	ImportModel(std::string path);
	virtual ~ImportModel();
};

