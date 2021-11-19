#include "Matrix4.h"
Matrix4 Matrix4::operator-(const Matrix4& toSubstract)
{
	return Matrix4(
		{ {
			{data[0][0] - toSubstract.data[0][0],
			data[0][1] - toSubstract.data[0][1],
			data[0][2] - toSubstract.data[0][2],
			data[0][3] - toSubstract.data[0][3]},

			{data[1][0] - toSubstract.data[1][0],
			data[1][1] - toSubstract.data[1][1],
			data[1][2] - toSubstract.data[1][2],
			data[1][3] - toSubstract.data[1][3]},

			{data[2][0] - toSubstract.data[2][0],
			data[2][1] - toSubstract.data[2][1],
			data[2][2] - toSubstract.data[2][2],
			data[2][3] - toSubstract.data[2][3]},

			{data[3][0] - toSubstract.data[3][0],
			data[3][1] - toSubstract.data[3][1],
			data[3][2] - toSubstract.data[3][2],
			data[3][3] - toSubstract.data[3][3]}

			} }
	);
}

Matrix4 Matrix4::operator+(const Matrix4& toAdd)
{

	return Matrix4(
		{ {
			{data[0][0] + toAdd.data[0][0],
			data[0][1] + toAdd.data[0][1],
			data[0][2] + toAdd.data[0][2],
			data[0][3] + toAdd.data[0][3]},

			{data[1][0] + toAdd.data[1][0],
			data[1][1] + toAdd.data[1][1],
			data[1][2] + toAdd.data[1][2],
			data[1][3] + toAdd.data[1][3]},

			{data[2][0] + toAdd.data[2][0],
			data[2][1] + toAdd.data[2][1],
			data[2][2] + toAdd.data[2][2],
			data[2][3] + toAdd.data[2][3]},

			{data[3][0] + toAdd.data[3][0],
			data[3][1] + toAdd.data[3][1],
			data[3][2] + toAdd.data[3][2],
			data[3][3] + toAdd.data[3][3]}

			} }
	);
}

Matrix4 Matrix4::operator*(const Matrix4& toMultiply)
{
	return Matrix4(
		{ {
			{data[0][0] * toMultiply.data[0][0] + data[0][1] * toMultiply.data[1][0] + data[0][2] * toMultiply.data[2][0] + data[0][3] * toMultiply.data[3][0],
			data[0][0] * toMultiply.data[0][1] + data[0][1] * toMultiply.data[1][1] + data[0][2] * toMultiply.data[2][1] + data[0][3] * toMultiply.data[3][1],
			data[0][0] * toMultiply.data[0][2] + data[0][1] * toMultiply.data[1][2] + data[0][2] * toMultiply.data[2][2] + data[0][3] * toMultiply.data[3][2],
			data[0][0] * toMultiply.data[0][3] + data[0][1] * toMultiply.data[1][3] + data[0][2] * toMultiply.data[2][3] + data[0][3] * toMultiply.data[3][3]},

			{data[1][0] * toMultiply.data[0][0] + data[1][1] * toMultiply.data[1][0] + data[1][2] * toMultiply.data[2][0] + data[1][3] * toMultiply.data[3][0],
			data[1][0] * toMultiply.data[0][1] + data[1][1] * toMultiply.data[1][1] + data[1][2] * toMultiply.data[2][1] + data[1][3] * toMultiply.data[3][1],
			data[1][0] * toMultiply.data[0][2] + data[1][1] * toMultiply.data[1][2] + data[1][2] * toMultiply.data[2][2] + data[1][3] * toMultiply.data[3][2],
			data[1][0] * toMultiply.data[0][3] + data[1][1] * toMultiply.data[1][3] + data[1][2] * toMultiply.data[2][3] + data[1][3] * toMultiply.data[3][3]},

			{data[2][0] * toMultiply.data[0][0] + data[2][1] * toMultiply.data[1][0] + data[2][2] * toMultiply.data[2][0] + data[2][3] * toMultiply.data[3][0],
			data[2][0] * toMultiply.data[0][1] + data[2][1] * toMultiply.data[1][1] + data[2][2] * toMultiply.data[2][1] + data[2][3] * toMultiply.data[3][1],
			data[2][0] * toMultiply.data[0][2] + data[2][1] * toMultiply.data[1][2] + data[2][2] * toMultiply.data[2][2] + data[2][3] * toMultiply.data[3][2],
			data[2][0] * toMultiply.data[0][3] + data[2][1] * toMultiply.data[1][3] + data[2][2] * toMultiply.data[2][3] + data[2][3] * toMultiply.data[3][3]},

			{data[3][0] * toMultiply.data[0][0] + data[3][1] * toMultiply.data[1][0] + data[3][2] * toMultiply.data[2][0] + data[3][3] * toMultiply.data[3][0],
			data[3][0] * toMultiply.data[0][1] + data[3][1] * toMultiply.data[1][1] + data[3][2] * toMultiply.data[2][1] + data[3][3] * toMultiply.data[3][1],
			data[3][0] * toMultiply.data[0][2] + data[3][1] * toMultiply.data[1][2] + data[3][2] * toMultiply.data[2][2] + data[3][3] * toMultiply.data[3][2],
			data[3][0] * toMultiply.data[0][3] + data[3][1] * toMultiply.data[1][3] + data[3][2] * toMultiply.data[2][3] + data[3][3] * toMultiply.data[3][3]}

			} }
	);

}

Vector3D Matrix4::operator*(const Vector3D& vector)
{
	return Vector3D(vector.getX() * data[0][0] + vector.getY() * data[0][1] + vector.getZ() * data[0][2],
		vector.getX() * data[1][0] + vector.getY() * data[1][1] + vector.getZ() * data[1][2],
		vector.getX() * data[2][0] + vector.getY() * data[2][1] + vector.getZ() * data[2][2]);
}

//calcul l'inverse de la matrice m et l'applique sur la matrice actuel.
void Matrix4::setInverse(const Matrix4& m)
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
	this->data[0][0] = (m.data[1][1] * m.data[2][2]) - (m.data[1][2] * m.data[2][1]); //ei -fh
	this->data[0][1] = (m.data[0][2] * m.data[2][1]) - (m.data[0][1] * m.data[2][2]); //ch - bi
	this->data[0][2] = (m.data[0][1] * m.data[1][2]) - (m.data[0][2] * m.data[1][1]); //bf-ce

	this->data[1][0] = (m.data[1][2] * m.data[2][0]) - (m.data[1][0] * m.data[2][2]); //fg-di
	this->data[1][1] = (m.data[0][0] * m.data[2][2]) - (m.data[0][2] * m.data[2][0]); //ai-cg
	this->data[1][2] = (m.data[0][2] * m.data[0][1]) - (m.data[0][0] * m.data[1][2]); //cd-af

	this->data[2][0] = (m.data[1][0] * m.data[2][1]) - (m.data[1][1] * m.data[2][0]); //dh-eg
	this->data[2][1] = (m.data[0][1] * m.data[2][0]) - (m.data[0][0] * m.data[2][1]); //bg-ah
	this->data[2][2] = (m.data[0][0] * m.data[1][1]) - (m.data[0][1] * m.data[1][0]); //ae-bd
}

//retourne une matrice comprennant l'inverse de la matrice actuel.
Matrix4 Matrix4::inverse() const
{
	Matrix4 result;
	result.setInverse(*this);
	return result;
}

//inverse la matrice
void Matrix4::invert()
{
	setInverse(*this);
}

void Matrix4::setTranspose(const Matrix4& m)
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

Matrix4 Matrix4::transpose() const
{
	Matrix4 result;
	result.setTranspose(*this);
	return result;
}