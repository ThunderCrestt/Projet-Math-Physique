#pragma once
#include <array>
#include "Vector3D.h"
class Matrix4
{
private:
	std::array<std::array<float, 4>, 4> data;
public:

	Matrix4(std::array<std::array<float, 4>, 4> data = { {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1} }
})
	{
		this->data = data;
	}
	Matrix4 operator-(const Matrix4& toAdd);

	Matrix4 operator+(const Matrix4& toAdd);

	Matrix4 operator*(const Matrix4& toMultiply);
	Vector3D operator*(const Vector3D& vector);

	//calcul l'inverse de la matrice m et l'applique sur la matrice actuel.
	void setInverse(const Matrix4& m);
	Matrix4 inverse() const;
	void invert();
	void setTranspose(const Matrix4& m);
	Matrix4 transpose() const;
};

