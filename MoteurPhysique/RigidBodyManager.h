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
public :
	RigidBodyManager();
	std::vector<RigidBody*> getRigidBodies();
	void addToRigidBodies(RigidBody& rb);
	void removeFromRigidBodies(RigidBody& rb);
	void integerAllRigidBodies(float duration);
	void startFrame();
	void runPhysic(float duration);

};

#endif // ! RigidBodyManager
