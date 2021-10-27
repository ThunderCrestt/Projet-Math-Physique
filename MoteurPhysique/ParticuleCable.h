#pragma once
#include "ParticuleLink.h"
class ParticuleCable: public ParticuleLink
{
public:
	float maxLength;
	float restitution;
	ParticuleCable(Particule* p1, Particule* p2,float maxLength, float restitution);
	virtual unsigned addContact(std::vector<ParticuleContact*>*contacts) const;
};

