#include "model.h"
#include "misc.h"
#include "controls.h"
#include "vboindexer.cpp"
/////////////MATRIX FOR TRANSFORM [-1,1] to [0,1]///////
glm::mat4 coordiationTransformMatrix(
	0.5, 0.0, 0.0, 0.0,
	0.0, 0.5, 0.0, 0.0,
	0.0, 0.0, 0.5, 0.0,
	0.5, 0.5, 0.5, 1.0
);
glm::vec3 light(5, 5, 0);
/////////////INIT FUNKCE///////////////
int model::load_3DModel(std::string path) {
	std::vector<glm::vec3> ver;
	std::vector<glm::vec2> uv;
	std::vector<glm::vec3> nor;
	loadObj(path, ver,uv,nor);
	//loadObj(path, this->ver, this->uv, this->nor);
	//indexVBO(ver,uv,nor,this->ver,this->uv,this->nor,this->indices);
	indexVBO(ver,uv,nor,this->indices,this->ver,this->uv,this->nor);
	return 0;
}
int model::load_texture(const char * path) {

	this->textur=loadTexture2d(path,&this->textureHeight,&this->textureWidth);

	/*for (int i = 0; i < this->uv.size(); i++) {
		this->uv[i][0] = this->uv[i][0] * this->textureWidth;
		this->uv[i][1] = this->uv[i][1] * this->textureHeight;
	}*/
	return 0;
}
int model::buffer()
{
	//std::cout << "buffer::"<<this->getSizeofVer()<<"\t"<<this->getCountOfVertex()<<"*"<<sizeof(glm::vec3)<< std::endl;
	glGenBuffers(1, &(this->vertexBuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->getSizeofVer(), this->getVer(), GL_STATIC_DRAW);
	
	glGenBuffers(1, &(this->uvBuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this->uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->getSizeofUv(), this->getUv(), GL_STATIC_DRAW);
	
	glGenBuffers(1, &(this->normalBuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this->normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->getSizeofNor(), this->getNor(), GL_STATIC_DRAW);

	glGenBuffers(1, &(this->elementBuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this->elementBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->getSizeofInd(), this->getIndices(), GL_STATIC_DRAW);
	//std::cerr << "textura" << ":" << this->textur << std::endl;
	return 0;
}
void model::setShader(GLuint sh, GLuint textID, GLuint MVPID, GLuint v, GLuint m, GLuint db, GLuint shadowMap, GLuint lightInvDir, GLuint depthSh, GLuint depthID)
{
	this->shader = sh;
	this->depthShader = depthSh;
	this->textureID = textID;
	this->MVPID = MVPID;
	this->viewID = v;
	this->modelID = m;
	this->DepthBiasID = db;
	this->shadowMapID = shadowMap;
	this->depthMVPID = depthID;
	this->lightInvDirID = lightInvDir;
}

/////////INFO//////////
void model::setRigidBodyIndex(int id)
{
	this->rigidBodyIndex = id;
}
int model::getRigidBodyIndex()
{
	return this->rigidBodyIndex;
}
int model::hitted(model * byWho)
{
	//std::cerr << "MODEL\n";
	if (byWho->classID != GROUND) {
		//	std::cerr << "somethig\n";
	//	this->textur = loadTexture2d("red.bmp", &this->textureHeight, &this->textureWidth);
	}/*
	 btRigidBody* body = btRigidBody::upcast(this->obj);
	 btVector3 vec = body->getLinearVelocity();
	 btVector3 vec2(this->velocity[0], this->velocity[1], this->velocity[2]);
	 vec += vec2;
	 vec /= 2;
	 body->setLinearVelocity(vec);
	 *///std::cerr << "object " << this->RigidBodyIndex << "zasazen\n";

	return NOTHING;
}
double model::getDmg()
{
	return glm::length(this->velocity);
}
///////VELOCITY & POSITION///////////
int model::setVelocity(glm::vec3 dir)
{
	vec3Copy(dir, &this->velocity);
		return 0;
}
void model::setPosition(glm::mat4 mat)
{
	mat4Copy(mat, &this->matrix);
}
glm::mat4 model::getPosition()
{
	return this->matrix;
}
glm::vec3 model::getVelocity()
{
	return this->velocity;
}
void model::calculateVelocity()
{
	//this->velocity = glm::vec3(0,0,0);
}
///////////WORK with VER,UV,NOR,IND//////////////

//navrati ukazatel na pole vrcholu/jejich uv ci normal
GLvoid* model::getVer()
{
	return &(this->ver)[0][0];
}
std::vector<glm::vec3> model::getVertices()
{
	return this->ver;
}
int model::getSizeofVer()
{
	return this->ver.size() * sizeof(glm::vec3);
}
int model::getCountOfVertex()
{
	return this->ver.size();
}

GLvoid* model::getUv()
{
	return &(this->uv)[0][0];
}
int model::getSizeofUv()
{
	return this->uv.size() * sizeof(glm::vec2);
}

GLvoid* model::getNor()
{
	return &(this->nor)[0][0];
}
int model::getSizeofNor()
{
	return this->nor.size() * sizeof(glm::vec3);
}

GLvoid * model::getIndices()
{
	return &(this->indices)[0];
}
int model::getSizeofInd()
{
	return this->indices.size() * sizeof(unsigned short);
}

//PRACE s MODEL MATRIX
void model::scale(glm::vec3 vector)
{
	//this->matrix = glm::scale(2.0f, 2.0f, 2.0f);
}
void model::translate(glm::vec3 vector)
{
}
void model::draw(GLuint depthTexture)
{
	
	glUseProgram(this->shader);
	glm::mat4 Projection = getProject();
	glm::mat4 View = getView();
	glm::mat4 MVP = Projection * View * this->matrix;
	glm::mat4 depthBias = coordiationTransformMatrix*this->depthMVP;
	//std::cerr << glm::to_string(MVP) << std::endl;
	glUniformMatrix4fv(this->MVPID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(this->modelID, 1, GL_FALSE, &this->matrix[0][0]);
	glUniformMatrix4fv(this->viewID, 1, GL_FALSE, &View[0][0]);
	glUniformMatrix4fv(this->DepthBiasID, 1, GL_FALSE, &depthBias[0][0]);

	glUniform3f(this->lightInvDirID,light.x,light.y,light.z);

	//nahraju texturu do shaderu
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->textur);
	glUniform1i(this->textureID, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glUniform1i(this->shadowMapID, 1);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->uvBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, this->normalBuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementBuffer);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_SHORT, (void*)0);
	//glDrawArrays(GL_TRIANGLES, 0,this->getCountOfVertex());
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	this->calculateVelocity();

}
void model::depthDraw()
{
	glUseProgram(this->depthShader);
	glm::mat4 depthProject = glm::ortho<float>(-10, 10, -10, 10, - 10, 20);
	glm::mat4 depthView=glm::lookAt(light,glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 depthMVP = this->matrix*depthView*depthProject;

	glUniformMatrix4fv(this->depthMVPID,1,GL_FALSE,&depthMVP[0][0]);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementBuffer);
	glDrawElements(GL_TRIANGLES,this->indices.size(),GL_UNSIGNED_SHORT,(void*)0);
	//glDrawArrays(GL_TRIANGLES, 0, this->getCountOfVertex());
	glDisableVertexAttribArray(0);
}
////////////////CONSTRUCTOR & DESTRUCTOR
model::model()
{
	this->classID = MODEL;
}
model::~model()
{
	glDeleteBuffers(1, &this->vertexBuffer);
	glDeleteBuffers(1, &this->uvBuffer);
}
