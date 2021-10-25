#pragma once
#include "Particule.h"
class ParticuleForceGenerator
{
private :

public :
	ParticuleForceGenerator() {}
	virtual void updateForce(Particule* particule, float duration) = 0;
	virtual ~ParticuleForceGenerator(void) = default;
};

