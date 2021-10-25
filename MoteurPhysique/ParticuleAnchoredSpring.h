#pragma once
#include "ParticuleForceGenerator.h"
#include "Vector3D.h"
class ParticuleAnchoredSpring : public ParticuleForceGenerator
{
private :
	Vector3D *_pointAncrage;
	float _constanteRessort;
	float _l0;
public :
	ParticuleAnchoredSpring(Vector3D *pointAncrage, float k, float l0);
	void updateForce(Particule* particule, float duration);

};

