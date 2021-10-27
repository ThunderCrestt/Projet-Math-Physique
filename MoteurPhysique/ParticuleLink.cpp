#include "ParticuleLink.h"

float ParticuleLink::currentLength() const
{
	Vector3D relativePos = particule[0]->getPosition() - particule[1]->getPosition();
	return relativePos.getNorm();
}

