#pragma once
#include "Vector3D.h"
#include <vector>
#include "Rigidbody.h"
#include "RegistreForceRigidBody.h"
#include "BroadCollisionDetection.h"
#include "NarrowCollisionDetection.h"
#include "BoundingVolumes.h"
#ifndef  RigidBodyManager_h
#define RigidBodyManager_h
class RigidBodyManager
{
private :
	std::vector<RigidBody*> rigidBodies;
	//TODO : remplacer dans le registre la force par une primitive ? car en soit le rigidBody y est contenu
	RegistreForceRigidBody registre;
public :

	//TODO : un vector ou juste une node avec parent qui ont node qui on eux même les nodes
	std::vector<BVHNode<BoundingSphere>> BVHtree;
	RigidBodyManager();
	std::vector<RigidBody*> getRigidBodies();
	void addToRigidBodies(RigidBody& rb);
	void removeFromRigidBodies(RigidBody& rb);
	void integerAllRigidBodies(float duration);
	void addToRegistre(CollisionPrimitive& primitive, ForceGenerator& fg);
	void removeFromRegistre(CollisionPrimitive& primitive, ForceGenerator& fg);
	CollisionPrimitive findPrimitiveInRegistre(RigidBody& rb);
	void startFrame();
	void runPhysic(float duration);
	RegistreForceRigidBody getRegistre();
	unsigned generateContacts();
};

#endif // ! RigidBodyManager
