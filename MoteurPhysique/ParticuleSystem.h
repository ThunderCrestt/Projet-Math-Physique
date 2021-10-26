#pragma once
#include <vector>
#include "Particule.h"
#include "RegistreForces.h"
#include "ParticuleForceGenerator.h"
class ParticuleSystem
{
	//ajouter les collisions ici 

	private:
		//std::vector<Particule*> _allParticules;
		RegistreForces _registre;
	public :
		ParticuleSystem();
		//add a particule(particule) to the particule system
		void addParticule( Particule &particule, ParticuleForceGenerator &forceGenerator);
		//remove a particule(particule) from the particule system
		void removeParticule(Particule &particule , ParticuleForceGenerator &forceGenerator);
		//compute the next position and velocity of each particule
		void integerAllParticule(float time);
		//return the vector of particules
		RegistreForces  getRegistry();

		//calcule les forces et integre les particules
		void runPhysic(float duration);
};

