#pragma once
#ifndef MATRIX3
#define MATRIX3

#include <array>
#include "Vector3D.h"
#include "Quaternion.h"
class Matrix3
{
private:
	/**
	*contient la matrice en elle même
	*/
	std::array<std::array<float, 3>, 3> data;
public:
	/**
	*Constructeur de la matrice
	*/
	Matrix3(std::array<std::array<float, 3>, 3> data = {{ {1,0,0},{0,1,0},{0,0,1} }})
		{
			this->data = data;
		}

		Matrix3 operator-(const Matrix3& toAdd);

		Matrix3 operator+(const Matrix3& toAdd);

		Matrix3 operator*(const Matrix3& toMultiply);
		
		Vector3D operator*(const Vector3D& vector);

		/**
		* calcul la matrice inverse de m et l'applique à la matrice courante
		*/
		void setInverse(const Matrix3& m);
		/**
		* retourne une matrice contennant la matrice inverse de la matrice courante
		*/
		Matrix3 inverse() const;
		/**
		*inverse la matrice actuel
		*/
		void invert();
		/**
		*calcul la tansposition de la matrice m et l'applique à la matrice courante
		*/
		void setTranspose(const Matrix3& m);
		/**
		*Transpose la matrice actuel
		*/
		Matrix3 transpose() const;
		/**
		* set l'orientation de la matrice en fonction d'un quaternion
		*/
		void setOrientation(const Quaternion& q);
};

#endif