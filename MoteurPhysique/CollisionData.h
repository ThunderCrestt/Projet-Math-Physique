#pragma once
#include "Contact.h"
#include <vector>
using namespace std;

class CollisionData
{
private :
	vector<Contact*> allContacts;
	int contactsRestant;
public : 
	CollisionData();
	void addContact(Contact& contact);
	void removeContact(Contact& contact);
	vector<Contact*> getAllContact();
};

