#include "DragForceGenerator.h"
void DragForceGenerator::updateForce(Particule* particule, float duration) {
	Vector3D velocity= particule->getVelocity(); 
	//On calcule le coef de drag
	float coeff =velocity.getNorm();
	coeff = this->_K1 * coeff + this->_K2 * coeff * coeff;
	// On Calcul la force finale et on l'ajoute à la particule
	velocity.normalize();
	Vector3D force = velocity * -coeff;
	particule->addForce(force);
}
