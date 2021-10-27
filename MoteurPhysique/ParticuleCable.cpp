#include "ParticuleCable.h"

ParticuleCable::ParticuleCable(Particule* p1, Particule* p2, float maxLength, float restitution)
{
	this->particule[0] = p1;
	this->particule[1] = p2;
	this->maxLength = maxLength;
	this->restitution = restitution;
}

unsigned ParticuleCable::addContact(std::vector<ParticuleContact*>* contact) const
{
	float length = currentLength();
	if (length < maxLength)
	{
		return 0;
	}
	Vector3D normal = particule[1]->getPosition() - particule[0]->getPosition();
	normal.normalize();
	float penetration = length - maxLength;
	contact->push_back(new ParticuleContact(particule[0], particule[1], restitution, normal, penetration));
	return 1;
}