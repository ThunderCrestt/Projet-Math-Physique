#include "ParticuleRod.h"
ParticuleRod::ParticuleRod(Particule* p1, Particule* p2, float length)
{
	this->particule[0] = p1;
	this->particule[1] = p2;
	this->length = length;
}

unsigned ParticuleRod::addContact(std::vector<ParticuleContact*>* contact) const
{
	// Find the length of the rod.
	float penetration;
	float currentLen = currentLength();
		// Check whether we’re overextended.
		if (currentLen == length)
		{
			return 0;
		}
	// Otherwise return the contact.
	// Calculate the normal.
	Vector3D normal = particule[1]->getPosition() - particule[0]
		->getPosition();
	normal.normalize();
	// The contact normal depends on whether we’re extending
	// or compressing.
	if (currentLen > length) {
		
		penetration = currentLen - length;
	}
	else {
		normal = normal * -1;
		penetration = length - currentLen;
	}
	// Always use zero restitution (no bounciness).
	float restitution = 0;
	contact->push_back(new ParticuleContact(particule[0], particule[1], restitution, normal, penetration));
	return 1;
}
