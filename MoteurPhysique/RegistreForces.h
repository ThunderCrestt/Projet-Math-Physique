#pragma once
#include "Particule.h"
#include "ParticuleForceGenerator.h"
#include <vector>



struct EnregistrementForce {
	Particule* particule;
	ParticuleForceGenerator* fg;
	EnregistrementForce(Particule& _particule, ParticuleForceGenerator& _fg)
	{
		particule = &_particule;
		fg = &_fg;
	}
	bool operator==(const EnregistrementForce& ef)
	{
		if (this->particule == ef.particule && this->fg == ef.fg)
		{
			return true;
		}
		else { return false; }
	}
};

typedef std::vector<EnregistrementForce> Registre;
class RegistreForces
{

private :
	Registre _registre;
public:
	RegistreForces(){}
	void addToRegistre(Particule &particule, ParticuleForceGenerator &fg);
	void removeFromRegistre(Particule& particule, ParticuleForceGenerator& fg);
	EnregistrementForce getEnregistrementAtPos(int pos);
	Registre getRegistre();
	void clear();
	void updateForces(float duration);
};

