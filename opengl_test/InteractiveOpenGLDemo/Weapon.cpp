#include "Weapon.h"
#include "controls.h"
///vectory pro rotaci projektilu
static glm::vec3 upProjectil(1, 0, 0);
static glm::vec3 dirProjectil(0, -1, 0);
static float VAngle=0;
static float HAngle=0;
static float oldVAngle = 0;
static float oldHAngle = 0;
void Weapon::Angles()
{
	VAngle =  getVAngle() - oldVAngle;
	HAngle = getHAngle() - oldHAngle;
	oldHAngle = getHAngle();
	oldVAngle = getVAngle();
}
void Weapon::triggered()
{
	this->p->triggered();
}
Model * Weapon::getPlayer()
{
	return this->player;
}
void Weapon::setPlayer(Model * p)
{
	this->player = p;
}

void Weapon::init(Projectil * p)
{
	this->Angles();
	this->modelMatrix = glm::rotate(glm::mat4(1.f), -PI / 2, glm::vec3(0, 1, 0));
	this->modelMatrix = glm::rotate(this->modelMatrix, PI / 2, glm::vec3(1, 0, 0));
	this->modelMatrix = glm::scale(this->modelMatrix, glm::vec3(0.02, 0.02, 0.02));
	if(p!=NULL){
		this->p = p;
		upProjectil = glm::vec3(1, 0, 0);
		dirProjectil = glm::vec3(0, -1, 0);
		this->p->modelMatrix = glm::rotate(this->p->modelMatrix, -getVAngle(), upProjectil);
		dirProjectil = glm::rotate(dirProjectil, getVAngle(), upProjectil);
		this->p->modelMatrix = glm::rotate(this->p->modelMatrix, -getHAngle(), dirProjectil);

		this->p->modelMatrix[3][0] = this->modelMatrix[3][0];
		this->p->modelMatrix[3][1] = this->modelMatrix[3][1];
		this->p->modelMatrix[3][2] = this->modelMatrix[3][2];
		this->p->setWeapon(this);
	}
}

void Weapon::reload(Projectil * p)
{
	if (p != NULL) {
		this->p = p;
		this->Angles();
		upProjectil = glm::vec3(1, 0, 0);
		dirProjectil = glm::vec3(0, -1, 0);

		this->p->modelMatrix = glm::rotate(this->p->modelMatrix, -getVAngle(), upProjectil);
		dirProjectil = glm::rotate(dirProjectil, getVAngle(), upProjectil);
		this->p->modelMatrix = glm::rotate(this->p->modelMatrix, -getHAngle(), dirProjectil);
		
		this->p->modelMatrix[3][0] = this->modelMatrix[3][0];
		this->p->modelMatrix[3][1] = this->modelMatrix[3][1];
		this->p->modelMatrix[3][2] = this->modelMatrix[3][2];
		this->p->setWeapon(this);
	}
}

void Weapon::fire(Projectil* load, btCollisionObject *obj)
{
	if (this->p != NULL) {
		this->p->fire(obj);

		this->reload(load);
	}
}

void Weapon::calc()
{
	static int i = 0;
	if (this->p != NULL) {
		

		this->player->calc();
		this->Angles();
		//std::cerr <<i<<"VANGLE: "<<VAngle<<"\t HANGLE: "<<HAngle<<std::endl;
		this->p->modelMatrix = glm::rotate(this->p->modelMatrix, -VAngle, upProjectil);
		dirProjectil = glm::rotate(dirProjectil, VAngle, upProjectil);
		this->p->modelMatrix = glm::rotate(this->p->modelMatrix, -HAngle, dirProjectil);

		glm::vec3 shift = -getRight()*0.01f;
		this->p->modelMatrix[3][0] = this->modelMatrix[3][0]+shift.x;
		this->p->modelMatrix[3][1] = this->modelMatrix[3][1]+shift.y;
		this->p->modelMatrix[3][2] = this->modelMatrix[3][2]+shift.z;
		i++;
		//std::cerr << "PRDEL" << glm::to_string(this->p->modelMatrix)<<std::endl;
		//return this->p->modelMatrix;
	}
}


glm::mat4 Weapon::getPosition()
{
	static int i = 0;
	this->player->calc();
	if(i%60==0)
	//std::cerr << "WEAPON: " << glm::to_string(this->modelMatrix)<<std::endl;
	i++;
	return this->modelMatrix;
	
}

Projectil * Weapon::getProjectil()
{
	return this->p;
}

Weapon::Weapon()
{
	this->classID = WEAPON;

}


Weapon::~Weapon()
{
}
