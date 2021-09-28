#pragma once
#include <vector>
#include "Particule.h"
class ParticuleSystem
{
	private:
		std::vector<Particule*> _allParticules;
	public :
		ParticuleSystem();
		//add a particule(particule) to the particule system
		void addParticule( Particule &particule);
		//remove a particule(particule) from the particule system
		void removeParticule(Particule& particule);
		//compute the next position and velocity of each particule
		void integerAllParticule(float time);
		//return the vector of particules
		std::vector<Particule*> getAllParticules();
		//get a particular particule in the vector
		Particule* getParticuleAtPos(int pos);
};

