#include "ParticuleSpring.h"
ParticuleSpring::ParticuleSpring(Particule* autreParticule, float constanteRessort, float l0): ForceGenerator()
{
	this->_autreParticule = autreParticule;
	this->_constanteRessort = constanteRessort;
	this->_l0 = l0;
}
void ParticuleSpring::updateForce(Particule* particule, float duration)
{
	Vector3D position = particule->getPosition();
	//on calcule la différence entre les deux positions des particules
	position = position - this->_autreParticule->getPosition();
	//on calcule la norme de la force 
	float magnitude= abs(position.getNorm() - this->_l0) * this->_constanteRessort;
	position.normalize();
	//on applique la direction à la magnitude calculé
	Vector3D force = position * -magnitude;
	//on ajoute la force à la somme totale des forces de la particule
	particule->addForce(force);
}