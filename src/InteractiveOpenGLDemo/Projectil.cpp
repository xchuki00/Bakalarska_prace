#include "Projectil.h"
#include "controls.h"
#include "misc.h"
#include "Weapon.h"
int Model::idCount = 0;
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
			//std::cerr << "INIT WEAOPN ID" << this->weapon->id << std::endl;
		}
	}
	else if(this->inTargetAtr){

		glm::vec3 pom;
		pom.x = this->weapon->getPosition()[0][1] + this->weapon->getPosition()[0][2] + this->weapon->getPosition()[0][3];
		pom.y = this->weapon->getPosition()[1][1] + this->weapon->getPosition()[1][2] + this->weapon->getPosition()[1][3];
		pom.z = this->weapon->getPosition()[2][1] + this->weapon->getPosition()[2][2] + this->weapon->getPosition()[2][3];
		if (pom.x != this->oldModel.x || pom.y != this->oldModel.y || pom.z != this->oldModel.z) {
			float angle = AngleBetween(pom, this->oldModel);
			glm::vec3 axis = glm::cross(pom, this->oldModel);
			this->modelMatrix = glm::rotate(this->modelMatrix, -angle, axis);
			this->translateVec = glm::rotate(this->translateVec, angle, axis);
			this->modelMatrix[3][0] = this->weapon->getPosition()[3][0] + this->translateVec[0];
			this->modelMatrix[3][2] = this->weapon->getPosition()[3][2] + this->translateVec[1];
			this->modelMatrix[3][2] = this->weapon->getPosition()[3][2] + this->translateVec[2];
			//this->modelMatrix = glm::translate(this->weapon->getPosition(), this->translateVec);
			//mat4Copy(this->weapon->getPosition(), &this->oldOfTarget);
			this->oldModel.x = pom.x;
			this->oldModel.y = pom.y;
			this->oldModel.z = pom.z;
			static int i = 0;
			if (i % 60 == 0)
				//std::cerr <<"ANGLE:"<< angle<<"AXSI"<<glm::to_string(axis)<< "PROJECTIL: " << glm::to_string(this->modelMatrix) << std::endl;
			i++;
		}

	}
	else if (this->firedAtr && !this->inTargetAtr) {

		glm::vec3 w = this->wind->getLocalWind(this->modelMatrix[3]);
		btRigidBody *rb = btRigidBody::upcast(this->bt);
		rb->clearForces();
		rb->applyCentralForce(btVector3(w.x,w.y,w.z));
		rb->activate();
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
	double force = ((glfwGetTime() - this->timeOfTriggered)>1.5)? (glfwGetTime() - this->timeOfTriggered):1.5;
	force *= 7;
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
	std::cerr << "Objetk " << this->id << " ZASAZENO " << byWho->classID << " OBJECT ID " << byWho->id << std::endl;

	if (!this->inTargetAtr&&byWho->classID!=PLAYER) {
		///Kontrola uhlu dopadu <45 == zabodne jinak odraz?
		if (this->bt != nullptr) {
			btRigidBody* body = btRigidBody::upcast(this->bt);
			btTransform t;
			if (body && body->getMotionState())
			{
				body->getMotionState()->getWorldTransform(t);
				//t = obj->getWorldTransform();
			}
			else
			{
				t = this->bt->getWorldTransform();
			}
			t.getOpenGLMatrix(glm::value_ptr(this->modelMatrix));
		}
		//this->models[i]->setPosition(mat);

		if (byWho->classID != GROUND) {
			glm::vec3 modPos = byWho->getPosition()[3];
			glm::vec3 weaponPos = this->weapon->getPosition()[3];
			((Weapon*)(this->weapon))->setLastDmg(distance(modPos, weaponPos));
		}
		this->weapon = byWho;
		this->translateVec.x = (this->modelMatrix[3][0] - this->weapon->getPosition()[3][0])*0.8;
		this->translateVec.y = (this->modelMatrix[3][1] - this->weapon->getPosition()[3][1])*0.8;
		this->translateVec.z = (this->modelMatrix[3][2] - this->weapon->getPosition()[3][2])*0.8;
		this->oldModel.x = this->weapon->getPosition()[0][1] + this->weapon->getPosition()[0][2] + this->weapon->getPosition()[0][3];
		this->oldModel.y = this->weapon->getPosition()[1][1] + this->weapon->getPosition()[1][2] + this->weapon->getPosition()[1][3];
		this->oldModel.y = this->weapon->getPosition()[2][1] + this->weapon->getPosition()[2][2] + this->weapon->getPosition()[2][3];
		this->inTargetAtr = true;		
		return DESTROY_BULLET;
	}
	return NOTHING;
}
