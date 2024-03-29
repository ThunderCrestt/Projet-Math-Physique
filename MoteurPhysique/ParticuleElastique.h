#pragma once
#include "ForceGenerator.h"
class ParticuleElastique : public ForceGenerator
{
private:
	//si on veut lier deux particules par un ressort il faut deux générateurs
	Particule* _autreParticule;
	float _constanteRessort;
	float _l0;
public:
	ParticuleElastique(Particule* autreParticule, float constanteRessort, float l0);
	void updateForce(Particule* particule, float duration) override;

};

