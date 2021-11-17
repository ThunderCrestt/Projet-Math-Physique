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
	
	float vs = calculerVs();
	float newVs = vs * (restitution);

	float g;
	if (particules[1] != nullptr) {    //Si on a définit une seconde particule, on l'utilise pour calculer k et on change sa velocité

		g= newVs / (particules[0]->getInversMass() + particules[1]->getInversMass());
		particules[1]->setVelocity(particules[1]->getVelocity() +  contactNormal*g * particules[1]->getInversMass());
	}
	else {      //Sinon on calcule k en considérant l'objet de contact comme ayant une vitesse nulle et une masse inversée nulle (=masse infinie)
		g = newVs / (particules[0]->getInversMass());
	}
	//Et dans tout les cas on change la vélocité de la première particule
	particules[0]->setVelocity(particules[0]->getVelocity() - contactNormal*g * particules[0]->getInversMass());
	
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
	Vector3D movePerIMass = contactNormal *(-penetration / totalInverseMass) * 0.01;
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