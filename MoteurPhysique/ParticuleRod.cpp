#include "ParticuleRod.h"

unsigned ParticuleRod::fillContact(ParticuleContact* contact, unsigned limit) const
{
	float currentLen = currentLength();
	if (currentLen == length)
	{
		return 0;
	}
	contact->particules[0] = particule[0];
	contact->particules[1] = particule[1];

	Vector3D normal = particule[1]->getPosition() - particule[0]->getPosition();
	normal.normalize();

	if (currentLen > length) {
		contact->contactNormal = normal;
		contact->penetration = currentLen - length;
	}
	else {
		contact->contactNormal = normal;
		contact->penetration = length - currentLen;
	}

	contact->restitution = 0;

	return 1;
}