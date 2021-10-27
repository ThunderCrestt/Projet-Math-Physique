#include "ParticuleSystem.h"

ParticuleWorld::ParticuleWorld() : resolver(resolver)
{
	this->_registre =RegistreForces();
	this->resolver = ParticuleContactResolver(0);
	this->contacts =  std::vector<ParticuleContact*>();
	this->registreContactGenerator = std::vector<ParticuleContactGenerator*>();
	//un simple g�n�rateur de contact entre les particules en plus des cables
	//on suppose que toutes les particules ont le m�me rayon
	this->simpleContactGenerator = SimpleParticuleContactGenerator(0.03, getAllParticules());
}
std::vector<Particule*> ParticuleWorld::getAllParticules()
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
//juste des choses qui doivent �tre fait � chaque d�but de frame
void ParticuleWorld::startFrame()
{
	this->simpleContactGenerator.setParticules(getAllParticules());

	for (auto& elem : this->getRegistry().getRegistre())
	{
		elem.particule->clearAccumulator();
	}
}

//ici on g�n�re tous les contacts en fonction des contacts ajout� dans registreContactGenerator ainsi que les diff�rents simpleContactGenerator qui permettent juste de v�rifier les collisons entre les particules
unsigned ParticuleWorld::generateContacts()
{
	unsigned used = simpleContactGenerator.addContact(&contacts);
	for (int i = 0; i < registreContactGenerator.size(); i++)
	{
		 used += registreContactGenerator[i]->addContact(&contacts);
	}

	return used;
}

//fonctions d'ajout et de retrait dans les registre de force
void ParticuleWorld::addToRegistreForce(Particule& particule, ParticuleForceGenerator &forceGenerator)
{
	_registre.addToRegistre(particule, forceGenerator);
}

void ParticuleWorld::removeFromRegistreForce(Particule& particule, ParticuleForceGenerator &forceGenerator)
{
	_registre.removeFromRegistre(particule, forceGenerator);
}


//fonction pour ajouter des particules � l'environnement
void ParticuleWorld::addParticule(Particule& particule)
{
	_allParticules.push_back(&particule);
}

void ParticuleWorld::removeParticule(Particule& particule)
{
	_allParticules.erase(std::remove(_allParticules.begin(), _allParticules.end(), &particule), _allParticules.end());
}

void ParticuleWorld::integerAllParticule(float time)
{
	//maybe compute the time pass between each frame here or before the call of this function.

	for (auto& elem : this->getRegistry().getRegistre())
	{
		elem.particule->integrer(time);
	}
	
}

RegistreForces ParticuleWorld::getRegistry()
{
	return _registre;
}

void ParticuleWorld::runPhysic(float duration)
{
	//on update les forces
	this->startFrame();
	this->getRegistry().updateForces(duration);

	//on int�gre les particules avec les forces r�sultantes, puis on clear les forces
	this->integerAllParticule(duration);

	//on g�n�re les contacts
	unsigned usedContacts = generateContacts();

	//on les r�sout
	resolver.setIterations(usedContacts * 2);
	resolver.resolveContacts(contacts, usedContacts, duration);
	//on clear tous les contacts
	contacts.clear();

}