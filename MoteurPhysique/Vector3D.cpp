#include "Vector3D.h"

float Vector3D::getX()
{
	return this->_x;
}

float Vector3D::getY()
{
	return this->_y;
}


float Vector3D::getZ()
{
	return this->_z;
}

void Vector3D::setX(float x)
{
	this->_x = x;
}

void Vector3D::setY(float y)
{
	this->_y = y;
}

void Vector3D::setZ(float z)
{
	this->_z = z;
}
float Vector3D::getNorm()
{
	return sqrt(pow(getX(),2) + pow(getY(),2) + pow(getZ(),2));
}

float Vector3D::getSquareNorm()
{
	return pow(getX(), 2) + pow(getY(), 2) + pow(getZ(), 2);
}

void Vector3D::normalize()
{
	setX(getX() / getNorm());
	setY(getY() / getNorm());
	setZ(getZ() / getNorm());

}


Vector3D Vector3D::multiplyByScalar(float scalar)
{
	multiply_X_ByScalar(scalar);
	multiply_Y_ByScalar(scalar);
	multiply_Z_ByScalar(scalar);
	return *this;
}

Vector3D Vector3D::addToVector(Vector3D toAdd)
{
	setX(getX() + toAdd.getX());
	setX(getY() + toAdd.getY());
	setX(getZ() + toAdd.getZ());
	return *this;

}

Vector3D Vector3D::toSubstractToVector(Vector3D toSubstract)
{
	setX(getX() - toSubstract.getX());
	setX(getY() - toSubstract.getY());
	setX(getZ() - toSubstract.getZ());
	return *this;
}

void Vector3D::multiply_X_ByScalar(float scalar)
{
	setX(getX() * scalar);
}

void Vector3D::multiply_Y_ByScalar(float scalar)
{
	setY(getY() * scalar);
}

void Vector3D::multiply_Z_ByScalar(float scalar)
{
	setZ(getZ() * scalar);
}

Vector3D Vector3D::composantProduct(Vector3D vector)
{
	return Vector3D(getX() * vector.getX(), getY() * vector.getY(), getZ() * vector.getZ());
}

float Vector3D::scalarProduct(Vector3D vector)
{
	return getX() * vector.getX() + getY() * vector.getY() + getZ() * vector.getZ();
}

Vector3D Vector3D::vectorProduct(Vector3D vector)
{
	float x= getY() * vector.getZ() - getZ() * vector.getY();
	float y= getZ() * vector.getX() - getX() * vector.getZ();
	float z= getX() * vector.getY() - getY() * vector.getX();
	return Vector3D(x,y,z);
}