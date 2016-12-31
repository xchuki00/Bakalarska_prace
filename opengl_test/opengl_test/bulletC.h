#pragma once
#include "includes.h"
#include "model.h"
class bulletC
{
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration * collisionConfig;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver *solver;
	
	btCollisionShape *Ground;
	std::vector<btCollisionShape*> shapes;
public:
	btDiscreteDynamicsWorld* world;
	bulletC();
	~bulletC();
	void initBullet();
	int addCollisionObject(
		glm::mat4 position,
		glm::vec3 velocityGL,
		btCollisionShape *shape,
		btScalar mass,
		int index
	);
	int addCollisionObject(
		glm::mat4 ,
		glm::vec3 ,
		std::vector<glm::vec3> ,
		btScalar ,
		int index
	);
	int addGround(glm::mat4 position, float width, float height);
	std::vector<int*>* calculate();
	btTransform  getTransform(int id);
	
};

