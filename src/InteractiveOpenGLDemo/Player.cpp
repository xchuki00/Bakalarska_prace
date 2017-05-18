#include "Player.h"
#include "controls.h"
#include "misc.h"
static glm::vec3 up(0, -1, 0);
static glm::vec3 dir(0, 0, -1);
static float VAngle = 0;
static float HAngle = 0;
static float oldVAngle = 0;
static float oldHAngle = 0;
void Player::jump()
{
	this->landed = false;
}


Player::~Player()
{
	

}
int Player::hasArrows()
{
	return this->arrows;
}

void Player::addArrowStack(ArrowStack * as)
{
	if (as != NULL || as !=nullptr) {
		this->arrowStack = as;
		this->arrowStack->setCountOfArrows(this->arrows);
	}
}

void Player::addHitsHud(HitsHud * hh)
{
	if (hh != NULL || hh != nullptr) {
		this->hitsHud = hh;
		this->hitsHud->setPrefix("Score:");
		this->hitsHud->setContains(hits);
	}
}

void Player::triggered()
{
	this->w->triggered();
}

void Player::fire(Projectil* load, btCollisionObject *obj)
{
		if (this->w != NULL || this->w != nullptr) {
				this->w->fire(load, obj);
		}
		this->arrows--;
		if (this->arrowStack != NULL || this->arrowStack != nullptr) {
			this->arrowStack->minus();
		}
}

void Player::Angles()
{
	VAngle = getVAngle() - oldVAngle;
	HAngle = getHAngle() - oldHAngle;
	oldHAngle = getHAngle();
	oldVAngle = getVAngle();
}

void Player::setWeapon(Weapon * ww)
{
	//	mat4Copy(m, &this->WeaponSlot);
	
	if (ww != NULL) {
		this->Angles();
		this->w = ww;
		this->w->modelMatrix = glm::rotate(this->w->modelMatrix, -PI / 6, glm::vec3(1, 0, 0));
		up = glm::rotate(up, PI / 6, glm::vec3(1, 0, 0));
		dir = glm::rotate(dir, PI / 6, glm::vec3(1, 0, 0));
		this->w->modelMatrix[3][0] = this->modelMatrix[3].x;
		this->w->modelMatrix[3][1] = this->modelMatrix[3].y;	
		this->w->modelMatrix[3][2] = this->modelMatrix[3].z;
		this->w->setPlayer(this);
	}
	
}

void Player::calc()
{
	if (this->w != NULL) {
		this->Angles();
		//glm::vec3 shift = getDir();
		glm::vec3 shift = getDir() - getUp()*0.04 + getRight()*0.04;
		this->w->modelMatrix = glm::rotate(this->w->modelMatrix, VAngle, up);
		dir = glm::rotate(dir, -VAngle, up);
		this->w->modelMatrix = glm::rotate(this->w->modelMatrix, HAngle, dir);


		this->w->modelMatrix[3][0] = this->modelMatrix[3][0] + shift.x;
		this->w->modelMatrix[3][1] = this->modelMatrix[3][1] + shift.y;
		this->w->modelMatrix[3][2] = this->modelMatrix[3][2] + shift.z;
	}
}

void Player::reportDmg(float f)
{
	this->hits += f;
	this->hitsHud->setContains(this->hits);
}

Weapon * Player::getWeapon()
{
	return this->w;
}
glm::mat4 Player::getPosition() {

	return this->modelMatrix;
}

Player::Player()
{
	this->classID = PLAYER;

}

bool Player::land()
{
	return this->landed;
}

int Player::hitted(Model * byWho)
{
	if (byWho->classID == GROUND&&!this->landed) {
		this->landed = true;
	}
	return 0;
}


