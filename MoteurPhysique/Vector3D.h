#pragma once
#include <cmath>
class Vector3D
{
private :
	float _x;
	float _y;
	float _z;
public :
	Vector3D(float x, float y, float z) :_x(x), _y(y), _z(z) {
	};
	float getX(void);
	float getY(void);
	float getZ(void);
	void setX(float x);
	void setY(float y);
	void setZ(float z);

	float getNorm(void);
	float getSquareNorm(void);

	void normalize(void); //we put the coordonates on the norm of the vector
	Vector3D multiplyByScalar(float scalar);
	Vector3D addToVector(Vector3D toAdd);
	Vector3D toSubstractToVector(Vector3D toSubstract);

	void multiply_X_ByScalar(float scalar);
	void multiply_Y_ByScalar(float scalar);
	void multiply_Z_ByScalar(float scalar);

	float scalarProduct(Vector3D vector);
	Vector3D vectorProduct(Vector3D vector);

};

