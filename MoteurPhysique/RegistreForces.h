#pragma once
#include "Particule.h"
#include "ForceGenerator.h"
#include <vector>



struct EnregistrementForce {
	Particule* particule;
	ForceGenerator* fg;
	EnregistrementForce(Particule& _particule, ForceGenerator& _fg)
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
public:
	Registre _registre;
	RegistreForces(){}
	void addToRegistre(Particule &particule, ForceGenerator &fg);
	void removeFromRegistre(Particule& particule, ForceGenerator& fg);
	EnregistrementForce getEnregistrementAtPos(int pos);
	Registre getRegistre();
	void clear();
	void updateForces(float duration);
};

