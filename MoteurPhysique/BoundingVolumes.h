#pragma once
#ifndef  BOUNDINGVOLUMES_H
#define BOUNDINGVOLUMES_H


#include "Vector3D.h"

class BoundingVolumeClass
{
public:

	virtual float getSize();
	virtual bool overlaps(const BoundingVolumeClass* other);
	virtual void calculateNewBoundingVolume(const BoundingVolumeClass& one, const  BoundingVolumeClass& two);
};


//TODO : peut être faire un boundingBox pour les murs
class BoundingSphere 
{	
	public :
		Vector3D center;
		float radius;
	/**
	* Creates a new bounding sphere at the given center and radius.
	*/
	BoundingSphere(const Vector3D& center, float radius);

	/**
	* Creates a bounding sphere to enclose the two given bounding
	* spheres.
	*/

	BoundingSphere(const BoundingSphere& one, const  BoundingSphere& two);
	void calculateNewBoundingVolume(const BoundingSphere& one, const  BoundingSphere& two);

	/**
	* Checks if the bounding sphere overlaps with the other given
	* bounding sphere.
	*/

	bool overlaps(const BoundingSphere* other);
	float getGrowth(const BoundingSphere& other) const;
	float getSize();
};


#endif // ! BOUNDINGVOLUMES_H
