#pragma once
#include <cmath>
class Vector3D
{
private :
	float _x;
	float _y;
	float _z;
public :
	Vector3D(float x=0., float y=0., float z=0.) :_x(x), _y(y), _z(z) {
	};
	float getX(void) const;
	float getY(void) const;
	float getZ(void) const;
	void setX(float x);
	void setY(float y);
	void setZ(float z);

	float getNorm(void);
	float getSquareNorm(void);

	void normalize(void); //we put the coordonates on the norm of the vector
	Vector3D multiplyByScalarAndApplyResult(float scalar);
	Vector3D addToThisVectorAndApplyResult(const Vector3D &toAdd);
	Vector3D toSubstractToVectorAndApplyResult(const Vector3D &toSubstract);
	Vector3D multiplyByScalar(float scalar);
	Vector3D addToVector(const Vector3D &toAdd);
	Vector3D substractToVector(const Vector3D &toSubstract);

	void multiply_X_ByScalar(float scalar);
	void multiply_Y_ByScalar(float scalar);
	void multiply_Z_ByScalar(float scalar);

	Vector3D composantProduct(const Vector3D &vector);
	float scalarProduct(const Vector3D &vector);
	Vector3D vectorProduct(const Vector3D &vector);

	Vector3D operator+(const Vector3D &toAdd)
	{
		return this->addToVector(toAdd);
	}

	Vector3D operator*(const float scalar)
	{
		return this->multiplyByScalar(scalar);
	}
};

