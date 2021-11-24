#pragma once
#include "Vector3D.h"
#include "ForceGenerator.h"
#include "Rigidbody.h"
class GravityForceGenerator : public ForceGenerator
{
private : 
	Vector3D _gravity;
public:
	GravityForceGenerator(Vector3D gravity) : ForceGenerator()
	{
		this->_gravity = gravity;
	}

	void updateForce(Particule* particule, float duration);
	void updateForce(RigidBody* rb, float duration);
};

