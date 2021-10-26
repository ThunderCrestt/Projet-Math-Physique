#pragma once
#include "ParticuleForceGenerator.h"
#include "Vector3D.h"
class ParticuleFlottaison : public ParticuleForceGenerator
{
private:
	float _profondeurMax;
	float _volume;
	float _hauteurEau;
	float _densité;

public:
	ParticuleFlottaison(float profondeurMax,float volume,float hauteurEau,float densité);
	void updateForce(Particule* particule, float duration);
};

