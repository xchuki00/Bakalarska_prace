#include "Projectil.h"
#include "controls.h"
#include "misc.h"

void Projectil::setMass(int m)
{
	this->mass = m;
}

void Projectil::setWeapon(Model * w)
{
	this->weapon = w;
}

Projectil::Projectil()
{
	this->classID = PROJECTIL;
}


Projectil::~Projectil()
{
}

glm::mat4 Projectil::getPosition()
{
	if (!this->firedAtr) {
		if (this->weapon != NULL) {
			this->weapon->calc();
		}
	}
	else if(this->inTargetAtr){
		//leftP=glm::rotate(leftP,Angle(oldModleleft,newModleleft),cross(oldModelLeft,NewModelLeft));
		//glm::mat4 mat(1.0f);
		//mat = glm::rotate(5.f,glm::vec3(0,1,0));








	}

	return this->modelMatrix;
}

int Projectil::init()
{

	this->countOfIndex = this->indices.size();
	this->modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));
	//this->modelMatrix = glm::rotate(this->modelMatrix, PI, glm::vec3(0, 1, 0));
	this->buffer();
	return 0;
}

void Projectil::triggered()
{
	this->timeOfTriggered = glfwGetTime();
}

int Projectil::fire(btCollisionObject *obj)
{

	this->bt = obj;
	btRigidBody* rb = btRigidBody::upcast(this->bt);
	double force = (glfwGetTime() - this->timeOfTriggered)*3;
//	btVector3 velocity(this->modelMatrix[2][0]*force, this->modelMatrix[2][1] * force, this->modelMatrix[2][2] * force);
	btVector3 velocity(getDir().x*force, getDir().y*force, getDir().z*force);
	rb->setLinearVelocity(velocity);
	this->firedAtr = true;
	return 0;
}

bool Projectil::fired()
{
	return this->firedAtr;
}

bool Projectil::inTarget()
{
	return this->inTargetAtr;
}

int Projectil::hitted(Model * byWho)
{
	if (!this->inTargetAtr) {
		this->weapon = byWho;
		mat4Copy(this->weapon->getPosition(), &this->oldOfTarget);
	//	btRigidBody *rb = btRigidBody::upcast(this->bt);
		//rb->setMassProps(0, btVector3(0, 0, 0));
		///Vypocet pozicniho  vstahu mezi projektilem a tim co trefil
		///make this->bt= static
		///set inTarget to true kvuli vypoctum polohy
		this->inTargetAtr = true;
	}
	//std::cerr << byWho->classID;
	//this->bt->setCollisionFlags(1);
	return 0;
}
