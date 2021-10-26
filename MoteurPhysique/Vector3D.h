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
	//get the X coordinate of the vector
	float getX(void) const;
	//get the Y coordinate of the vector
	float getY(void) const;
	//get the Z coordinate of the vector
	float getZ(void) const;
	//set the X coordinate of the vector
	void setX(float x);
	//set the Y coordinate of the vector
	void setY(float y);
	//set the Z coordinate of the vector
	void setZ(float z);

	//set the vector to 0,0,0
	void clear()
	{
		setX(0);
		setY(0);
		setZ(0);
	}

	//get the norm of the vector
	float getNorm(void);
	//get the square norm of the vector
	float getSquareNorm(void);

	//normalize the vector
	void normalize(void); //we put the coordonates on the norm of the vector
	//multiply this vector by a float(scalar) and apply the result to this vector
	Vector3D multiplyByScalarAndApplyResult(float scalar);
	//add this vector to another vector(toAdd) and apply the result to this vector
	Vector3D addToThisVectorAndApplyResult(const Vector3D &toAdd);
	//substract this vector by another vector(toSubstract) and apply the result to this vector
	Vector3D toSubstractToVectorAndApplyResult(const Vector3D &toSubstract);
	//multiply this vector by a float
	Vector3D multiplyByScalar(float scalar);
	//add this vector to another vector(toAdd)
	Vector3D addToVector(const Vector3D &toAdd);
	//substract this vector by another vector(toSubstract)
	Vector3D substractToVector(const Vector3D &toSubstract);


	//multiply the X composant with a float(scalar)
	void multiply_X_ByScalar(float scalar);
	//multiply the Y composant with a float(scalar)
	void multiply_Y_ByScalar(float scalar);
	//multiply the Z composant with a float(scalar)
	void multiply_Z_ByScalar(float scalar);

	//multiply each coordinate of the vector by the coordinate of another vector(vector)
	Vector3D composantProduct(const Vector3D &vector);
	//compute the scalarProduct of this vector with another vector(vector)
	float scalarProduct(const Vector3D &vector);
	//compute the vectorProduct of this vector with another vector(vector)
	Vector3D vectorProduct(const Vector3D &vector);

	//add a vector to another
	Vector3D operator+(const Vector3D &toAdd)
	{
		return this->addToVector(toAdd);
	}

	Vector3D operator-(const Vector3D& tosubstract)
	{
		return this->substractToVector(tosubstract);
	}

	//multiply this vector with a float
	Vector3D operator*(const float scalar)
	{
		return this->multiplyByScalar(scalar);
	}

	/*
	Vector3D operator+=(const Vector3D toAdd)
	{
		return this->addToVector(toAdd);
	}
	*/
};

