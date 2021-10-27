#include "ParticuleCable.h"

unsigned ParticuleCable::fillContact(ParticuleContact* contact, unsigned limit) const
{
	float length = currentLength();
	if (length < maxLength)
	{
		return 0;
	}

	contact->particules[0] = particule[0];
	contact->particules[1] = particule[1];

	Vector3D normal = particule[1]->getPosition() - particule[0]->getPosition();
	normal.normalize();
	contact->contactNormal = normal;

	contact->penetration = length - maxLength;
	contact->restitution = restitution;

	return 1;
}