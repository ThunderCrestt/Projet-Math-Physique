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


//TODO : peut �tre faire un boundingBox pour les murs
class BoundingSphere 
{	
	public :
		Vector3D center;
		float radius;
	/**
	* Cr�er un boundingVolume en forme de sph�re au centrer center et de rayon radius
	*/
	BoundingSphere(const Vector3D& center, float radius);

	/**
	* Cr�er une boundingSphere comprennant les deux boundingSphere pass�
	*/

	BoundingSphere(const BoundingSphere& one, const  BoundingSphere& two);
	void calculateNewBoundingVolume(const BoundingSphere& one, const  BoundingSphere& two);

	/**
	* V�rifie la superposition des deux sph�res
	*/
	bool overlaps(const BoundingSphere* other);
	float getGrowth(const BoundingSphere& other) const;
	float getSize();
};


#endif // ! BOUNDINGVOLUMES_H
