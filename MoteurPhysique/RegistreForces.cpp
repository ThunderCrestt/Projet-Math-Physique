#include "RegistreForces.h"
void RegistreForces::addToRegistre(Particule& particule, ParticuleForceGenerator& fg)
{
	EnregistrementForce ef=EnregistrementForce(particule,fg);
	this->_registre.push_back(ef);
}
void RegistreForces::removeFromRegistre(Particule& particule, ParticuleForceGenerator& fg)
{
	EnregistrementForce ef = EnregistrementForce(particule, fg);
	this->_registre.erase(std::remove(this->_registre.begin(), this->_registre.end(), ef), this->_registre.end());
}

EnregistrementForce RegistreForces::getEnregistrementAtPos(int pos)
{
	return this->_registre[pos];
}

Registre* RegistreForces::getRegistre()
{
	return &this->_registre;
}


void RegistreForces::clear()
{

}

void RegistreForces::updateForces(float duration)
{
	for (auto& elem : this->_registre)
	{
		elem.fg->updateForce(elem.particule, duration);
	}
}
