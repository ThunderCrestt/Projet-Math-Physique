#include "ParticuleContact.h"

ParticuleContact::ParticuleContact(Particule* p1, Particule* p2, float restitution, Vector3D contactNormal, float penetration)
{
	this->particules[0] = p1;
	this->particules[1] = p2;
	this->restitution = restitution;
	this->contactNormal = contactNormal;
	this->penetration = penetration;
}
void ParticuleContact::resolve(float duration)
{
resolveVelocity(duration);
resolveInterpenetration(duration);

}
float ParticuleContact::calculerVs() const
{
	Vector3D relativeVelocity = particules[0]->getVelocity();
	if (particules[1]) relativeVelocity = relativeVelocity- particules[1]->getVelocity();
	return relativeVelocity.scalarProduct(contactNormal);
}
void ParticuleContact::resolveVelocity(float duration)
{
	//on calculVs
	float vs = calculerVs();
	//On regarde si ça vaut le coup de résoudre
	if (vs > 0)
	{
		//pas d'impulsions requises
		return;
	}
	// On calcule le nouveau Vs
	float newVs = -vs * restitution;
	//pour contact au repos
	Vector3D accCausedVelocity = particules[0]->getAcceleration();
	if (particules[1]) accCausedVelocity = accCausedVelocity- particules[1]->getAcceleration();

	float accCausedSepVelocity = accCausedVelocity.scalarProduct(contactNormal * duration);
	// If we’ve got a closing velocity due to acceleration build-up,
	// remove it from the new separating velocity.
	if (accCausedSepVelocity < 0)
	{
		newVs += restitution * accCausedSepVelocity;
		// Make sure we haven’t removed more than was
		// there to remove.
		if (newVs < 0) newVs = 0;
	}

	float deltaSpeed = newVs - vs;
	// on applique la vitesse en fonction de la masse de la particule
	float totalInverseMass = particules[0]->getInversMass();
	if (particules[1]) totalInverseMass += particules[1]->getInversMass();
	// si toute les masses on une masses à 0, pas d'impulsion
	if (totalInverseMass <= 0) return;
	//On calcule l'impulsion
	float impulse = deltaSpeed / totalInverseMass;
	Vector3D impulsionParMass = contactNormal * impulse;
	//on applique les  impulsions 
	particules[0]->setVelocity(particules[0]->getVelocity() +impulsionParMass * particules[0]->getInversMass());
	if (particules[1])
	{
		// Particle 1 goes in the opposite direction.
		particules[1]->setVelocity(particules[1]->getVelocity() +impulsionParMass * -particules[1]->getInversMass());
	}


}

void ParticuleContact::resolveInterpenetration(float duration)
{
	//si y a pas de pénétration on return
	if (penetration <= 0) return;
	// le mouvement de chaque objet dépends de sa masse donc on voit si les objets on une masse
		float totalInverseMass = particules[0]->getInversMass();
	if (particules[1]) totalInverseMass += particules[1]->getInversMass();
	// si pas de masse on return
	if (totalInverseMass <= 0) return;
	Vector3D movePerIMass = contactNormal *(-penetration / totalInverseMass);
	//On résout l'interpenetration
	particules[0]->setPosition(particules[0]->getPosition() +
		movePerIMass * particules[0]->getInversMass());
	if (particules[1])
	{
		particules[1]->setPosition(particules[1]->getPosition() +
			movePerIMass * particules[1]->getInversMass());
	}
}

bool ParticuleContact::operator==(const ParticuleContact c)
{
	if ((c.particules[0] == particules[0] && c.particules[1] == particules[1]) ||       //Si le contact pointe vers deux particules identiques
		(c.particules[0] == particules[1] && c.particules[1] == particules[0]))         //dans n'importe quel ordre, alors il est identique
		return true;
	else return false;
}