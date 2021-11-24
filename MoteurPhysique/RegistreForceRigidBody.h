#pragma once
#include "RigidBody.h"
#include "ForceGenerator.h"
#include <vector>

#ifndef REGISTREFORCERIGIDBODY_h
#define REGISTREFORCERIGIDBODY_h


struct EnregistrementForceRigidBody {
	RigidBody* rb;
	ForceGenerator* fg;
	EnregistrementForceRigidBody(RigidBody& _rb, ForceGenerator& _fg)
	{
		rb = &_rb;
		fg = &_fg;
	}
	bool operator==(const EnregistrementForceRigidBody& ef)
	{
		if (this->rb == ef.rb && this->fg == ef.fg)
		{
			return true;
		}
		else { return false; }
	}
};

typedef std::vector<EnregistrementForceRigidBody> RegistreRigidBody;

class RegistreForceRigidBody
{

private:
public:
	RegistreRigidBody _registre;
	RegistreForceRigidBody();
	void addToRegistre(RigidBody &rb, ForceGenerator& fg);
	void removeFromRegistre(RigidBody& rb, ForceGenerator& fg);
	EnregistrementForceRigidBody getEnregistrementAtPos(int pos);
	RegistreRigidBody getRegistre();
	void clear();
	void updateForces(float duration);
};

#endif // !REGISTREFORCERIGIDBODY_h
