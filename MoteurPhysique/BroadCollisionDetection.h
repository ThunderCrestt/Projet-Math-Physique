#pragma once
#include "Rigidbody.h"
#include "BoundingVolumes.h"
/**
* Stores a potential contact to check later.
*/
struct PotentialContact
{
	/**
	* Holds the bodies that might be in contact.
	*/
	RigidBody* body[2];
};
/**
* A base class for nodes in a bounding volume hierarchy.
*
* This class uses a binary tree to store the bounding
* volumes.
*/
template <class boundingVolume>
class BVHNode
{
public:
	/**
	* Holds the child nodes of this node.
	*/
	BVHNode* children[2];
	BVHNode* parent;
	/**
	* Holds a single bounding volume encompassing all the
	* descendents of this node.
	*/
	boundingVolume *volume;
	/**
	* Holds the rigid body at this node of the hierarchy.
	* Only leaf nodes can have a rigid body defined (see isLeaf).
	* Note that it is possible to rewrite the algorithms in this
	* class to handle objects at all levels of the hierarchy,
	* but the code provided ignores this vector unless firstChild
	* is NULL.
	*/
	RigidBody* body;

	bool isLeaf() const
	{
		return (body != NULL);
	}
	/**
	* Checks the potential contacts from this node downward in
	* the hierarchy, writing them to the given array (up to the
	* given limit). Returns the number of potential contacts it
	* found.
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
	// If we don’t have a parent, then we ignore the sibling processing.
	if (parent)
	{
		// Find our sibling.
		BVHNode* sibling;
		if (parent->children[0] == this) sibling = parent->children[1];
		else sibling = parent->children[0];
		// Write its data to our parent.
		parent->volume = sibling->volume;
		parent->body = sibling->body;
		parent->children[0] = sibling->children[0];
		parent->children[1] = sibling->children[1];
		// Delete the sibling (we blank its parent and
		// children to avoid processing/deleting them).
		sibling->parent = NULL;
		sibling->body = NULL;
		sibling->children[0] = NULL;
		sibling->children[1] = NULL;
		delete sibling;
		// Recalculate the parent’s bounding volume.
		parent->recalculateBoundingVolume(true);
	}
	// Delete our children (again we remove their parent data so
	// we don’t try to process their siblings as they are deleted).
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
	// Early out if we don’t have the room for contacts, or
	// if we’re a leaf node.
	if (isLeaf() || limit == 0) return 0;
	// Get the potential contacts of one of our children with
	// the other.
	return children[0]->getPotentialContactsWith(
		children[1], contacts, limit
	);
}
template <class boundingVolume>
unsigned BVHNode<boundingVolume>::getPotentialContactsWith(const BVHNode<boundingVolume>* other, PotentialContact* contacts, unsigned limit) const
{
	// Early-out if we don’t overlap or if we have no room
	// to report contacts.
	if (!overlaps(other) || limit == 0) return 0;
	// If we’re both at leaf nodes, then we have a potential contact.
	if (isLeaf() && other->isLeaf())
	{
		contacts->body[0] = body;
		contacts->body[1] = other->body;
		return 1;
	}
	// Determine which node to descend into. If either is
	// a leaf, then we descend the other. If both are branches,
	// then we use the one with the largest size.
	if (other->isLeaf() ||
		(!isLeaf() && volume->getSize() >= other->volume->getSize()))
	{
		// Recurse into ourself.
		unsigned count = children[0]->getPotentialContactsWith(
			other, contacts, limit
		);
		// Check whether we have enough slots to do the other side too.
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
		// Recurse into the other node.
		unsigned count = getPotentialContactsWith(
			other->children[0], contacts, limit
		);
		// Check whether we have enough slots to do the other side too.
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

	// Use the bounding volume combining constructor.
	volume->calculateNewBoundingVolume(*children[0]->volume,*children[1]->volume);
	//volume = BoundingVolumeClass(
	//	children[0]->volume,
	//	children[1]->volume
	//);

	// Recurse up the tree
	if (parent) parent->recalculateBoundingVolume(true);
}
template <class boundingVolume>

void BVHNode<boundingVolume>::insert(RigidBody* newBody, const BoundingVolumeClass& newVolume)
{
	// If we don't have a parent, then we ignore the sibling
	// processing
	if (parent)
	{
		// Find our sibling
		BVHNode* sibling;
		if (parent->children[0] == this) sibling = parent->children[1];
		else sibling = parent->children[0];

		// Write its data to our parent
		parent->volume = sibling->volume;
		parent->body = sibling->body;
		parent->children[0] = sibling->children[0];
		parent->children[1] = sibling->children[1];

		// Delete the sibling (we blank its parent and
		// children to avoid processing/deleting them)
		sibling->parent = NULL;
		sibling->body = NULL;
		sibling->children[0] = NULL;
		sibling->children[1] = NULL;
		delete sibling;

		// Recalculate the parent's bounding volume
		parent->recalculateBoundingVolume(true);
	}

	// Delete our children (again we remove their
	// parent data so we don't try to process their siblings
	// as they are deleted).
	if (children[0]) {
		children[0]->parent = NULL;
		delete children[0];
	}
	if (children[1]) {
		children[1]->parent = NULL;
		delete children[1];
	}
}