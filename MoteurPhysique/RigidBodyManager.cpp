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

unsigned  RigidBodyManager::generateContacts()
{
	//unsigned limit = maxContacts;
	//Contact* nextContact = contacts;

	//ContactGenRegistration* reg = firstContactGen;
	//while (reg)
	//{
	//	unsigned used = reg->gen->addContact(nextContact, limit);
	//	limit -= used;
	//	nextContact += used;

	//	// We've run out of contacts to fill. This means we're missing
	//	// contacts.
	//	if (limit <= 0) break;

	//	reg = reg->next;
	//}

	//// Return the number of contacts used.
	//return maxContacts - limit;
	return 0;
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
	unsigned int limit = 5;
	CollisionData *collisionData = new CollisionData();
	PotentialContact* pContact = new PotentialContact();
	//TODO : comment on insère un BVHnode ?
	//à faire pour tout le bvh si jamais ça le fais pas la
	// call broadPhase -> doit donner tous les contacts potentiels avec getPotentialContact on obtient des potentialContact avec les deux rigiBody potentiellement en contact
	BVHtree[0].getPotentialContacts(pContact,limit);
	//TODO : ici soit créer un collisionData à remplir avec seulement friction et restitution de set à 0 et 1 soit dans le setBodyData de la narrowDetection enlever les data.friction
	//TODO: avec les rigidBody on cherche les primitives correspondant dans une liste de primitive ( ou liste de primitive lié à un contact generator ?)
	//TODO : on appelle une fonction qui vient choisir quel type de collision c'est en fonction des deux primitives ( shpere and sphere ..) et rempli le collisionData
	//TODO : if CollisionsData est non vide return true and pause the game
}
