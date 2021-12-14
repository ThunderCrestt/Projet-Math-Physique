#include "CollisionData.h"


CollisionData::CollisionData()
{

}

void CollisionData::addContact(Contact& contact)
{
	allContacts.push_back(&contact);
}

void CollisionData::removeContact(Contact& contact)
{
	allContacts.erase(remove(allContacts.begin(), allContacts.end(), &contact), allContacts.end());
}

vector<Contact*> CollisionData::getAllContact()
{
	return allContacts;
}
