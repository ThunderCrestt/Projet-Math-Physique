#include "ParticuleAnchoredSpring.h"
ParticuleAnchoredSpring::ParticuleAnchoredSpring(Vector3D *pointAncrage, float k, float l0) : ParticuleForceGenerator()
{
	this->_pointAncrage = pointAncrage;
	this->_constanteRessort = k;
	this->_l0 = l0;
}
void ParticuleAnchoredSpring::updateForce(Particule* particule, float duration)
{
	//ajouté update position en cas de caméra ?

	Vector3D position = particule->getPosition();
	//on calcule la différence de position entre le point d'ancrage et la position de la particule
	position = position - *_pointAncrage;
	//on calcule la norme de la force 
	float magnitude = abs(position.getNorm() - this->_l0) * this->_constanteRessort;
	position.normalize();
	//on applique la direction à la magnitude calculé
	Vector3D force = position * -magnitude;
	//on ajoute la force à la somme totale des forces de la particule
	particule->addForce(force);


}