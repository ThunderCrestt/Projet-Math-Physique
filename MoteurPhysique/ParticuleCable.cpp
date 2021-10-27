#include "ParticuleCable.h"

unsigned ParticuleCable::addContact(std::vector<ParticuleContact*> contact, unsigned limit) const
{
	float length = currentLength();
	if (length < maxLength)
	{
		return 0;
	}
	Vector3D normal = particule[1]->getPosition() - particule[0]->getPosition();
	normal.normalize();
	float penetration = length - maxLength;
	contact.push_back(new ParticuleContact(particule[0], particule[1], restitution, normal, penetration));
	return 1;
}