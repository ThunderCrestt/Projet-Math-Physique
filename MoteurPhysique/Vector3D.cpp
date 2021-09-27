#include "Vector3D.h"

float Vector3D::getX() const
{
	return this->_x;
}

float Vector3D::getY() const
{
	return this->_y;
}


float Vector3D::getZ() const
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


Vector3D Vector3D::multiplyByScalarAndApplyResult(float scalar)
{
	multiply_X_ByScalar(scalar);
	multiply_Y_ByScalar(scalar);
	multiply_Z_ByScalar(scalar);
	return *this;
}

Vector3D Vector3D::addToThisVectorAndApplyResult(const Vector3D &toAdd)
{
	setX(getX() + toAdd.getX());
	setX(getY() + toAdd.getY());
	setX(getZ() + toAdd.getZ());
	return *this;

}

Vector3D Vector3D::toSubstractToVectorAndApplyResult(const Vector3D &toSubstract)
{
	setX(getX() - toSubstract.getX());
	setX(getY() - toSubstract.getY());
	setX(getZ() - toSubstract.getZ());
	return *this;
}

Vector3D Vector3D::multiplyByScalar(float scalar)
{
	Vector3D result = Vector3D(scalar * getX(), scalar * getY(), scalar * getZ());
	return result;
}

Vector3D Vector3D::addToVector(const Vector3D &toAdd)
{
	Vector3D result = Vector3D(this->getX() + toAdd.getX(), this->getY()+toAdd.getY(), this->getZ() + toAdd.getZ());
	return result;
}

Vector3D Vector3D::substractToVector(const Vector3D &toSubstract)
{
	Vector3D result = Vector3D(this->getX() - toSubstract.getX(), this->getY() - toSubstract.getY(), this->getZ() - toSubstract.getZ());
	return result;
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

Vector3D Vector3D::composantProduct(const Vector3D &vector)
{
	return Vector3D(getX() * vector.getX(), getY() * vector.getY(), getZ() * vector.getZ());
}

float Vector3D::scalarProduct(const Vector3D &vector)
{
	return getX() * vector.getX() + getY() * vector.getY() + getZ() * vector.getZ();
}

Vector3D Vector3D::vectorProduct(const Vector3D &vector)
{
	float x= getY() * vector.getZ() - getZ() * vector.getY();
	float y= getZ() * vector.getX() - getX() * vector.getZ();
	float z= getX() * vector.getY() - getY() * vector.getX();
	return Vector3D(x,y,z);
}