#pragma once
#include "Particule.h"
#include "Rigidbody.h"
class ForceGenerator
{
private :

public :
	ForceGenerator() {}
	virtual void updateForce(Particule* particule, float duration) = 0;
	virtual void updateForce(RigidBody* rb, float duration) = 0;

	virtual ~ForceGenerator(void) = default;
};

