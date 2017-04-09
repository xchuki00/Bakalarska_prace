#include "animation.h"
#include "misc.h"


animation::animation()
{

	this->imp = new Assimp::Importer();
}


animation::~animation()
{
	delete this->imp;
}
void animation::updateNode(const aiNode * Node, aiMatrix4x4 ParentTransform, double time)
{
	std::string NodeName(Node->mName.data);
	const aiAnimation* pAnimation = this->animations;
	aiMatrix4x4 NodeTransformation = aiMatrix4x4(Node->mTransformation);
	const aiNodeAnim* pNodeAnim = this->findAnimNode(pAnimation, NodeName);


	if (pNodeAnim != nullptr) {

		aiVector3D Scaling;
		this->getNodeScale(&Scaling, time, pNodeAnim);
		aiMatrix4x4 scaleM = aiMatrix4x4();
		scaleM.Scaling(Scaling, scaleM);

		aiQuaternion RotationQ;
		this->getNodeRotation(&RotationQ, time, pNodeAnim);
		aiMatrix4x4 rotateM = aiMatrix4x4(RotationQ.GetMatrix());

		aiVector3D Translation;
		this->getNodePosition(&Translation, time, pNodeAnim);
		aiMatrix4x4 TransM = aiMatrix4x4();
		TransM.Translation(Translation, TransM);
		//std::cerr << "SCALE" << Scaling.x<<"," << Scaling.y << "," << Scaling.z << "\n";
		//std::cerr << "ROTATE" << RotationQ.x << "," << RotationQ.y << "," << RotationQ.z <<"," << RotationQ.w << "\n";
		//std::cerr << "TRANS" << Translation.x << "," << Translation.y << "," << Translation.z << "\n";

		NodeTransformation = TransM*rotateM*scaleM;
	}
	aiMatrix4x4 GlobalTransformation = ParentTransform * NodeTransformation;

	if (this->bonesMap.find(NodeName) != this->bonesMap.end()) {
		unsigned int BoneIndex = this->bonesMap[NodeName];
		this->bones[BoneIndex].matrix = this->inverseGlobalMartix * GlobalTransformation*this->bones[BoneIndex].offset;
	}
	for (unsigned int i = 0; i < Node->mNumChildren; i++) {
		this->updateNode(Node->mChildren[i], GlobalTransformation, time);
	}
}

const aiNodeAnim * animation::findAnimNode(const aiAnimation * anim, std::string nodeName)
{
	for (int i = 0; i < anim->mNumChannels; i++) {
		if (anim->mChannels[i]->mNodeName.data == nodeName) {
			return anim->mChannels[i];
		}
	}
	return nullptr;
}

void animation::getNodeRotation(aiQuaternion* vec, double time, const aiNodeAnim * animNode)
{
	int j = animNode->mNumRotationKeys - 1;
	
	if (time < animNode->mRotationKeys[0].mTime) {
		j = 0;
	}
	else {
		for (int i = 0; i < animNode->mNumRotationKeys - 1; i++) {
			if (animNode->mRotationKeys[i + 1].mTime == time) {
				j = i;
				break;
			}
			if (animNode->mRotationKeys[i + 1].mTime > time)
			{
				float deltaT = (float)(animNode->mRotationKeys[i + 1].mTime - animNode->mRotationKeys[i].mTime);
				float factor = (float)((time - animNode->mRotationKeys[i].mTime) / deltaT);

				aiQuaternion::Interpolate((*vec), animNode->mRotationKeys[i].mValue, animNode->mRotationKeys[i+1].mValue, factor);
				(*vec) = (*vec).Normalize();
				return;
			}
		}
	}
	(*vec).x = animNode->mRotationKeys[j].mValue.x;
	(*vec).y = animNode->mRotationKeys[j].mValue.y;
	(*vec).z = animNode->mRotationKeys[j].mValue.z;
	(*vec).w = animNode->mRotationKeys[j].mValue.w;
	return;
}

void animation::getNodeScale(aiVector3D* vec, double time, const aiNodeAnim * animNode)
{
	int j = animNode->mNumScalingKeys - 1;
	if (time < animNode->mScalingKeys[0].mTime) {
		j = 0;
	}
	else {
		for (int i = 0; i < animNode->mNumScalingKeys - 1; i++) {
			if (animNode->mScalingKeys[i + 1].mTime == time) {
				j = i;
				break;
			}
			if (animNode->mScalingKeys[i + 1].mTime > time)
			{
				float deltaT = animNode->mScalingKeys[1 + i].mTime - animNode->mScalingKeys[i].mTime;
				float factor = (time - animNode->mScalingKeys[i].mTime) / deltaT;
				aiVector3D delta = animNode->mScalingKeys[i+1].mValue - animNode->mScalingKeys[i].mValue;
				aiVector3D out = animNode->mScalingKeys[i].mValue + factor * delta;
				(*vec).x = out.x;
				(*vec).y = out.y;
				(*vec).z = out.z;
				return;
			}
		}
	}
	(*vec).x = animNode->mScalingKeys[j].mValue.x;
	(*vec).y = animNode->mScalingKeys[j].mValue.y;
	(*vec).z = animNode->mScalingKeys[j].mValue.z;
	return;
}

void animation::getNodePosition(aiVector3D* vec, double time, const aiNodeAnim * animNode)
{
	int j = animNode->mNumPositionKeys - 1;
	if (time < animNode->mPositionKeys[0].mTime) {
		j = 0;
	}
	else {
		for (int i = 0; i < animNode->mNumPositionKeys - 1; i++) {
			if (animNode->mPositionKeys[i + 1].mTime == time) {
				j = i;
				break;
			}
			if (animNode->mPositionKeys[i + 1].mTime > time)
			{
				float deltaT = animNode->mPositionKeys[1 + i].mTime - animNode->mPositionKeys[i].mTime;
				float factor = (time - animNode->mPositionKeys[i].mTime) / deltaT;
				aiVector3D delta = animNode->mPositionKeys[i+1].mValue - animNode->mPositionKeys[i].mValue;
				aiVector3D out = animNode->mPositionKeys[i].mValue + factor * delta;
				(*vec).x = out.x;
				(*vec).y = out.y;
				(*vec).z = out.z;
				return;
			}
		}
	}
	(*vec).x = animNode->mPositionKeys[j].mValue.x;
	(*vec).y = animNode->mPositionKeys[j].mValue.y;
	(*vec).z = animNode->mPositionKeys[j].mValue.z;
	return;
}

void animation::setRootNode(const aiNode * node)
{
	this->nodes = node;
	mat4Copy(this->nodes->mTransformation, &this->inverseGlobalMartix);
	this->inverseGlobalMartix.Inverse();
}

void animation::setAnimation(const aiAnimation * anim)
{
	this->animations = anim;
}

double animation::getDuration()
{
	return this->animations->mDuration;
}

double animation::getTickPerSecond()
{
	return this->animations->mTicksPerSecond;
}
