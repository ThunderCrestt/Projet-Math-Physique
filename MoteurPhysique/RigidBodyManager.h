#pragma once
#include "Vector3D.h"
#include <vector>
#include "Rigidbody.h"
#include "RegistreForceRigidBody.h"

#ifndef  RigidBodyManager_h
#define RigidBodyManager_h

class RigidBodyManager
{
private :
	std::vector<RigidBody*> rigidBodies;
	RegistreForceRigidBody registre;
public :
	RigidBodyManager();
	std::vector<RigidBody*> getRigidBodies();
	void addToRigidBodies(RigidBody& rb);
	void removeFromRigidBodies(RigidBody& rb);
	void integerAllRigidBodies(float duration);
	void addToRegistre(RigidBody& rb, ForceGenerator& fg);
	void removeFromRegistre(RigidBody& rb, ForceGenerator& fg);

	void startFrame();
	void runPhysic(float duration);
	RegistreForceRigidBody getRegistre();

};

#endif // ! RigidBodyManager
