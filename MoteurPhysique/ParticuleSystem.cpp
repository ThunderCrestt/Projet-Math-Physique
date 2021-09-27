#include "ParticuleSystem.h"

ParticuleSystem::ParticuleSystem()
{
	this->_allParticules = std::vector<Particule*>();
}

void ParticuleSystem::addParticule(Particule& particule)
{
	_allParticules.push_back(&particule);
}

void ParticuleSystem::integerAllParticule(float time)
{
	//maybe compute the time pass between each frame here or before the call of this function.
	for (auto& elem : _allParticules)
	{
		elem->integrer(time);
	}
}

std::vector<Particule*> ParticuleSystem::getAllParticules()
{
	return _allParticules;
}
Particule* ParticuleSystem::getParticuleAtPos(int pos)
{
	return (_allParticules[pos]);
}