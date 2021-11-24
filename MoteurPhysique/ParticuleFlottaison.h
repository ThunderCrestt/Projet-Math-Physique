#pragma once
#include "ForceGenerator.h"
#include "Vector3D.h"
class ParticuleFlottaison : public ForceGenerator
{
private:
	float _profondeurMax;
	float _volume;
	float _hauteurEau;
	float _densit�;

public:
	ParticuleFlottaison(float profondeurMax,float volume,float hauteurEau,float densit�);
	void updateForce(Particule* particule, float duration);
};

