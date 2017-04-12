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
float Model::getDmg()
{
	return 1.0;
}
glm::mat4 Model::getPosition()
{
	return this->modelMatrix;
}
void Model::CalcBones(double time)
{
	static double timeLast=0;
	if (this->animation!=nullptr) {
		if (timeLast != time) {
			timeLast = time;
			aiMatrix4x4 startMatrix = aiMatrix4x4();
			this->animation->updateNode(this->animation->nodes,startMatrix,time);
			this->setFinalTransformation();
		}
	}
}
void Model::calc()
{
}
void Model::draw()
{
	this->CalcBones(this->getTime());
	glm::mat4 Projection = getProject();
	glm::mat4 View = getView();
	glm::mat4 MVP = Projection * View * this->getPosition();
	glUniformMatrix4fv(this->MVPID, 1, GL_FALSE, &MVP[0][0]);

	Projection = getOrthoProject();
	View = getOrthoView();
	glm::mat4 LVP = /*glm::translate(glm::mat4(1.0f), glm::vec3(1.0f))*glm::scale(glm::mat4(1.0f), glm::vec3(0.5f))*/Projection * View * this->getPosition();
	glUniformMatrix4fv(this->LVPID, 1, GL_FALSE, &LVP[0][0]);

	glUniformMatrix4fv(this->ModelID, 1, GL_FALSE, &this->modelMatrix[0][0]);
	if (this->animation!=nullptr) {
		glUniformMatrix4fv(this->BonesID, this->finalTransform.size(), GL_FALSE, &this->finalTransform[0][0][0]);
	}
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->textur);
	glUniform1i(this->textureID, 1);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MyVertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(MyVertex), (const GLvoid*)sizeof(glm::vec3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(MyVertex), (const GLvoid*)(sizeof(glm::vec2) + sizeof(glm::vec3)));
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(MyVertex), (const GLvoid*)(sizeof(glm::vec2) + sizeof(glm::vec3) + sizeof(glm::vec3)));
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(MyVertex), (const GLvoid*)(sizeof(glm::vec2) + sizeof(glm::vec3)+sizeof(glm::vec3)+sizeof(glm::vec4)));
	//std::cerr << this->classID << "vertexpoitn\n";
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);

	glDrawElements(GL_TRIANGLES, this->countOfIndex, GL_UNSIGNED_SHORT, 0);
}

void Model::DrawToShadowMap()
{
//	this->CalcBones(this->getTime());
	glm::mat4 Projection = getOrthoProject();
	glm::mat4 View = getOrthoView();
	
	glm::mat4 MVP = /*glm::translate(glm::mat4(1.0f), glm::vec3(1.0f))*glm::scale(glm::mat4(1.0f),glm::vec3(0.5f))**/Projection * View * this->getPosition();
	glUniformMatrix4fv(this->ShadowMVPID, 1, GL_FALSE, &MVP[0][0]);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MyVertex), 0);
	//std::cerr << this->classID << "vertexpoitn\n";
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);

	glDrawElements(GL_TRIANGLES, this->countOfIndex, GL_UNSIGNED_SHORT, 0);
}

double Model::getTime()
{
	return this->AnimationTime;
}

Model::Model()
{
	this->classID = MODEL;
	this->id = idCount;


	idCount++;
}


Model::~Model()
{
	glDeleteBuffers(1, &this->vertexBuffer);
	glDeleteBuffers(1, &this->indexBuffer);
	//glDeleteTextures(1, &this->textureID);
	//glDeleteBuffers(1, &this->boneBuffer);
	glDeleteProgram(this->shader);
}

int Model::load_3DModel(std::string path)
{
	//this->countOfIndex = loadObjAss(path,this->vertices,this->indices);
	this->countOfIndex = loadAnimated(path, this);

	this->buffer();
	//this->CalcBones();
	return 0;
}

int Model::load_texture(const char * path)
{
	this->textur = loadTexture2d(path, &this->textureHeight, &this->textureWidth, GL_RGBA);

	return 0;
}
int Model::set3DModel(ImportModel * importmodel)
{
	this->vertices = importmodel->getVertices();
	this->indices = importmodel->getIndices();
	this->countOfIndex = this->indices.size();
	if (importmodel->hasAnimation()) {
		this->animation = importmodel->getAnimation();
		this->setAnimatonShaderID();
		this->initFinalTransformation();
	}
	this->buffer();
	return 0;
}

int Model::setTexture(GLuint t)
{
	this->textur = t;
	return 0;
}

void Model::initFinalTransformation()
{
	for (int i = 0; i<this->animation->bones.size(); i++) {
		this->finalTransform.push_back(aiMatrix4x4());
	}
}

void Model::setFinalTransformation()
{
	for (int i = 0; i<this->animation->bones.size(); i++) {
		mat4Copy(this->animation->bones[i].matrix, &this->finalTransform[i]);
	}
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

	//std::cerr << "prdel";
	return 0;
}

void Model::setShader(GLuint sh)
{
	this->shader = sh;
	this->textureID = glGetUniformLocation(this->shader, "myTextureSampler");
	this->MVPID = glGetUniformLocation(this->shader, "MVP");
	this->ModelID = glGetUniformLocation(this->shader, "M");
	this->LVPID = glGetUniformLocation(this->shader, "LVP");
}

void Model::setShadowShader(GLuint sh)
{
	this->shadowShader = sh;
	this->ShadowMVPID = glGetUniformLocation(this->shadowShader, "MVP");
}

void Model::setAnimatonShaderID()
{
	if(this->animation!=nullptr)
		this->BonesID = glGetUniformLocation(this->shader, "gBones");
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
