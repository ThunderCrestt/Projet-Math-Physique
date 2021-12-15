#include "RegistreForceRigidBody.h"
#include "RegistreForces.h"

RegistreForceRigidBody::RegistreForceRigidBody()
{

}

void RegistreForceRigidBody::addToRegistre(CollisionPrimitive& primitive, ForceGenerator& fg)
{
	EnregistrementForceRigidBody ef = EnregistrementForceRigidBody(primitive, fg);
	this->_registre.push_back(ef);
}
void RegistreForceRigidBody::removeFromRegistre(CollisionPrimitive& primitive, ForceGenerator& fg)
{
	EnregistrementForceRigidBody ef = EnregistrementForceRigidBody(primitive, fg);
	this->_registre.erase(std::remove(this->_registre.begin(), this->_registre.end(), ef), this->_registre.end());
}

EnregistrementForceRigidBody RegistreForceRigidBody::getEnregistrementAtPos(int pos)
{
	return this->_registre[pos];
}

RegistreRigidBody RegistreForceRigidBody::getRegistre()
{
	return this->_registre;
}

CollisionPrimitive RegistreForceRigidBody::findPrimitiveInRegistre(RigidBody& rb)
{
	for (auto& elem : _registre)
	{
		if (*elem.primitive->body == rb)
		{
			return *elem.primitive;
		}
	}
}

void RegistreForceRigidBody::clear()
{

}

void RegistreForceRigidBody::updateForces(float duration)
{
	for (auto& elem : this->_registre)
	{
		elem.fg->updateForce(elem.primitive->body, duration);
	}
}
