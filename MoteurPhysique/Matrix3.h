#pragma once
#ifndef MATRIX3
#define MATRIX3

#include <array>
#include "Vector3D.h"
#include "Quaternion.h"
class Matrix3
{
private:
	std::array<std::array<float, 3>, 3> data;
public:
	Matrix3(std::array<std::array<float, 3>, 3> data = {{ {1,0,0},{0,1,0},{0,0,1} }})
		{
			this->data = data;
		}

		Matrix3 operator-(const Matrix3& toAdd);

		Matrix3 operator+(const Matrix3& toAdd);

		Matrix3 operator*(const Matrix3& toMultiply);
		
		Vector3D operator*(const Vector3D& vector);

		//calcul l'inverse de la matrice m et l'applique sur la matrice actuel.
		void setInverse(const Matrix3& m);
		Matrix3 inverse() const;
		void invert();
		void setTranspose(const Matrix3& m);
		Matrix3 transpose() const;
		void setOrientation(const Quaternion& q);
};

#endif