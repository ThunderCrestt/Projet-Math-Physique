#pragma once
#include "ParticuleLink.h"
class ParticuleRod : public ParticuleLink
{
public :
	float length;
	ParticuleRod(Particule* p1, Particule* p2, float length);
	unsigned addContact(std::vector<ParticuleContact*> *contact, unsigned limit) const;

};

