#include "BulletWorld.h"
#include "BulletCollision/CollisionShapes/btShapeHull.h"
#include <BulletCollision\CollisionShapes\btConvexHullShape.h>
#include <BulletCollision\CollisionShapes\btHeightfieldTerrainShape.h>
int BulletWorld::init()
{
	this->broadphase = new btDbvtBroadphase();
	this->collisionConfig = new btDefaultCollisionConfiguration();
	this->dispatcher = new btCollisionDispatcher(this->collisionConfig);
	this->solver = new btSequentialImpulseConstraintSolver;
	this->world = new btDiscreteDynamicsWorld(this->dispatcher, this->broadphase, this->solver, this->collisionConfig);
	this->world->setGravity(btVector3(0, -2, 0));
	//std::cerr << "Bullet Init" << std::endl;
	return 0;
}

btCollisionObject * BulletWorld::addCollisionObject(glm::mat4 position, glm::vec3 velocityGL, btScalar mass, Model * index)
{
	btConvexHullShape *shape = new btConvexHullShape();
	for (int i = 0; i < index->vertices.size(); i++) {
		//shape->addPoint(btVector3(vertices.data()[i][0], vertices.data()[i][1], vertices.data()[i][2]), true);
		shape->addPoint(btVector3(index->vertices.data()[i].pos.x, index->vertices.data()[i].pos.y, index->vertices.data()[i].pos.z), true);
	}
	btShapeHull *hull = new btShapeHull(shape);
	btScalar m = shape->getMargin();
	hull->buildHull(m);
	delete shape;
	shape = new btConvexHullShape(hull->getVertexPointer()[0], hull->numVertices());
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
	RigidBody->setUserPointer((void*)index);
	this->world->addRigidBody(RigidBody);

	this->shapes.push_back(shape);

	index->setBulletWorld(this->world);
	index->setObj(this->world->getCollisionObjectArray()[this->world->getNumCollisionObjects() - 1]);
	return this->world->getCollisionObjectArray()[this->world->getNumCollisionObjects() - 1];
}

btCollisionObject * BulletWorld::addCollisionObject(glm::mat4 position, glm::vec3 velocityGL, btScalar mass, Model * index, btCollisionShape * shape)
{
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
	RigidBody->setUserPointer((void*)index);
	//RigidBody->setUserIndex2(this->world->getNumCollisionObjects());
	this->world->addRigidBody(RigidBody);
	bool match = false;
	/*for (int i = 0; i < this->shapes.size(); i++) {
		if (shape == this->shapes[i]) {
			match = true;
			break;
		}
	}
	if (!match) {*/
		this->shapes.push_back(shape);
	/*}//delete shape;*/

		index->setBulletWorld(this->world);
		index->setObj(this->world->getCollisionObjectArray()[this->world->getNumCollisionObjects() - 1]);
	return this->world->getCollisionObjectArray()[this->world->getNumCollisionObjects() - 1];
	return nullptr;
}



btCollisionObject * BulletWorld::addGround(glm::mat4 position,Model * index)
{
	std::vector<float> zMap;
	glm::vec3 vertex;
	float maxH = 0;
	float minH = 0;
	float maxW = 0;
	float minW = 0;
	float maxL = 0;
	float minL = 0;
	for (int i = 0; i < index->vertices.size();i++) {
		vertex = index->vertices.data()->pos;
		maxH = (vertex.y > maxH)? vertex.y : maxH;
		maxW = (vertex.x > maxW) ? vertex.x : maxW;
		maxL = (vertex.z > maxL) ? vertex.z : maxL;
		minH = (vertex.y < minH) ? vertex.y : minH;
		minW = (vertex.x < minW) ? vertex.x : minW;
		minL = (vertex.z < minL) ? vertex.z : minL;
		zMap.push_back(vertex.y);
	}

	btCollisionShape *Ground = new btHeightfieldTerrainShape((maxW-minW),(maxL-minL),&zMap[0], 1, minH,maxH,1,PHY_FLOAT,false);

	//btCollisionShape* Ground = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
	btTransform temp;

	temp.setFromOpenGLMatrix(glm::value_ptr(position));
	temp.setOrigin(btVector3(0, (minH + maxH)*0.5f, 0));
	btDefaultMotionState* groundMotionState =
		new btDefaultMotionState(temp);
	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI(0, groundMotionState, Ground, btVector3(0, 0, 0));
	btRigidBody* rb = new btRigidBody(groundRigidBodyCI);
	rb->setUserPointer((void *)index);
	rb->setUserIndex2(this->world->getNumCollisionObjects());
	this->world->addRigidBody(rb);
	index->setBulletWorld(this->world);
	index->setObj(this->world->getCollisionObjectArray()[this->world->getNumCollisionObjects() - 1]);
	//std::cerr << "ground add" << std::endl;
	return this->world->getCollisionObjectArray()[this->world->getNumCollisionObjects() - 1];

}

std::vector<Model*> *BulletWorld::calculate()
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
	std::vector<Model*> *hitted = new std::vector<Model*>;
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
		
		hitted->push_back((Model*)obA->getUserPointer());
		hitted->push_back((Model*)obB->getUserPointer());
	}
	return hitted;
}


BulletWorld::BulletWorld()
{
}


BulletWorld::~BulletWorld()
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
