#include "RigidBodyManager.h"
RigidBodyManager::RigidBodyManager()
{

}
std::vector<RigidBody*> RigidBodyManager::getRigidBodies()
{
	return this->rigidBodies;
}
void RigidBodyManager::addToRigidBodies(RigidBody& rb)
{
	this->rigidBodies.push_back(&rb);
}
void RigidBodyManager::removeFromRigidBodies(RigidBody& rb)
{
	this->rigidBodies.erase(std::remove(this->rigidBodies.begin(), this->rigidBodies.end(), &rb), this->rigidBodies.end());

}
void RigidBodyManager::integerAllRigidBodies(float duration)
{
	/*
	for (auto& elem : this->getRegistry().getRegistre())
	{
		elem.particule->integrer(time);
	}
	*/
}
void RigidBodyManager::startFrame()
{
	//TODO : clear accumulator ?
}

void RigidBodyManager::runPhysic(float duration)
{
	this->startFrame();
	//on update les forces;
	integerAllRigidBodies(duration);
}
