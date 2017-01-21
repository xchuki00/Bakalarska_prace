#include "bulletC.h"

//#include "btBulletDynamicsCommon.h"
//#include <BulletCollision\CollisionShapes\btSphereShape.h>

bulletC::bulletC()
{
}


bulletC::~bulletC()
{
	for (int i = this->world->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = this->world->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		this->world->removeCollisionObject(obj);
		delete obj;
	}
	btCollisionShape *shape;
	for (int j = 0; j<this->shapes.size(); j++)
	{
		shape = this->shapes[j];
		this->shapes[j] = 0;
		delete shape;
	}

	delete this->world;
	delete this->solver;
	delete this->dispatcher;
	delete this->collisionConfig;
	delete this->broadphase;
	
}

void bulletC::initBullet()
{
	this->broadphase = new btDbvtBroadphase();
	this->collisionConfig = new btDefaultCollisionConfiguration();
	this->dispatcher = new btCollisionDispatcher(this->collisionConfig);
	this->solver = new btSequentialImpulseConstraintSolver;
	this->world = new btDiscreteDynamicsWorld(this->dispatcher, this->broadphase, this->solver, this->collisionConfig);
	this->world->setGravity(btVector3(0, -1, 0));
	std::cerr << "Bullet Init" << std::endl;
	
}

btCollisionObject* bulletC::addCollisionObject(glm::mat4 position, glm::vec3 velocityGL, btCollisionShape *shape, btScalar mass,int index)
{
	//this->bodies.push_back(new btSphereShape(1));
	//btCollisionShape *shape = new btBoxShape(btVector3(1.0f, 1.0f, 1.0f));
	//btCollisionShape *shape = new btSphereShape(1);
	//btdefaultMotionState(position,inertia)
	btTransform temp;
	temp.setFromOpenGLMatrix(glm::value_ptr(position));
	btVector3 inertiaVec(0,0,0);
	if (mass > 0)
	{
		shape->calculateLocalInertia(mass, inertiaVec);
	}

	btDefaultMotionState* motionState =
		new btDefaultMotionState(temp);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, motionState, shape, inertiaVec);
	btRigidBody* RigidBody = new btRigidBody(fallRigidBodyCI);
	btVector3 velocity(velocityGL[0], velocityGL[1], velocityGL[2]);
	RigidBody->setLinearVelocity(velocity);
	RigidBody->setUserIndex(index);
	RigidBody->setUserIndex2(this->world->getNumCollisionObjects());
	this->world->addRigidBody(RigidBody);
	bool match = false;
	for (int i = 0; i < this->shapes.size(); i++) {
		if (shape == this->shapes[i]) {
			match = true;
			break;
		}
	}
	if (!match) {
		this->shapes.push_back(shape);
	}//delete shape;
	return this->world->getCollisionObjectArray()[this->world->getNumCollisionObjects() - 1];
}

btCollisionObject* bulletC::addCollisionObject(glm::mat4 position, glm::vec3 velocityGL, std::vector<glm::vec3> vertices, btScalar mass, int index)
{
	btConvexHullShape *shape = new btConvexHullShape();
	for (int i = 0; i < vertices.size(); i++) {
		shape->addPoint(btVector3(vertices.data()[i][0], vertices.data()[i][1], vertices.data()[i][2]),true);
	}
	
	btTransform temp;
	temp.setFromOpenGLMatrix(glm::value_ptr(position));
	btVector3 inertiaVec(0, 0, 0);
	if (mass > 0)
	{
		shape->calculateLocalInertia(mass, inertiaVec);
	}
	
	btDefaultMotionState* motionState =
		new btDefaultMotionState(temp);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, motionState, shape, inertiaVec);
	btRigidBody* RigidBody = new btRigidBody(fallRigidBodyCI);
	btVector3 velocity(velocityGL[0], velocityGL[1], velocityGL[2]);
	RigidBody->setLinearVelocity(velocity);
	RigidBody->setUserIndex(index);
	
	this->world->addRigidBody(RigidBody);
	bool match = false;
	for (int i = 0; i < this->shapes.size(); i++) {
		if (shape == this->shapes[i]) {
			match = true;
			break;
		}
	}
	if (!match) {
		this->shapes.push_back(shape);
	}//delete shape;
	return this->world->getCollisionObjectArray()[this->world->getNumCollisionObjects() - 1];
}




btCollisionObject* bulletC::addGround(glm::mat4 position, float wideth, float height,int index)
{
	this->Ground = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
	btTransform temp;
	temp.setFromOpenGLMatrix(glm::value_ptr(position));
	btDefaultMotionState* groundMotionState =
		new btDefaultMotionState(temp);	
	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI(0, groundMotionState, this->Ground, btVector3(0, 0, 0));
	btRigidBody* rb = new btRigidBody(groundRigidBodyCI);
	rb->setUserIndex(index);
	rb->setUserIndex2(this->world->getNumCollisionObjects());
	this->world->addRigidBody(rb);
		std::cerr << "ground add" << std::endl;
	return this->world->getCollisionObjectArray()[this->world->getNumCollisionObjects() - 1];
	
}
std::vector<int*>* bulletC::calculate()
{

	static double lastT = glfwGetTime();
	double current = glfwGetTime();
	double delta = double(current - lastT);
	this->world->stepSimulation(delta, 10);
		//print positions of all objects
		for (int j = this->world->getNumCollisionObjects() - 1; j >= 0; j--)
		{
			btCollisionObject* obj = this->world->getCollisionObjectArray()[j];
			btRigidBody* body = btRigidBody::upcast(obj);
			btTransform trans;
			if (body && body->getMotionState())
			{
				body->getMotionState()->getWorldTransform(trans);

			}
			else
			{
				trans = obj->getWorldTransform();
			}
//			printf("world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
		}
		int numManifolds = world->getDispatcher()->getNumManifolds();
		std::vector<int*> *hitted=new std::vector<int*>;
		for (int i = 0; i<numManifolds; i++)
		{
			btPersistentManifold* contactManifold = world->getDispatcher()->getManifoldByIndexInternal(i);
			const btCollisionObject* obA = (contactManifold->getBody0());
			const btCollisionObject* obB = (contactManifold->getBody1());

			int numContacts = contactManifold->getNumContacts();
			for (int j = 0; j<numContacts; j++)
			{
				btManifoldPoint& pt = contactManifold->getContactPoint(j);
				if (pt.getDistance()<0.f)
				{
					const btVector3& ptA = pt.getPositionWorldOnA();
					const btVector3& ptB = pt.getPositionWorldOnB();
					const btVector3& normalOnB = pt.m_normalWorldOnB;
				
					
				}
			}
			int *pom = new int[2];
			pom[0] = obA->getUserIndex();
			pom[1] = obB->getUserIndex();
			hitted->push_back(pom);
			//hitted->push_back(obA->getUserIndex());
			//hitted->push_back(obB->getUserIndex());
			
		}
		return hitted;
}

btTransform bulletC::getTransform(int id)
{

	
	btTransform t;
	btCollisionObject* obj = this->world->getCollisionObjectArray()[id];
	btRigidBody* body = btRigidBody::upcast(obj);
	
	if (body && body->getMotionState())
	{
		body->getMotionState()->getWorldTransform(t);

	}
	else
	{
		t= obj->getWorldTransform();
	}
	return t;
}
