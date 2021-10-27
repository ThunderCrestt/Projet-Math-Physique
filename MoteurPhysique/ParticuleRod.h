#pragma once
#include "ParticuleLink.h"
class ParticuleRod : public ParticuleLink
{
public :
	float length;

	virtual unsigned fillContact(ParticuleContact* contact, unsigned limit) const;

};

