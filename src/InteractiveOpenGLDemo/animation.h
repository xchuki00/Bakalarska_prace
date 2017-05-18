#pragma once
#include "includes.h"
#include "structures.h"
class animation
{
public:
	aiMatrix4x4 inverseGlobalMartix;
	std::vector<bone> bones;
	std::map<std::string, unsigned int> bonesMap;

	Assimp::Importer *imp;
	const aiNode* nodes = nullptr;
	const aiAnimation* animations = nullptr;


	virtual void updateNode(const aiNode* Node, aiMatrix4x4 ParentTransform, double time);
	virtual const aiNodeAnim* findAnimNode(const aiAnimation *anim, std::string nodeName);
	virtual void getNodeRotation(aiQuaternion* vec, double time, const aiNodeAnim* animNode);
	virtual void getNodeScale(aiVector3D* vec, double time, const aiNodeAnim* animNode);
	virtual void getNodePosition(aiVector3D* vec, double time, const aiNodeAnim* animNode);
	void setRootNode(const aiNode *node);
	void setAnimation(const aiAnimation* anim);
	double getDuration();
	double getTickPerSecond();
	animation();
	virtual ~animation();
};

