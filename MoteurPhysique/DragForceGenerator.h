#pragma once
#include "Particule.h"
#include "ForceGenerator.h"
#include "Rigidbody.h"
class DragForceGenerator : public ForceGenerator
{
private :
	float _K1;
	float _K2;
public :
	DragForceGenerator(float k1,float k2) :ForceGenerator()
	{
		_K1 = k1;
		_K2 = k2;
	}
	void updateForce(Particule* particule, float duration);
	void updateForce(RigidBody* body, float duration);


};

