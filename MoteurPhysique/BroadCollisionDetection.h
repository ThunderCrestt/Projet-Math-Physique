#pragma once
#include "Rigidbody.h"
#include "BoundingVolumes.h"
/**
* Contient les contacts potentiels
*/
struct PotentialContact
{
	/**
	* contient les deux rigiBody potentiellement en contact
	*/
	RigidBody* body[2];
};
/**
* une classe décrivant les noeud d'un BVH 
*/
template <class boundingVolume>
class BVHNode
{
public:
	/**
	* Contient les enfants du ce noeud pour un maximum de deux comme conseiller dans le livre de ian Millington
	*/
	BVHNode* children[2];
	BVHNode* parent;
	/**
	* Contient un boundingVOlume
	*/
	boundingVolume *volume;
	/**
	* Contient le rigidBody du noeud, seules les feuilles de l'arbre peuvent avoir un body
	*/
	RigidBody* body;

	bool isLeaf() const
	{
		return (body != NULL);
	}
	/**
	* trouve les contacts potentiels
	*/
	unsigned getPotentialContacts(PotentialContact* contacts,unsigned limit) const;
	unsigned getPotentialContactsWith(const BVHNode<boundingVolume>* other, PotentialContact* contacts, unsigned limit) const;
	bool overlaps(const BVHNode* other) const;
	void insert(RigidBody* newBody, const BoundingVolumeClass& newVolume);
	void recalculateBoundingVolume(bool recurse);
	~BVHNode();

};
template <class boundingVolume>
bool BVHNode<boundingVolume>::overlaps(const BVHNode* other) const
{
	return volume->overlaps(other->volume);
}


template <class boundingVolume>
BVHNode<boundingVolume>::~BVHNode()
{
	//Si le noeud n'a pas de parent,  pas besoin de chercher de noeud soeurs
	if (parent)
	{
		// trouver le noeud soeur
		BVHNode* sibling;
		if (parent->children[0] == this) sibling = parent->children[1];
		else sibling = parent->children[0];
		// écrire les données
		parent->volume = sibling->volume;
		parent->body = sibling->body;
		parent->children[0] = sibling->children[0];
		parent->children[1] = sibling->children[1];

		//On supprime le noeud soeur
		//et on rend vide les parents et les enfants pour éviter de les rappeler
		sibling->parent = NULL;
		sibling->body = NULL;
		sibling->children[0] = NULL;
		sibling->children[1] = NULL;
		delete sibling;
		// on reclacul le boundingVolume
		parent->recalculateBoundingVolume(true);
	}
	//On supprime le noeud enfant et on rend null le noeud parent
	if (children[0]) {
		children[0]->parent = NULL;
		delete children[0];
	}
	if (children[1]) {
		children[1]->parent = NULL;
		delete children[0];
	}
}
//retourne les contacts potentiels à partir des noeuds du BVH
template <class boundingVolume>
unsigned BVHNode<boundingVolume>::getPotentialContacts(PotentialContact* contacts, unsigned limit) const
{

	if (isLeaf() || limit == 0) return 0;
	// Récupère les contact potentiels entre les deux enfants.
	return children[0]->getPotentialContactsWith(
		children[1], contacts, limit
	);
}
template <class boundingVolume>
unsigned BVHNode<boundingVolume>::getPotentialContactsWith(const BVHNode<boundingVolume>* other, PotentialContact* contacts, unsigned limit) const
{

	if (!overlaps(other) || limit == 0) return 0;
	if (isLeaf() && other->isLeaf())
	{
		contacts->body[0] = body;
		contacts->body[1] = other->body;
		return 1;
	}
	//on détermine ou déscendre en fonction de si c'est une branche ou une feuille, dans le cas d'une branche on prendra la plus grande
	if (other->isLeaf() ||
		(!isLeaf() && volume->getSize() >= other->volume->getSize()))
	{
		//appel récursif
		unsigned count = children[0]->getPotentialContactsWith(
			other, contacts, limit
		);
		//On vérifie qu'on peut vérifier l'autre côté
		if (limit > count) {
			return count + children[1]->getPotentialContactsWith(
				other, contacts + count, limit - count
			);
		}
		else {
			return count;
		}
	}
	else
	{
		//appel récursif sur l'autre noeud
		unsigned count = getPotentialContactsWith(
			other->children[0], contacts, limit
		);
		//On vérifie qu'on peut vérifier l'autre côté
		if (limit > count) {
			return count + getPotentialContactsWith(
				other->children[1], contacts + count, limit - count
			);
		}
		else {
			return count;
		}
	}
}
template <class boundingVolume>

void BVHNode<boundingVolume>::recalculateBoundingVolume(bool recurse)
{
	if (isLeaf()) return;

	volume->calculateNewBoundingVolume(*children[0]->volume,*children[1]->volume);
	//volume = BoundingVolumeClass(
	//	children[0]->volume,
	//	children[1]->volume
	//);

	if (parent) parent->recalculateBoundingVolume(true);
}
template <class boundingVolume>

void BVHNode<boundingVolume>::insert(RigidBody* newBody, const BoundingVolumeClass& newVolume)
{
	// si pas de parent, pas de noeud soeurs à trouver
	if (parent)
	{
		// trouver le noeud soeur
		BVHNode* sibling;
		if (parent->children[0] == this) sibling = parent->children[1];
		else sibling = parent->children[0];

		//écritures des données
		parent->volume = sibling->volume;
		parent->body = sibling->body;
		parent->children[0] = sibling->children[0];
		parent->children[1] = sibling->children[1];

		//On supprime le noeud soeur
		//et on rend vide les parents et les enfants pour éviter de les rappeler
		sibling->parent = NULL;
		sibling->body = NULL;
		sibling->children[0] = NULL;
		sibling->children[1] = NULL;
		delete sibling;

		//On calcul le nouveau bounding volume
		parent->recalculateBoundingVolume(true);
	}

	//On supprime le noeud soeur
	//et on rend vide les parents et les enfants pour éviter de les rappeler
	if (children[0]) {
		children[0]->parent = NULL;
		delete children[0];
	}
	if (children[1]) {
		children[1]->parent = NULL;
		delete children[1];
	}
}