#include "ParticuleFlottaison.h"
ParticuleFlottaison::ParticuleFlottaison(float profondeurMax, float volume, float hauteurEau, float densité)
{
	this->_profondeurMax = profondeurMax;
	this->_volume = volume;
	this->_hauteurEau = hauteurEau;
	this->_densité = densité;
}
void ParticuleFlottaison::updateForce(Particule* particule, float duration)
{
	float profondeur = particule->getPosition().getY();
	// on regarde si on est pas hors de l'eau
	if (profondeur >= _hauteurEau + _profondeurMax) return;
	Vector3D force(0, 0, 0);
	// on va voir si on est pas à la profondeur max
	if (profondeur <= _hauteurEau - _profondeurMax)
	{
		force.setY(_densité * _volume);
		particule->addForce(force);
		return;
	}
	//Sinon on est juste partiellement submergé
	force.setY(_densité * _volume *(profondeur - _profondeurMax - _hauteurEau) / 2 * _profondeurMax);
	particule->addForce(force);
}