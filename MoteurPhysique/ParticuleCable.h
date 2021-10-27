#pragma once
#include "ParticuleLink.h"
class ParticuleCable: public ParticuleLink
{
public:
	float maxLength;
	float restitution;

	virtual unsigned addContact(std::vector<ParticuleContact*>, unsigned limit) const;
};

