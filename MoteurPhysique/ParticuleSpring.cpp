#include "ParticuleSpring.h"
ParticuleSpring::ParticuleSpring(Particule* autreParticule, float constanteRessort, float l0): ParticuleForceGenerator()
{
	this->_autreParticule = autreParticule;
	this->_constanteRessort = constanteRessort;
	this->_l0 = l0;
}
void ParticuleSpring::updateForce(Particule* particule, float duration)
{
	Vector3D position = particule->getPosition();
	position = position - this->_autreParticule->getPosition();
	float coeff= abs(position.getNorm() - this->_l0) * this->_constanteRessort;
	position.normalize();
	Vector3D force = position * -coeff;
	particule->addForce(force);
}