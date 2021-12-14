#pragma once
#include "Rigidbody.h"
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
template<class BoundingVolumeClass>
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
	BoundingVolumeClass volume;
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
	unsigned getPotentialContactsWith(const BVHNode<BoundingVolumeClass>* other, PotentialContact* contacts, unsigned limit) const;
	bool overlaps(const BVHNode<BoundingVolumeClass>* other) const;
	void insert(RigidBody* newBody, const BoundingVolumeClass& newVolume);
	void recalculateBoundingVolume();
	~BVHNode();

};
