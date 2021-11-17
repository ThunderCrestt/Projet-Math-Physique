#pragma once
#include "Particule.h"
#include "ParticuleContact.h"
#include "ParticuleContactGenerator.h"
class ParticuleLink : public ParticuleContactGenerator
{
private :
	

public :
	virtual unsigned addContact(std::vector<ParticuleContact*>* contacts) const = 0;

	float currentLength() const;

	Particule* particule[2];

};

