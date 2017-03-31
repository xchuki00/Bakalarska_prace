#include "Model.h"
#include "loader.h"
#include "texture.h"
#include "controls.h"
#include "misc.h"
/////////////MATRIX FOR TRANSFORM [-1,1] to [0,1]///////


glm::mat4 coordiationTransformMatrix(
	0.5, 0.0, 0.0, 0.0,
	0.0, 0.5, 0.0, 0.0,
	0.0, 0.0, 0.5, 0.0,
	0.5, 0.5, 0.5, 1.0
);
glm::vec3 light(5, 5, 0);
btCollisionObject * Model::getObj()
{
	return this->bt;
}
void Model::setObj(btCollisionObject * obj)
{
	this->bt = obj;
}
int Model::hitted(Model * byWho)
{
	return 0;
}
double Model::getDmg()
{
	return 0.0;
}
glm::mat4 Model::getPosition()
{
	return this->modelMatrix;
}
void Model::CalcBones(double time)
{
	static double timeLast=0;
	if (this->nodes != nullptr&&this->animations != nullptr) {
		if (timeLast != time) {
			timeLast = time;
			aiMatrix4x4 startMatrix = aiMatrix4x4();
			this->updateNode(this->nodes,startMatrix,time);
			for(int i=0;i<this->bones.size();i++){
				mat4Copy(this->bones[i].matrix, &this->finalTransform[i]);
			}
		}

	}
}
void Model::calc()
{
}
void Model::draw()
{
	//std::cerr <<this->classID<< " CALC PROSEL" << this->bones.size() << "\t" << this->finalTransform.size() << std::endl;
	this->CalcBones(this->getTime());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	//std::cerr << this->classID << "enable\n";
	glUseProgram(this->shader);
	glm::mat4 Projection = getProject();
	glm::mat4 View = getView();
	glm::mat4 MVP = Projection * View * this->getPosition();
	//std::cerr << this->classID << this->finalTransform.size()<<"mvp\n";
	glUniformMatrix4fv(this->MVPID, 1, GL_FALSE, &MVP[0][0]);
	if (this->finalTransform.size() != 0) {
		glUniformMatrix4fv(this->BonesID, this->finalTransform.size(), GL_FALSE, &this->finalTransform[0][0][0]);
	}
	//std::cerr << this->classID << "uniform\n";
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->textur);
	glUniform1i(this->textureID, 0);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MyVertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(MyVertex), (const GLvoid*)sizeof(glm::vec3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(MyVertex), (const GLvoid*)(sizeof(glm::vec2) + sizeof(glm::vec3)));
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(MyVertex), (const GLvoid*)(sizeof(glm::vec2) + sizeof(glm::vec3) + sizeof(glm::vec3)));
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(MyVertex), (const GLvoid*)(sizeof(glm::vec2) + sizeof(glm::vec3)+sizeof(glm::vec3)+sizeof(glm::vec4)));
	//std::cerr << this->classID << "vertexpoitn\n";
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);

	glDrawElements(GL_TRIANGLES, this->countOfIndex, GL_UNSIGNED_SHORT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	//std::cerr << this->classID << "DRAW DONE\n";
}

void Model::depthDraw()
{
}

double Model::getTime()
{
	return this->AnimationTime;
}

Model::Model()
{
	this->classID = MODEL;
	this->id = idCount;

	this->imp = new Assimp::Importer();

	idCount++;
}


Model::~Model()
{
	glDeleteBuffers(1, &this->vertexBuffer);
	glDeleteBuffers(1, &this->indexBuffer);
	//glDeleteBuffers(1, &this->boneBuffer);
	glDeleteProgram(this->shader);
}

int Model::load_3DModel(std::string path)
{
	//this->countOfIndex = loadObjAss(path,this->vertices,this->indices);
	this->countOfIndex = loadAnimated(path, this);
	std::cerr << "NODES " << this->nodes << " ANIM " << this->animations<< std::endl;

	this->buffer();
	if (this->nodes != nullptr) {
	//	std::cerr << "ANIMATION duration" << this->animations->mDuration << " " << this->animations->mChannels[3]->mNumPositionKeys<<std::endl;
		mat4Copy(this->nodes->mTransformation, &this->inverseGlobalMartix);
		this->inverseGlobalMartix.Inverse();
	}
	std::cerr << "model " << path << " nacten a nabufrovan." << std::endl;
	//this->CalcBones();
	return 0;
}

int Model::load_texture(const char * path)
{
	this->textur = loadTexture2d(path, &this->textureHeight, &this->textureWidth);

	return 0;
}

int Model::set3DModel(std::vector<MyVertex> v)
{
	this->vertices = v;

	return 0;
}

int Model::setIndices(std::vector<unsigned short> i)
{
	this->indices = i;
	return 0;
}

int Model::setTexture(GLuint t)
{
	this->textur = t;
	return 0;
}

int Model::buffer()
{
	std::cerr << "VERTEX" << this->vertices.size()<<this->indices.size() << std::endl;
	glGenBuffers(1, &this->vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MyVertex) * this->vertices.size(), &this->vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &this->indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * this->indices.size(), &this->indices[0], GL_STATIC_DRAW);

	if (this->nodes != nullptr&&this->animations != nullptr) {
			aiMatrix4x4 startMatrix= aiMatrix4x4();
			this->updateNode(this->nodes, startMatrix,0);
			//printNodeHiearchy(this->nodes);
		}
	//std::cerr << "prdel";
	return 0;
}

void Model::setShader(GLuint sh, GLuint texturID, GLuint MVPID, GLuint v, GLuint m, GLuint db, GLuint shadowMap, GLuint lightInvDir, GLuint depthSh, GLuint depthID)
{
	this->shader = sh;
	this->MVPID = MVPID;
	this->textureID = texturID;
	this->BonesID= glGetUniformLocation(this->shader, "gBones");
}

void Model::setShader(GLuint sh)
{
	this->shader = sh;
	this->textureID = glGetUniformLocation(this->shader, "myTextureSampler");
	this->MVPID = glGetUniformLocation(this->shader, "MVP");

}

void Model::setRigidBodyIndex(int id)
{
}

void Model::setPosition(glm::mat4 mat)
{
	mat4Copy(mat, &this->modelMatrix);
}

void Model::setBulletWorld(btDiscreteDynamicsWorld* bw)
{
	this->bulletWorld = bw;
}

btDiscreteDynamicsWorld* Model::getBulletWorld()
{
	return this->bulletWorld;
}

void Model::updateNode(const aiNode * Node, aiMatrix4x4 ParentTransform, double time)
{
//	std::cerr << "PRDER" << std::endl;
	std::string NodeName(Node->mName.data);
	const aiAnimation* pAnimation = this->animations;
	aiMatrix4x4 NodeTransformation=aiMatrix4x4(Node->mTransformation);
//	aiMatrix4x4 NodeTransformation = aiMatrix4x4();
	const aiNodeAnim* pNodeAnim = this->findAnimNode(pAnimation, NodeName);


	if (pNodeAnim!=nullptr) {

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
		//NodeTransformation = aiMatrix4x4();
		//NodeTransformation.Scaling(Scaling, NodeTransformation);
		//NodeTransformation.Translation(Translation, NodeTransformation);
		NodeTransformation = TransM*rotateM*scaleM;
		//NodeTransformation = rotateM;
	}
//	std::cerr << "rootNodde success\n";
	aiMatrix4x4 GlobalTransformation = ParentTransform * NodeTransformation;

	if (this->bonesMap.find(NodeName) != this->bonesMap.end()) {
		unsigned int BoneIndex = this->bonesMap[NodeName];
		this->bones[BoneIndex].matrix = this->inverseGlobalMartix * GlobalTransformation*this->bones[BoneIndex].offset;
	}
	for (unsigned int i = 0; i < Node->mNumChildren; i++) {
		this->updateNode(Node->mChildren[i], GlobalTransformation, time);
	}
}

const aiNodeAnim * Model::findAnimNode(const aiAnimation * anim, std::string nodeName)
{
	//std::cerr << "find node anim\n";

	for (int i = 0; i < anim->mNumChannels; i++) {
		if (anim->mChannels[i]->mNodeName.data == nodeName) {
			return anim->mChannels[i];
		}
	}
	return nullptr;
}

void Model::getNodeRotation(aiQuaternion* vec, double time,const aiNodeAnim * animNode)
{
	//std::cerr << "rot";
	for (int i = 0; i < animNode->mNumRotationKeys-1; i++) {
		if (animNode->mRotationKeys[i+1].mTime > time)
		{
			float deltaT=animNode->mRotationKeys[i+1].mTime-animNode->mRotationKeys[i].mTime;
			float factor=(time-animNode->mRotationKeys[i].mTime)/deltaT;
			aiQuaternion out;
			aiQuaternion::Interpolate(out, animNode->mRotationKeys[i].mValue, animNode->mRotationKeys[i+1].mValue, factor);
			out = out.Normalize();
			(*vec).x = out.x;
			(*vec).y = out.y;
			(*vec).z = out.z;
			(*vec).w = out.w;
			return;
		}
	}
	(*vec).x = animNode->mRotationKeys[0].mValue.x;
	(*vec).y = animNode->mRotationKeys[0].mValue.y;
	(*vec).z = animNode->mRotationKeys[0].mValue.z;
	(*vec).w = animNode->mRotationKeys[0].mValue.w;
	return;
}

void Model::getNodeScale(aiVector3D* vec, double time,const aiNodeAnim * animNode)
{
//	std::cerr << "scale";
	for (int i = 0; i < animNode->mNumScalingKeys - 1; i++) {
		if (animNode->mScalingKeys[i + 1].mTime > time)
		{
			float deltaT = animNode->mScalingKeys[1 + i].mTime - animNode->mScalingKeys[i].mTime;
			float factor = (time - animNode->mScalingKeys[i].mTime) / deltaT;
			aiVector3D delta=animNode->mScalingKeys[i+1].mValue-animNode->mScalingKeys[i].mValue;
			aiVector3D out = animNode->mScalingKeys[i].mValue + factor*delta;
			(*vec).x = out.x;
			(*vec).y = out.y;
			(*vec).z = out.z;
			return;
		}
	}
	(*vec).x = animNode->mScalingKeys[0].mValue.x;
	(*vec).y = animNode->mScalingKeys[0].mValue.y;
	(*vec).z = animNode->mScalingKeys[0].mValue.z;
	return;
}

void Model::getNodePosition(aiVector3D* vec, double time, const aiNodeAnim * animNode)
{
	//std::cerr << "pos";
	for (int i = 0; i < animNode->mNumPositionKeys - 1; i++) {
		if (animNode->mPositionKeys[i + 1].mTime > time)
		{
			float deltaT = animNode->mPositionKeys[1 + i].mTime - animNode->mPositionKeys[i].mTime;
			float factor = (time - animNode->mPositionKeys[i].mTime) / deltaT;
			aiVector3D delta = animNode->mPositionKeys[i + 1].mValue - animNode->mPositionKeys[i].mValue;
			aiVector3D out = animNode->mPositionKeys[i].mValue + factor * delta;
			(*vec).x = out.x;
			(*vec).y = out.y;
			(*vec).z = out.z;
			return;
		}
	}
	(*vec).x = animNode->mPositionKeys[0].mValue.x;
	(*vec).y = animNode->mPositionKeys[0].mValue.y;
	(*vec).z = animNode->mPositionKeys[0].mValue.z;
	return;
}

