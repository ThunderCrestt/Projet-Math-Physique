#include "BoundingVolumes.h"


BoundingSphere::BoundingSphere(const Vector3D& center, float radius)
{
	this->center = center;
	this->radius = radius;
}



BoundingSphere::BoundingSphere( BoundingSphere& one,  BoundingSphere& two)
{
	this->radius = (one.radius + two.radius + (one.center - two.center).getNorm()) / 2;
	Vector3D line = two.center - one.center;
	this->center = one.center;
}

bool BoundingSphere::overlaps(const BoundingSphere* other)
{
	float distanceSquared = (center - other->center).getSquareNorm(); // or norm ?
	return distanceSquared < (radius + other->radius)*
		(radius + other->radius);
}
