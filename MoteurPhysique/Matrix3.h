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
public:
	/**
	*Constructeur de la matrice
	*/
	std::array<std::array<float, 3>, 3> data;

	Matrix3(std::array<std::array<float, 3>, 3> data = {{ {1,0,0},{0,1,0},{0,0,1} }})
		{
			this->data = data;
		}

		Matrix3 operator-(const Matrix3& toAdd);

		Matrix3 operator+(const Matrix3& toAdd);

		Matrix3 operator*(const Matrix3& toMultiply);
		
		Vector3D operator*(const Vector3D& vector) const;

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

		Vector3D getAxisVector(int i) const
		{
			return Vector3D(data[0][i], data[1][i], data[2][i]);
		}

		Vector3D transform(const Vector3D& vector) const
		{
			return (*this) * vector;
		}

		Vector3D transformTranspose(const Vector3D& vector) const
		{
			return Vector3D(
				vector.getX() * data[0][0] + vector.getY() * data[1][0] + vector.getZ() * data[2][0],
				vector.getX() * data[0][1] + vector.getY() * data[1][1] + vector.getZ() * data[2][1],
				vector.getX() * data[0][2] + vector.getY() * data[1][2] + vector.getZ() * data[2][2]
			);
		}
		Matrix3 operator*(float scalarToMultiply) const
		{
			return Matrix3({ {
				{this->data[0][0] * scalarToMultiply,this->data[0][1] * scalarToMultiply,this->data[0][2] * scalarToMultiply},
				{this->data[1][0] * scalarToMultiply,this->data[1][1] * scalarToMultiply,this->data[1][2] * scalarToMultiply},
				{this->data[2][0] * scalarToMultiply,this->data[2][1] * scalarToMultiply,this->data[2][2] * scalarToMultiply},
				} });
		}

		void setComponents(const Vector3D& compOne, const Vector3D& compTwo,
			const Vector3D& compThree)
		{
			data[0][0] = compOne.getX();
			data[0][1] = compTwo.getX();
			data[0][2] = compThree.getX();
			data[1][0] = compOne.getY();
			data[1][1] = compTwo.getY();
			data[1][2] = compThree.getY();
			data[2][0] = compOne.getZ();
			data[2][1] = compTwo.getZ();
			data[2][2] = compThree.getZ();

		}

		Matrix3(const Vector3D& compOne, const Vector3D& compTwo,
			const Vector3D& compThree)
		{
			setComponents(compOne, compTwo, compThree);
		}

		/**
 * Sets the matrix to be a skew symmetric matrix based on
 * the given vector. The skew symmetric matrix is the equivalent
 * of the vector product. So if a,b are vectors. a x b = A_s b
 * where A_s is the skew symmetric form of a.
 */
		void setSkewSymmetric(const Vector3D vector)
		{
			data[0][0] = data[1][1] = data[2][2] = 0;
			data[0][1] = -vector.getZ();
			data[0][2] = vector.getY();
			data[1][0] = vector.getZ();
			data[1][2] = -vector.getX();
			data[2][0] = -vector.getY();
			data[2][1] = vector.getX();
		}

};

#endif