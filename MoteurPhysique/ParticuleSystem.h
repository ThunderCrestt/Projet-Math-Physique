#pragma once
#include <vector>
#include "ParticuleContactResolver.h"
#include "Particule.h"
#include "RegistreForces.h"
#include "ParticuleForceGenerator.h"
#include "ParticuleContactGenerator.h"
#include "SimpleParticuleContactGenerator.h"
class ParticuleWorld
{
	//ajouter les collisions ici 

	private:
		std::vector<Particule*> _allParticules;
		RegistreForces _registre;
	public :
		ParticuleWorld();
		void addParticule(Particule& particule);
		void removeParticule(Particule& particule);
		void addToRegistreForce( Particule &particule, ParticuleForceGenerator &forceGenerator);
		void removeFromRegistreForce(Particule &particule , ParticuleForceGenerator &forceGenerator);
		//compute the next position and velocity of each particule
		void integerAllParticule(float time);
		//return the vector of particules
		RegistreForces  getRegistry();
		unsigned generateContacts();
		void startFrame();
		//calcule les forces et integre les particules
		std::vector<Particule*> getAllParticules();
		void runPhysic(float duration);

		ParticuleContactResolver resolver;

		//contient tous les contact generator
		std::vector<ParticuleContactGenerator*> registreContactGenerator;
		SimpleParticuleContactGenerator simpleContactGenerator;
		//contient tous les contacts
		std::vector <ParticuleContact*> contacts;
		unsigned maxContacts=100;


};

