#pragma once
#include "Vector3D.h"
#include "ParticuleForceGenerator.h"
#include "Rigidbody.h"
class GravityForceGenerator : public ParticuleForceGenerator
{
private : 
	Vector3D _gravity;
public:
	GravityForceGenerator(Vector3D gravity) : ParticuleForceGenerator()
	{
		this->_gravity = gravity;
	}

	void updateForce(Particule* particule, float duration);
	void updateForce(RigidBody* rb, float duration);
};

