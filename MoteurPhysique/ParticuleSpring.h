#pragma once
#include "ForceGenerator.h"
#include "Particule.h"
class ParticuleSpring : public ForceGenerator
{
private:
	//si on veut lier deux particules par un ressort il faut deux générateurs
	Particule* _autreParticule;
	float _constanteRessort;
	float _l0;
public :
	ParticuleSpring(Particule* autreParticule, float constanteRessort, float l0);
	void updateForce(Particule* particule, float duration);

};

