#pragma once
#include "Vector3D.h"
#include <vector>
#include "Rigidbody.h"
#ifndef  RigidBodyManager_h
#define RigidBodyManager_h

class RigidBodyManager
{
private :
	std::vector<RigidBody*> rigidBodies;

};

#endif // ! RigidBodyManager
