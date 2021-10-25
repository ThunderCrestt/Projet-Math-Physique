#include "ParticuleAnchoredSpring.h"
ParticuleAnchoredSpring::ParticuleAnchoredSpring(Vector3D *pointAncrage, float k, float l0) : ParticuleForceGenerator()
{
	this->_pointAncrage = pointAncrage;
	this->_constanteRessort = k;
	this->_l0 = l0;
}
void ParticuleAnchoredSpring::updateForce(Particule* particule, float duration)
{

	Vector3D position = particule->getPosition();
	position = position - *_pointAncrage;
	float coeff = abs(position.getNorm() - this->_l0) * this->_constanteRessort;
	position.normalize();
	Vector3D force = position * -coeff;
	particule->addForce(force);


}