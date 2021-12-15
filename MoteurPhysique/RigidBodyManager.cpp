#include "RigidBodyManager.h"
RigidBodyManager::RigidBodyManager()
{
	this->registre = RegistreForceRigidBody();
}
std::vector<RigidBody*> RigidBodyManager::getRigidBodies()
{
	return this->rigidBodies;
}

RegistreForceRigidBody RigidBodyManager::getRegistre()
{
	return this->registre;
}

void RigidBodyManager::addToRigidBodies(RigidBody& rb)
{
	this->rigidBodies.push_back(&rb);
}
void RigidBodyManager::removeFromRigidBodies(RigidBody& rb)
{
	this->rigidBodies.erase(std::remove(this->rigidBodies.begin(), this->rigidBodies.end(), &rb), this->rigidBodies.end());

}


void RigidBodyManager::addToRegistre(RigidBody& rb, ForceGenerator& fg)
{
	registre.addToRegistre(rb, fg);

}
void RigidBodyManager::removeFromRegistre(RigidBody& rb, ForceGenerator& fg)
{
	registre.removeFromRegistre(rb, fg);
}

void RigidBodyManager::integerAllRigidBodies(float duration)
{
	
	for (auto& elem : this->getRegistre().getRegistre())
	{
		elem.rb->integrer(duration);
	}
	
	
}
void RigidBodyManager::startFrame()
{
	//TODO : clear accumulator ?
	//TODO : insérer ici les boundingVolume et BVH ?
}

void RigidBodyManager::runPhysic(float duration)
{
	this->startFrame();
	//on update les forces;
	this->getRegistre().updateForces(duration);
	integerAllRigidBodies(duration);
	//TODO : comment on insère un BVHnode ?
	//TODO : call broadPhase -> doit donner tous les contacts potentiels avec getPotentialContact
	//TODO : call narrowPhase -> doit créer et utiliser la collisionData -> quelle résolution appelé ?
	//TODO : if Collisions return true and pause the game
}
