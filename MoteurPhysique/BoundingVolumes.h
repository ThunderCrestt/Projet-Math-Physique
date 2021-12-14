#pragma once
#include "Vector3D.h"
class BoundingSphere
{	
	public :
	float radius;
	Vector3D center;
	/**
	* Creates a new bounding sphere at the given center and radius.
	*/
	BoundingSphere(const Vector3D& center, float radius);

	/**
	* Creates a bounding sphere to enclose the two given bounding
	* spheres.
	*/

	BoundingSphere( BoundingSphere& one,  BoundingSphere& two);
	/**
	* Checks if the bounding sphere overlaps with the other given
	* bounding sphere.
	*/

	bool overlaps(const BoundingSphere* other);
};


