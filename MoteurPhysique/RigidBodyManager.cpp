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


void RigidBodyManager::addToRegistre(CollisionPrimitive& primitive, ForceGenerator& fg)
{
	registre.addToRegistre(primitive, fg);

}
void RigidBodyManager::removeFromRegistre(CollisionPrimitive& primitive, ForceGenerator& fg)
{
	registre.removeFromRegistre(primitive, fg);
}

CollisionPrimitive RigidBodyManager::findPrimitiveInRegistre(RigidBody& rb)
{
	return registre.findPrimitiveInRegistre(rb);
}


void RigidBodyManager::integerAllRigidBodies(float duration)
{
	
	for (auto& elem : this->getRegistre().getRegistre())
	{
		elem.primitive->body->integrer(duration);
	}
	
	
}

unsigned  RigidBodyManager::generateContacts()
{
	//must choose wich function from collisionDetector to call
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
	if (sizeof(pContact->body)>0)
	{
		//avec les rigidBody trouvé dans le contact potentiel on cherche les primitives correspondant
		//dans une liste de primitive
		CollisionPrimitive prim1 = findPrimitiveInRegistre(*pContact->body[0]);
		CollisionPrimitive prim2 = findPrimitiveInRegistre(*pContact->body[1]);
		collisionData->friction = 0;
		collisionData->restitution = 1;
		//TODO : generateContact(prim1,prim2,collisionData);
	}
	else {
		return;
	}
	//TODO : ici soit créer un collisionData à remplir avec seulement friction et restitution de set à 0 et 1 soit dans le setBodyData de la narrowDetection enlever les data.friction
	//TODO : on appelle une fonction qui vient choisir quel type de collision c'est en fonction des deux primitives ( shpere and sphere ..) et rempli le collisionData
	//TODO : if CollisionsData est non vide return true and pause the game
}
