#include "ParticuleSystem.h"

ParticuleSystem::ParticuleSystem()
{
	this->_registre =RegistreForces();
}

void ParticuleSystem::addParticule(Particule& particule, ParticuleForceGenerator &forceGenerator)
{
	_registre.addToRegistre(particule, forceGenerator);
}

void ParticuleSystem::removeParticule(Particule& particule, ParticuleForceGenerator &forceGenerator)
{
	_registre.removeFromRegistre(particule, forceGenerator);
}


void ParticuleSystem::integerAllParticule(float time)
{
	//maybe compute the time pass between each frame here or before the call of this function.
	for (auto& elem : this->getRegistry().getRegistre())
	{
		elem.particule->integrer(time);
	}
	
}

RegistreForces ParticuleSystem::getRegistry()
{
	return _registre;
}

void ParticuleSystem::runPhysic(float duration)
{

	//on update les forces
	this->getRegistry().updateForces(duration);

	//on int�gre les particules avec les forces r�sultantes, puis on clear les forces
	this->integerAllParticule(duration);

	//on g�n�re les contacts

	//on les r�sout
}