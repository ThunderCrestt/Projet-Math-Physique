#pragma once
#include "RigidBody.h"
#include "ForceGenerator.h"
#include <vector>
#include "NarrowCollisionDetection.h"
#ifndef REGISTREFORCERIGIDBODY_h
#define REGISTREFORCERIGIDBODY_h


struct EnregistrementForceRigidBody {
	CollisionPrimitive* primitive;
	ForceGenerator* fg;
	EnregistrementForceRigidBody(CollisionPrimitive& _rb, ForceGenerator& _fg)
	{
		primitive = &_rb;
		fg = &_fg;
	}
	bool operator==(const EnregistrementForceRigidBody& ef)
	{
		if (this->primitive == ef.primitive && this->fg == ef.fg)
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
	void addToRegistre(CollisionPrimitive&primitive, ForceGenerator& fg);
	void removeFromRegistre(CollisionPrimitive& primitive, ForceGenerator& fg);
	CollisionPrimitive findPrimitiveInRegistre(RigidBody &rb);
	EnregistrementForceRigidBody getEnregistrementAtPos(int pos);
	RegistreRigidBody getRegistre();
	void clear();
	void updateForces(float duration);
};

#endif // !REGISTREFORCERIGIDBODY_h
