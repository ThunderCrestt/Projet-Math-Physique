#pragma once
#ifndef MATRIX4
#define MATRIX4

#include <array>
#include "Vector3D.h"
#include "Quaternion.h"
class Matrix4
{
public:
	std::array<std::array<float, 4>, 4> data;

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
	//retourne une matrice comprennant l'inverse de la matrice actuel.
	Matrix4 inverse() const;
	//inverse la matrice actuel
	void invert();
	void setTranspose(const Matrix4& m);
	Matrix4 transpose() const;
	void setOrientationAndPos(const Quaternion& q, const Vector3D& pos);
	Vector3D transformInverse(const Vector3D& vector) const;
	Vector3D transformDirection(const Vector3D& vector) const;
	Vector3D transformInverseDirection(const Vector3D& vector) const;
	/**
	*Change la base du point world en local en fonction de la matrice de transformation
	*/
	Vector3D worldToLocal(const Vector3D& world, const Matrix4& transform);
	/**
	*Change la base du point local en world en fonction de la matrice de transformation
	*/
	Vector3D localToWorldDir(const Vector3D& local, const Matrix4& transform);
	Vector3D worldToLocalDir(const Vector3D& world, const Matrix4& transform);

};

#endif