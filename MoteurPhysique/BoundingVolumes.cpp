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

    // Est ce que la grand sphère contient la petite ?
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

    //sinon on travail avec des shpères qui se superposent partiellement
    else
    {
        distance = sqrt(distance);
        radius = (distance + one.radius + two.radius) * ((float)0.5f);

        // le nouveau centre est le centre de one décaler vers le centre de two d'une certaine distance
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

    // On retourne une valeur proportionnel à la surface de la sphère
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

    // On regarde si la grande sphère comprends la petite
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

    //sinon on travail avec des shpères qui se superposent partiellement

    else
    {
        distance = sqrt(distance);
        radius = (distance + one.radius + two.radius) * ((float)0.5f);

        // le nouveau centre est le centre de one décaler vers le centre de two d'une certaine distance
        center = one.center;
        if (distance > 0)
        {
            center = center + centreOffset * ((radius - one.radius) / distance);
        }
    }
}
