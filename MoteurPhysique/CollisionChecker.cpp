#include "CollisionChecker.h"

CollisionChecker::CollisionChecker()
{
}

bool CollisionChecker::Collision(Particule par, Particule par2, float circ1, float circ2)
{
	/*bool colX = par.getPosition().getX() == par2.getPosition().getX();
	bool colY = par.getPosition().getY() == par2.getPosition().getY();
	bool colZ = par.getPosition().getZ() == par2.getPosition().getZ();*/
	bool colX = par.getPosition().getX() + circ1 == par2.getPosition().getX() + circ2 || par.getPosition().getX() + circ1 >= par2.getPosition().getX()+circ2 || par.getPosition().getX() + circ1 <= par2.getPosition().getX()+circ2;
	bool colY = par.getPosition().getY() + circ1 == par2.getPosition().getY() + circ2 || par.getPosition().getY() + circ1 >= par2.getPosition().getY() + circ2 || par.getPosition().getY() + circ1 <= par2.getPosition().getY() + circ2;
	bool colZ = par.getPosition().getZ() + circ1 == par2.getPosition().getZ() + circ2 || par.getPosition().getZ() + circ1 >= par2.getPosition().getZ() + circ2 || par.getPosition().getZ() + circ1 <= par2.getPosition().getZ() + circ2;

	return colX && colY && colZ;
}
