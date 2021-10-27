#include "PlaneSurface2DContactGenerator.h"
#include <iostream>
PlaneSurface2DContactGenerator::PlaneSurface2DContactGenerator(Vector3D leftVector, Vector3D rightVector, std::vector<Particule*>particules, float restitution)
{
	this->leftVector = leftVector;
	this->rightVector = rightVector;
	this->particules = particules;
	this->restitution = restitution;
	this->liaison = leftVector - rightVector;
	//on utilise z et le produit vectoriel pour avoirl la normal
	this->normal = liaison.vectorProduct(Vector3D(0, 0, -0.1));
	this->normal.normalize();
}
unsigned PlaneSurface2DContactGenerator::addContact(std::vector<ParticuleContact*>* contacts) const
{
	unsigned iteration = 0;
	for (auto& elem : particules)
	{
		//si les composantes Y sont égales :
		if (leftVector.getY()==rightVector.getY())
		{
			float distance1 = elem->getPosition().getX() - elem->getRayon() - leftVector.getX();
			float distance2 = elem->getPosition().getX() + elem->getRayon() - leftVector.getX();
			//si la particule est entre les deux composantes x des vecteurs

			if (elem->getPosition().getX() - elem->getRayon()  >= leftVector.getX() && elem->getPosition().getX() + elem->getRayon() <= rightVector.getX())
			{
				//si la particule est en collisions ou non avec la surface
				if (float penetration = elem->getPosition().getY() - elem->getRayon()  <= leftVector.getY())
				{
					contacts->push_back(new ParticuleContact(elem, NULL, restitution, normal, penetration));
					iteration++;
				}
			}
		}	
		//si les composantes X sont égales
		else if (leftVector.getX() == rightVector.getX())
		{
			//si la particule est entre les deux composantes y des vecteurs
			if (elem->getPosition().getY() + elem->getRayon()  <= leftVector.getY() && elem->getPosition().getY() - elem->getRayon() >= rightVector.getY())
			{
				//si la particule est en collisions ou non avec la surface
				if (float penetration = elem->getPosition().getX() - elem->getRayon() <= leftVector.getX())
				{
					contacts->push_back(new ParticuleContact(elem, NULL, restitution, normal, penetration));
				} else 	if (float penetration = elem->getPosition().getX() + elem->getRayon()  >= leftVector.getX())
				{
					contacts->push_back(new ParticuleContact(elem, NULL, restitution, normal, penetration));
				}
			}
		}
		else {
			break;
		}
	}
	return iteration;
}
