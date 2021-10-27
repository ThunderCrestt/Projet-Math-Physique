#pragma once
#include "ParticuleLink.h"
class ParticuleCable: public ParticuleLink
{
public:
	float maxLength;
	float restitution;

	virtual unsigned fillContact(ParticuleContact* contact, unsigned limit) const;
};

