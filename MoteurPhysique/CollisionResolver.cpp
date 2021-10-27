#include "CollisionResolver.h"

CollisionResolver::CollisionResolver()
{
}

void CollisionResolver::ResolveCollision(Particule par)
{
	Vector3D invParSpeed = Vector3D(!par.getVelocity().getX(), !par.getVelocity().getY(), !par.getVelocity().getZ());
	
	par.setVelocity(invParSpeed);
}
