#include "BoundingVolumes.h"


BoundingSphere::BoundingSphere(const Vector3D& center, float radius)
{
	this->center = center;
	this->radius = radius;
}



BoundingSphere::BoundingSphere(const BoundingSphere& one,const BoundingSphere& two)
{
    Vector3D center1 = one.center;
    Vector3D center2 = two.center;
    Vector3D centreOffset = center1 - center2;
    float distance = centreOffset.getSquareNorm();
    float radiusDiff = two.radius - one.radius;

    // Check if the larger sphere encloses the small one
    if (radiusDiff * radiusDiff >= distance)
    {
        if (one.radius > two.radius)
        {
            center = one.center;
            radius = one.radius;
        }
        else
        {
            center = two.center;
            radius = two.radius;
        }
    }

    // Otherwise we need to work with partially
    // overlapping spheres
    else
    {
        distance = sqrt(distance);
        radius = (distance + one.radius + two.radius) * ((float)0.5f);

        // The new centre is based on one's centre, moved towards
        // two's centre by an ammount proportional to the spheres'
        // radii.
        center = one.center;
        if (distance > 0)
        {
            center =center+ centreOffset * ((radius - one.radius) / distance);
        }
    }
}

bool BoundingSphere::overlaps(const BoundingSphere* other)
{
	float distanceSquared = (center - other->center).getSquareNorm(); // or norm ?
	return distanceSquared < (radius + other->radius)*
		(radius + other->radius);
}

float BoundingSphere::getGrowth(const BoundingSphere& other) const
{
    BoundingSphere newSphere= BoundingSphere(*this, other);

    // We return a value proportional to the change in surface
    // area of the sphere.
    return newSphere.radius * newSphere.radius - radius * radius;
}

float BoundingSphere::getSize()
{
    return (4 / 3) * 3.141592653 * pow(this->radius, 3);
}

void BoundingSphere::calculateNewBoundingVolume(const BoundingSphere& one, const  BoundingSphere& two)
{
    Vector3D center1 = one.center;
    Vector3D center2 = two.center;
    Vector3D centreOffset = center1 - center2;
    float distance = centreOffset.getSquareNorm();
    float radiusDiff = two.radius - one.radius;

    // Check if the larger sphere encloses the small one
    if (radiusDiff * radiusDiff >= distance)
    {
        if (one.radius > two.radius)
        {
            center = one.center;
            radius = one.radius;
        }
        else
        {
            center = two.center;
            radius = two.radius;
        }
    }

    // Otherwise we need to work with partially
    // overlapping spheres
    else
    {
        distance = sqrt(distance);
        radius = (distance + one.radius + two.radius) * ((float)0.5f);

        // The new centre is based on one's centre, moved towards
        // two's centre by an ammount proportional to the spheres'
        // radii.
        center = one.center;
        if (distance > 0)
        {
            center = center + centreOffset * ((radius - one.radius) / distance);
        }
    }
}
