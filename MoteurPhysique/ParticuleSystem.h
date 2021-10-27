#pragma once
#include <vector>
#include "ParticuleContactResolver.h"
#include "Particule.h"
#include "RegistreForces.h"
#include "ParticuleForceGenerator.h"
#include "ParticuleContactGenerator.h"
class ParticuleSystem
{
	//ajouter les collisions ici 

	private:
		//std::vector<Particule*> _allParticules;
		RegistreForces _registre;
	public :
		ParticuleSystem();
		//add a particule(particule) to the particule system
		void addToRegistreForce( Particule &particule, ParticuleForceGenerator &forceGenerator);
		//remove a particule(particule) from the particule system
		void removeFromRegistreForce(Particule &particule , ParticuleForceGenerator &forceGenerator);
		//compute the next position and velocity of each particule
		void integerAllParticule(float time);
		//return the vector of particules
		RegistreForces  getRegistry();
		unsigned generateContacts();
		void startFrame();

		//calcule les forces et integre les particules
		void runPhysic(float duration);

		ParticuleContactResolver resolver;

		struct RegistreDeContacts
		{
			ParticuleContactGenerator* generateur;
			RegistreDeContacts* next;
		};
		RegistreDeContacts* firstContactGen;
		ParticuleContact* contacts;
		unsigned maxContacts;


};

