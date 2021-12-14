#pragma once
#include "Primitive.h"
#include "Vector3D.h"
class Plane : public Primitive
{
private:
	Vector3D normal;
	float offset;
public:
};

