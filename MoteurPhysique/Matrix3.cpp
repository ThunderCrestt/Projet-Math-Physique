#include "Matrix3.h"
Matrix3 Matrix3::operator-(const Matrix3& toSubstract)
{
	return Matrix3(
		{ {
			{data[0][0] - toSubstract.data[0][0],
			data[0][1] - toSubstract.data[0][1],
			data[0][2] - toSubstract.data[0][2]},

			{data[1][0] - toSubstract.data[1][0],
			data[1][1] - toSubstract.data[1][1],
			data[1][2] - toSubstract.data[1][2]},

			{data[2][0] - toSubstract.data[2][0],
			data[2][1] - toSubstract.data[2][1],
			data[2][2] - toSubstract.data[2][2]}

			} }
	);
}

Matrix3 Matrix3::operator+(const Matrix3& toAdd)
{
	return Matrix3(
		{ {
			{data[0][0] + toAdd.data[0][0],
			data[0][1] + toAdd.data[0][1],
			data[0][2] + toAdd.data[0][2]},

			{data[1][0] + toAdd.data[1][0],
			data[1][1] + toAdd.data[1][1],
			data[1][2] + toAdd.data[1][2]},

			{data[2][0] + toAdd.data[2][0],
			data[2][1] + toAdd.data[2][1],
			data[2][2] + toAdd.data[2][2]}

			} }
	);
}

Matrix3 Matrix3::operator*(const Matrix3& toMultiply)
{
	return Matrix3(
		{ {
			{data[0][0] * toMultiply.data[0][0] + data[0][1] * toMultiply.data[1][0] + data[0][2] * toMultiply.data[2][0],
			data[0][0] * toMultiply.data[0][1] + data[0][1] * toMultiply.data[1][1] + data[0][2] * toMultiply.data[2][1],
			data[0][0] * toMultiply.data[0][2] + data[0][1] * toMultiply.data[1][2] + data[0][2] * toMultiply.data[2][2]},

			{data[1][0] * toMultiply.data[0][0] + data[1][1] * toMultiply.data[1][0] + data[1][2] * toMultiply.data[2][0],
			data[1][0] * toMultiply.data[0][1] + data[1][1] * toMultiply.data[1][1] + data[1][2] * toMultiply.data[2][1],
			data[1][0] * toMultiply.data[0][2] + data[1][1] * toMultiply.data[1][2] + data[1][2] * toMultiply.data[2][2]},

			{data[2][0] * toMultiply.data[0][0] + data[2][1] * toMultiply.data[1][0] + data[2][2] * toMultiply.data[2][0],
			data[2][0] * toMultiply.data[0][1] + data[2][1] * toMultiply.data[1][1] + data[2][2] * toMultiply.data[2][1],
			data[2][0] * toMultiply.data[0][2] + data[2][1] * toMultiply.data[1][2] + data[2][2] * toMultiply.data[2][2]}

			} }
	);

}

Vector3D Matrix3::operator*(const Vector3D& vector)
{
	return Vector3D(vector.getX() * data[0][0] + vector.getY() * data[0][1] + vector.getZ() * data[0][2],
		vector.getX() * data[1][0] + vector.getY() * data[1][1] + vector.getZ() * data[1][2],
		vector.getX() * data[2][0] + vector.getY() * data[2][1] + vector.getZ() * data[2][2]);
}

//calcul l'inverse de la matrice m et l'applique sur la matrice actuel.
void Matrix3::setInverse(const Matrix3& m)
{
	//on calcule d'abord le déterminant
	float det = (m.data[0][0] * m.data[1][1] * m.data[2][2]) +
		(m.data[1][0] * m.data[2][1] * m.data[0][2]) +
		(m.data[2][0] * m.data[0][1] * m.data[1][2]) -
		(m.data[0][0] * m.data[2][1] * m.data[1][2]) -
		(m.data[2][0] * m.data[1][1] * m.data[0][2]) -
		(m.data[1][0] * m.data[0][1] * m.data[2][2]);
	if (det == (float)0)
	{
		return; // le déterminent est égale à 0, on ne peut pas calculer l'inverse
	}
	// la matrice est de la forme:
	// a b c
	// d e f
	// g h i
	this->data[0][0] = 1/det*( (m.data[1][1]*m.data[2][2])-(m.data[1][2] * m.data[2][1])); //ei -fh
	this->data[0][1] = 1 / det *( (m.data[0][2] * m.data[2][1]) - (m.data[0][1] * m.data[2][2])); //ch - bi
	this->data[0][2] = 1 / det *( (m.data[0][1] * m.data[1][2]) - (m.data[0][2] * m.data[1][1])); //bf-ce

	this->data[1][0] = 1 / det *( (m.data[1][2] * m.data[2][0]) - (m.data[1][0] * m.data[2][2])); //fg-di
	this->data[1][1] = 1 / det *( (m.data[0][0] * m.data[2][2]) - (m.data[0][2] * m.data[2][0])); //ai-cg
	this->data[1][2] = 1 / det *( (m.data[0][2] * m.data[1][0]) - (m.data[0][0] * m.data[1][2])); //cd-af

	this->data[2][0] = 1 / det *( (m.data[1][0] * m.data[2][1]) - (m.data[1][1] * m.data[2][0])); //dh-eg
	this->data[2][1] = 1 / det *( (m.data[0][1] * m.data[2][0]) - (m.data[0][0] * m.data[2][1])); //bg-ah
	this->data[2][2] = 1 / det *( (m.data[0][0] * m.data[1][1]) - (m.data[0][1] * m.data[1][0])); //ae-bd
}

//retourne une matrice comprennant l'inverse de la matrice actuel.
Matrix3 Matrix3::inverse() const
{
	Matrix3 resultMatrix;
	resultMatrix.setInverse(*this);
	return resultMatrix;
}

//inverse la matrice
void Matrix3::invert()
{
	setInverse(*this);
}

void Matrix3::setTranspose(const Matrix3& m)
{
	data[0][0] = m.data[0][0];
	data[0][1] = m.data[1][0]; 
	data[0][2] = m.data[2][0]; 
	data[1][0] = m.data[0][1]; 
	data[1][1] = m.data[1][1]; 
	data[1][2] = m.data[2][1];
	data[2][0] = m.data[0][2];
	data[2][1] = m.data[1][2]; 
	data[2][2] = m.data[2][2]; 
}

Matrix3 Matrix3::transpose() const
{
	Matrix3 result;
	result.setTranspose(*this);
	return result;
}

void Matrix3::setOrientation(const Quaternion &q) {
	data[0][0] = 1 - (2 * q.j * q.j + 2 * q.k * q.k);
	data[0][1] = 2 * q.i * q.j + 2 * q.k * q.r;
	data[0][2] = 2 * q.i * q.k - 2 * q.j * q.r;
	data[1][0] = 2 * q.i * q.j - 2 * q.k * q.r;
	data[1][1] = 1 - (2 * q.i * q.i + 2 * q.k * q.k);
	data[1][2] = 2 * q.j * q.k + 2 * q.i * q.r;
	data[2][0] = 2 * q.i * q.k + 2 * q.j * q.r;
	data[2][1] = 2 * q.j * q.k - 2 * q.i * q.r;
	data[2][2] = 1 - (2 * q.i * q.i + 2 * q.j * q.j);
}