#include "RegistreForceRigidBody.h"
#include "RegistreForces.h"

RegistreForceRigidBody::RegistreForceRigidBody()
{

}

void RegistreForceRigidBody::addToRegistre(RigidBody& rb, ForceGenerator& fg)
{
	EnregistrementForceRigidBody ef = EnregistrementForceRigidBody(rb, fg);
	this->_registre.push_back(ef);
}
void RegistreForceRigidBody::removeFromRegistre(RigidBody& rb, ForceGenerator& fg)
{
	EnregistrementForceRigidBody ef = EnregistrementForceRigidBody(rb, fg);
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


void RegistreForceRigidBody::clear()
{

}

void RegistreForceRigidBody::updateForces(float duration)
{
	for (auto& elem : this->_registre)
	{
		elem.fg->updateForce(elem.rb, duration);
	}
}
