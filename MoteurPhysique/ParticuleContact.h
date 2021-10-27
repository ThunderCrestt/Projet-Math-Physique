#pragma once
#include "Particule.h"
#include "Vector3D.h"
class ParticuleContact
{
public:

	Particule* particules[2];

	float restitution;

	Vector3D contactNormal;
	float penetration;
	void resolve(float duration);
	float calculerVs() const;

private:
	void resolveVelocity(float duration);
	void resolveInterpenetration(float duration);
};
