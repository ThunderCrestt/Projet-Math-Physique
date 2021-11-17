#pragma once
#include "Particule.h"
#include "Vector3D.h"
class ParticuleContact
{
public:
	ParticuleContact(Particule* p1, Particule* p2, float restitution, Vector3D contactNormal, float penetration);

	Particule* particules[2];

	float restitution;

	Vector3D contactNormal;
	float penetration;
	void resolve(float duration);
	float calculerVs() const;
	bool operator==(const ParticuleContact c);

private:
	void resolveVelocity(float duration);
	void resolveInterpenetration(float duration);

};

