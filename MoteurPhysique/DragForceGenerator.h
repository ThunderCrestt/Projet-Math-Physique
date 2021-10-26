#pragma once
#include "Particule.h"
#include "ParticuleForceGenerator.h"
class DragForceGenerator : public ParticuleForceGenerator
{
private :
	float _K1;
	float _K2;
public :
	DragForceGenerator(float k1,float k2) :ParticuleForceGenerator()
	{
		_K1 = k1;
		_K2 = k2;
	}
	void updateForce(Particule* particule, float duration);

};

