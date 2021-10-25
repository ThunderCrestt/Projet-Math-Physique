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
	position = position - this->_autreParticule->getPosition();
	float norm = position.getNorm();
	if (norm <= _l0) return;
	
	float coeff =(this->_l0-position.getNorm()) * this->_constanteRessort;
	position.normalize();
	Vector3D force = position * -coeff;
	particule->addForce(force);
	
}