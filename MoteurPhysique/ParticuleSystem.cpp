#include "ParticuleSystem.h"

ParticuleSystem::ParticuleSystem() : resolver(resolver)
{
	this->_registre =RegistreForces();
	this->resolver = ParticuleContactResolver(0);
	this->contacts =  std::vector<ParticuleContact*>();
	this->registreContactGenerator = std::vector<ParticuleContactGenerator*>();
	//un simple générateur de contact entre les particules en plus des cables
	this->simpleContactGenerator = SimpleParticuleContactGenerator(maxContacts, getAllParticules());
}
std::vector<Particule*> ParticuleSystem::getAllParticules()
{
	/*
	std::vector<Particule*> particules = std::vector<Particule*>();
	for (auto& elem : this->getRegistry().getRegistre())
	{
		particules.push_back(elem.particule);
	}
	*/
	return _allParticules;
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
	unsigned used = simpleContactGenerator.addContact(&contacts);
	//a voir si la boucle for auto fonctionne
	for (int i = 0; i < registreContactGenerator.size(); i++)
	{
		 used += registreContactGenerator[i]->addContact(&contacts);
	}

	return used;
}

void ParticuleSystem::addToRegistreForce(Particule& particule, ParticuleForceGenerator &forceGenerator)
{
	_registre.addToRegistre(particule, forceGenerator);
}

void ParticuleSystem::removeFromRegistreForce(Particule& particule, ParticuleForceGenerator &forceGenerator)
{
	_registre.removeFromRegistre(particule, forceGenerator);
}

void ParticuleSystem::addParticule(Particule& particule)
{
	_allParticules.push_back(&particule);
}

void ParticuleSystem::removeParticule(Particule& particule)
{
	_allParticules.erase(std::remove(_allParticules.begin(), _allParticules.end(), &particule), _allParticules.end());
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
	/*
for (int i = 0; i < contacts.size(); i++)
{
	delete contacts[i];
}
*/
	//on update les forces
	this->getRegistry().updateForces(duration);

	//on intègre les particules avec les forces résultantes, puis on clear les forces
	this->integerAllParticule(duration);

	//on génère les contacts
	unsigned usedContacts = generateContacts();

	//on les résout
	resolver.setIterations(usedContacts * 2);
	resolver.resolveContacts(contacts, usedContacts, duration);
	contacts.clear();

}