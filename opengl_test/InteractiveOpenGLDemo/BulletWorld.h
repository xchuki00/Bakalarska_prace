#pragma once
#include "includes.h"
#include "Model.h"
class BulletWorld
{
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration * collisionConfig;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	std::vector<btCollisionShape*> shapes;
public:
	btDiscreteDynamicsWorld* world;
	int init();
	btCollisionObject* addCollisionObject(
		glm::mat4 position,
		glm::vec3 velocityGL,
		btScalar mass,
		Model* index
	);

	btCollisionObject* addGround(glm::mat4 position, Model* index);
	std::vector<Model *> *calculate();

	BulletWorld();
	~BulletWorld();
};

