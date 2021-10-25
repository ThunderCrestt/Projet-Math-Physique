#include "ParticuleElastique.h"
ParticuleElastique::ParticuleElastique(Particule* autreParticule, float constanteRessort, float l0) : ParticuleForceGenerator()
{
	this->_autreParticule = autreParticule;
	this->_constanteRessort = constanteRessort;
	this->_l0 = l0;
}
void ParticuleElastique::updateForce(Particule* particule, float duration)
{
	Vector3D position = particule->getPosition();
	//on calcule la différence entre les deux positions des particules
	position = position - this->_autreParticule->getPosition();
	float norm = position.getNorm();
	if (norm <= _l0) { return; }

	//on calcule la norme de la force 
	float coeff =(this->_l0-norm) * this->_constanteRessort;
	position.normalize();
	//on applique la direction à la magnitude calculé
	Vector3D force = position * -coeff;
	//on ajoute la force à la somme totale des forces de la particule
	particule->addForce(force);
	
}