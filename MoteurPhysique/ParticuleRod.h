#pragma once
#include "ParticuleLink.h"
class ParticuleRod : public ParticuleLink
{
public :
	float length;

	unsigned addContact(std::vector<ParticuleContact*> contact, unsigned limit) const;

};

