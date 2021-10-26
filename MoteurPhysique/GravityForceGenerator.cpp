#include "GravityForceGenerator.h"
void GravityForceGenerator::updateForce(Particule* particule, float duration)
{
		if (particule->getMass()==0) return;
		// on applique la force en fonction de la masse de la particule
		particule->addForce(this->_gravity * particule->getMass());
}
