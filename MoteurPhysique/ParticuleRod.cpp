#include "ParticuleRod.h"
ParticuleRod::ParticuleRod(Particule* p1, Particule* p2, float length)
{
	this->particule[0] = p1;
	this->particule[1] = p2;
	this->length = length;
}

unsigned ParticuleRod::addContact(std::vector<ParticuleContact*>* contact) const
{
	float penetration;
	float currentLen = currentLength();
		// on regarde si on est pas surétendu
		if (currentLen == length)
		{
			return 0;
		}
	// calcul de la normale
	Vector3D normal = particule[1]->getPosition() - particule[0]
		->getPosition();
	normal.normalize();
	// la normale dépends de si la tige est compréssé ou étendu
	if (currentLen > length) {
		
		penetration = currentLen - length;
	}
	else {
		normal = normal * -1;
		penetration = length - currentLen;
	}
	// pas d'élasticité
	float restitution = 0;
	contact->push_back(new ParticuleContact(particule[0], particule[1], restitution, normal, penetration));
	return 1;
}
