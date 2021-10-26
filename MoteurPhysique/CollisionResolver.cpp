#include "CollisionResolver.h"

CollisionResolver::CollisionResolver()
{
}

void CollisionResolver::ResolveCollision(Particule par)
{
	Vector3D invParSpeed = Vector3D(!par.getSpeed().getX(), !par.getSpeed().getY(), !par.getSpeed().getZ());
	
	par.setSpeed(invParSpeed);
}
