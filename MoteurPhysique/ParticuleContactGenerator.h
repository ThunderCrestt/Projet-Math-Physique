#pragma once
#include "ParticuleContact.h"
#include <vector>
class ParticuleContactGenerator
{
public:
	/**
	* Fills the given contact structure with the generated
	* contact. The contact pointer should point to the first
	* available contact in a contact array, where limit is the
	* maximum number of contacts in the array that can be written
	* to. The method returns the number of contacts that have
	* been written.
	*/
	//on rempli le contact qu'on passe, ici un tableau.
	virtual unsigned addContact(std::vector<ParticuleContact*>* contacts) const = 0;
};

