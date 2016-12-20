// bullet_Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "btBulletDynamicsCommon.h"

int main()
{
	btCollisionShape *shape= new btSphereShape((btScalar(1.)));
	delete shape;
    return 0;
}

