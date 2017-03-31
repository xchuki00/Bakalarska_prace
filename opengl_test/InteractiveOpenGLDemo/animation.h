#pragma once
#include "includes.h"
#include "structures.h"
class animation
{
	aiMatrix4x4 inverseGlobalMartix;
	std::vector<bone> bones;
	std::vector<aiMatrix4x4> finalTransform;
	std::map<std::string, unsigned int> bonesMap;
	GLuint BonesID;
	Assimp::Importer *imp;
	const aiNode* nodes = nullptr;
	const aiAnimation* animations = nullptr;
	virtual void updateNode(const aiNode* Node, aiMatrix4x4 ParentTransform, double time);
	virtual const aiNodeAnim* findAnimNode(const aiAnimation *anim, std::string nodeName);
	virtual void getNodeRotation(aiQuaternion* vec, double time, const aiNodeAnim* animNode);
	virtual void getNodeScale(aiVector3D* vec, double time, const aiNodeAnim* animNode);
	virtual void getNodePosition(aiVector3D* vec, double time, const aiNodeAnim* animNode);

public:
	animation();
	~animation();
};

