#include "ParticuleSystem.h"

ParticuleSystem::ParticuleSystem() : resolver(resolver)
{
	this->_registre =RegistreForces();
	this->resolver = ParticuleContactResolver(0);
}

void ParticuleSystem::startFrame()
{
	for (auto& elem : this->getRegistry().getRegistre())
	{
		elem.particule->clearAccumulator();
	}
}
unsigned ParticuleSystem::generateContacts()
{
	unsigned limit = maxContacts;
	ParticuleContact* nextContact = contacts;
	RegistreDeContacts* reg = firstContactGen;
	while (reg)
	{
		unsigned used = reg->generateur->addContact(nextContact, limit);
		limit -= used;
		nextContact += used;
		// We�ve run out of contacts to fill. This means we�re missing
		// contacts.
		if (limit <= 0) break;
		reg = reg->next;
	}
	// Return the number of contacts used.
	return maxContacts - limit;
}

void ParticuleSystem::addToRegistreForce(Particule& particule, ParticuleForceGenerator &forceGenerator)
{
	_registre.addToRegistre(particule, forceGenerator);
}

void ParticuleSystem::removeFromRegistreForce(Particule& particule, ParticuleForceGenerator &forceGenerator)
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
	unsigned usedContacts = generateContacts();

	//on les r�sout
	resolver.setIterations(usedContacts * 2);
	resolver.resolveContacts(contacts, usedContacts, duration);
}