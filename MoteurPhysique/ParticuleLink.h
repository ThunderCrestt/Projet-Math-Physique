#pragma once
#include "Particule.h"
#include "ParticuleContact.h"
class ParticuleLink
{
private :
	

public :
	virtual unsigned fillContact(ParticuleContact* contact, unsigned limit) const = 0;

	float currentLength() const;

	Particule* particule[2];

};

