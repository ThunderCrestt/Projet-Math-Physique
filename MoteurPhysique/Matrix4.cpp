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

Vector3D Matrix4::operator*(const Vector3D& vector) const
{
	return Vector3D(vector.getX() * data[0][0] + vector.getY() * data[0][1] + vector.getZ() * data[0][2]+data[0][3],
		vector.getX() * data[1][0] + vector.getY() * data[1][1] + vector.getZ() * data[1][2] + data[1][3],
		vector.getX() * data[2][0] + vector.getY() * data[2][1] + vector.getZ() * data[2][2] + data[2][3]);
}

//calcul l'inverse de la matrice m et l'applique sur la matrice actuel.
void Matrix4::setInverse(const Matrix4& m)
{
	//on calcule d'abord le d�terminant
	float det = (
		m.data[0][0]*( (m.data[1][1]*m.data[2][2]*m.data[3][3]) + (m.data[1][2]* m.data[2][3]* m.data[3][1]) + (m.data[1][3]* m.data[2][1]* m.data[3][2])
		-(m.data[1][3]* m.data[2][2]* m.data[3][1]) - (m.data[1][2]* m.data[2][1]* m.data[3][3]) - (m.data[1][1]* m.data[2][3]* m.data[3][2]) 
		)
		
		- m.data[1][0]*( (m.data[0][1]* m.data[2][2]* m.data[3][3]) + (m.data[0][2]* m.data[2][3]* m.data[3][1]) + (m.data[0][3]* m.data[2][1]* m.data[3][2])
		-(m.data[0][3]* m.data[2][2]* m.data[3][1]) - (m.data[0][2]* m.data[2][1]* m.data[3][3]) - (m.data[0][1]* m.data[2][3]* m.data[3][2]) 
		) 
		
		+ m.data[2][0]*( (m.data[0][1]* m.data[1][2]* m.data[3][3]) + (m.data[0][2]* m.data[1][3]* m.data[3][1]) + (m.data[0][3]* m.data[1][1]* m.data[3][2])
			-(m.data[0][3]* m.data[1][2]* m.data[3][1]) - (m.data[0][2]* m.data[1][1]* m.data[3][3]) - (m.data[0][1]* m.data[1][3]* m.data[3][2]) 
		)
		
		-m.data[3][0]*( (m.data[0][1]* m.data[1][2]* m.data[2][3]) + (m.data[0][2]* m.data[1][3]* m.data[2][1]) + (m.data[0][3]* m.data[1][1]* m.data[2][2])
			-(m.data[0][3]* m.data[1][2]* m.data[2][1]) - (m.data[0][2]* m.data[1][1]* m.data[2][3]) - (m.data[0][1]* m.data[1][3]* m.data[2][2]) 
		));



	if (det == (float)0)
	{
		return; // le d�terminent est �gale � 0, on ne peut pas calculer l'inverse
	}
	//le calcul de la matrice est fait selon le calcul du d�terminant et de la matrice adjointe
	this->data[0][0] = 1/det*( (m.data[1][1]* m.data[2][2]* m.data[3][3]) + (m.data[1][2]* m.data[2][3]* m.data[3][1]) + (m.data[1][3]* m.data[2][1]* m.data[3][2]) 
		- (m.data[1][3]* m.data[2][2]* m.data[3][1]) - (m.data[1][2]* m.data[2][1]* m.data[3][3]) - (m.data[1][1]* m.data[2][3]* m.data[3][2]) );

	this->data[0][1] = 1 / det * ( -(m.data[0][1]* m.data[2][2]* m.data[3][3]) - (m.data[0][2]* m.data[2][3]* m.data[3][1]) - (m.data[0][3]* m.data[2][1]* m.data[3][2])
		+(m.data[0][3]* m.data[2][2]* m.data[3][1]) + (m.data[0][2]* m.data[2][1]* m.data[3][3]) + (m.data[0][1]* m.data[2][3]* m.data[3][2]) );
	
	this->data[0][2] = 1 / det * ( (m.data[0][1] * m.data[1][2] * m.data[3][3]) + (m.data[0][2] * m.data[1][3] * m.data[3][1]) + (m.data[0][3] * m.data[1][1] * m.data[3][2])
		- (m.data[0][3] * m.data[1][2] * m.data[3][1]) - (m.data[0][2] * m.data[1][1] * m.data[3][3]) - (m.data[0][1] * m.data[1][3] * m.data[3][2]) );
	
	this->data[0][3] = 1 / det * (-(m.data[0][1] * m.data[1][2] * m.data[2][3]) - (m.data[0][2] * m.data[1][3] * m.data[2][1]) - (m.data[0][3] * m.data[1][1] * m.data[2][2])
		+ (m.data[0][3] * m.data[1][2] * m.data[2][1]) + (m.data[0][2] * m.data[1][1] * m.data[2][3]) + (m.data[0][1] * m.data[1][3] * m.data[2][2]));

	//

	this->data[1][0] = 1 / det * (-(m.data[1][0] * m.data[2][2] * m.data[3][3]) - (m.data[1][2] * m.data[2][3] * m.data[3][0]) - (m.data[1][3] * m.data[2][0] * m.data[3][2])
		+ (m.data[1][3] * m.data[2][2] * m.data[3][0]) + (m.data[1][2] * m.data[2][0] * m.data[3][3]) + (m.data[1][0] * m.data[2][3] * m.data[3][2]));

	this->data[1][1] = 1 / det * ((m.data[0][0] * m.data[2][2] * m.data[3][3]) + (m.data[0][2] * m.data[2][3] * m.data[3][0]) + (m.data[0][3] * m.data[2][0] * m.data[3][2])
		- (m.data[0][3] * m.data[2][2] * m.data[3][0]) - (m.data[0][2] * m.data[2][0] * m.data[3][3]) - (m.data[0][0] * m.data[2][3] * m.data[3][2]));
	
	this->data[1][2] = 1 / det * (-(m.data[0][0] * m.data[1][2] * m.data[3][3]) - (m.data[0][2] * m.data[1][3] * m.data[3][0]) - (m.data[0][3] * m.data[1][0] * m.data[3][2])
		+ (m.data[0][3] * m.data[1][2] * m.data[3][0]) + (m.data[0][2] * m.data[1][0] * m.data[3][3]) + (m.data[0][0] * m.data[1][3] * m.data[3][2]));

	this->data[1][3] = 1 / det * ((m.data[0][0] * m.data[1][2] * m.data[2][3]) + (m.data[0][2] * m.data[1][3] * m.data[2][0]) + (m.data[0][3] * m.data[1][0] * m.data[2][2])
		- (m.data[0][3] * m.data[1][2] * m.data[2][0]) - (m.data[0][2] * m.data[1][0] * m.data[2][3]) - (m.data[0][0] * m.data[1][3] * m.data[2][2]));

	//

	this->data[2][0] = 1 / det * ((m.data[1][0] * m.data[2][1] * m.data[3][3]) + (m.data[1][1] * m.data[2][3] * m.data[3][0]) + (m.data[1][3] * m.data[2][0] * m.data[3][1])
		- (m.data[1][3] * m.data[2][1] * m.data[3][0]) - (m.data[1][1] * m.data[2][0] * m.data[3][3]) - (m.data[1][0] * m.data[2][3] * m.data[3][1]));

	this->data[2][1] = 1 / det * (-(m.data[0][0] * m.data[2][1] * m.data[3][3]) - (m.data[0][1] * m.data[2][3] * m.data[3][0]) - (m.data[0][3] * m.data[2][0] * m.data[3][1])
		+ (m.data[0][3] * m.data[2][1] * m.data[3][0]) + (m.data[0][1] * m.data[2][0] * m.data[3][3]) + (m.data[0][0] * m.data[2][3] * m.data[3][1]));

	this->data[2][2] = 1 / det * ((m.data[0][0] * m.data[1][1] * m.data[3][3]) + (m.data[0][1] * m.data[1][3] * m.data[3][0]) + (m.data[0][3] * m.data[1][0] * m.data[3][1])
		- (m.data[0][3] * m.data[1][1] * m.data[3][0]) - (m.data[0][1] * m.data[1][0] * m.data[3][3]) - (m.data[0][0] * m.data[1][3] * m.data[3][1]));

	this->data[2][3] = 1 / det * (-(m.data[0][0] * m.data[1][1] * m.data[2][3]) - (m.data[0][1] * m.data[1][3] * m.data[2][0]) - (m.data[0][3] * m.data[1][0] * m.data[2][1])
		+ (m.data[0][3] * m.data[1][1] * m.data[2][0]) + (m.data[0][1] * m.data[1][0] * m.data[2][3]) + (m.data[0][0] * m.data[1][3] * m.data[2][1]));

	//

	this->data[3][0] = 1 / det * (-(m.data[1][0] * m.data[2][1] * m.data[3][2]) - (m.data[0][1] * m.data[2][2] * m.data[3][0]) - (m.data[1][2] * m.data[2][0] * m.data[3][1])
		+ (m.data[1][2] * m.data[2][1] * m.data[3][0]) + (m.data[1][1] * m.data[2][0] * m.data[3][2]) + (m.data[1][0] * m.data[2][2] * m.data[3][1]));

	this->data[3][1] = 1 / det * ((m.data[0][0] * m.data[2][1] * m.data[3][2]) + (m.data[0][1] * m.data[2][2] * m.data[3][0]) + (m.data[0][2] * m.data[2][0] * m.data[3][1])
		- (m.data[0][2] * m.data[2][1] * m.data[3][0]) - (m.data[0][1] * m.data[2][0] * m.data[3][2]) - (m.data[0][0] * m.data[2][2] * m.data[3][1]));

	this->data[3][2] = 1 / det * (-(m.data[0][0] * m.data[1][1] * m.data[3][2]) - (m.data[0][1] * m.data[1][2] * m.data[3][0]) - (m.data[0][2] * m.data[1][0] * m.data[3][1])
		+ (m.data[0][2] * m.data[1][1] * m.data[3][0]) + (m.data[0][1] * m.data[1][0] * m.data[3][2]) + (m.data[0][0] * m.data[1][2] * m.data[3][1]));
	
	this->data[3][3] = 1 / det * ((m.data[0][0] * m.data[1][1] * m.data[2][2]) + (m.data[0][1] * m.data[1][2] * m.data[2][0]) + (m.data[0][2] * m.data[1][0] * m.data[2][1])
		- (m.data[0][2] * m.data[1][1] * m.data[2][0]) - (m.data[0][1] * m.data[1][0] * m.data[2][2]) - (m.data[0][0] * m.data[1][2] * m.data[2][1]));

}

//retourne une matrice comprennant l'inverse de la matrice actuel.
Matrix4 Matrix4::inverse() const
{
	Matrix4 resultMatrix;
	resultMatrix.setInverse(*this);
	return resultMatrix;
}

//inverse la matrice actuel
void Matrix4::invert()
{
	setInverse(*this);
}

void Matrix4::setTranspose(const Matrix4& m)
{
	data[0][0] = m.data[0][0];
	data[0][1] = m.data[1][0];
	data[0][2] = m.data[2][0];
	data[0][3] = m.data[3][0];
	data[1][0] = m.data[0][1];
	data[1][1] = m.data[1][1];
	data[1][2] = m.data[2][1];
	data[1][3] = m.data[3][1];
	data[2][0] = m.data[0][2];
	data[2][1] = m.data[1][2];
	data[2][2] = m.data[2][2];
	data[2][3] = m.data[3][2];
	data[3][0] = m.data[0][3];
	data[3][1] = m.data[1][3];
	data[3][2] = m.data[2][3];
	data[3][3] = m.data[3][3];
}

Matrix4 Matrix4::transpose() const
{
	Matrix4 result;
	result.setTranspose(*this);
	return result;
}

void Matrix4::setOrientationAndPos(const Quaternion& q, const Vector3D& pos)
{
	data[0][0] = 1 - (2 * q.j * q.j + 2 * q.k * q.k);
	data[0][1] = 2 * q.i * q.j + 2 * q.k * q.r;
	data[0][2] = 2 * q.i * q.k - 2 * q.j * q.r;
	data[0][3] = pos.getX();
	data[1][0] = 2 * q.i * q.j - 2 * q.k * q.r;
	data[1][1] = 1 - (2 * q.i * q.i + 2 * q.k * q.k);
	data[1][2] = 2 * q.j * q.k + 2 * q.i * q.r;
	data[1][3] = pos.getY();
	data[2][0] = 2 * q.i * q.k + 2 * q.j * q.r;
	data[2][1] = 2 * q.j * q.k - 2 * q.i * q.r;
	data[2][2] = 1 - (2 * q.i * q.i + 2 * q.j * q.j);
	data[2][3] = pos.getZ();
	data[3][0] = 0;
	data[3][1] = 0;
	data[3][2] = 0;
	data[3][3] = 1;
}

Vector3D Matrix4::transformInverse(const Vector3D& vector) const {
	Vector3D tmp = vector;
	tmp.setX(tmp.getX() - data[0][3]);
	tmp.setY(tmp.getY() - data[1][3]);
	tmp.setZ(tmp.getZ() - data[2][3]);
	return Vector3D(
		tmp.getX() * data[0][0] +
		tmp.getY() * data[1][0] +
		tmp.getZ() * data[2][0],

		tmp.getX() * data[0][1] +
		tmp.getY() * data[1][1] +
		tmp.getZ() * data[2][1],

		tmp.getX() * data[0][2] +
		tmp.getY() * data[1][2] +
		tmp.getZ() * data[2][2]
	);
}

Vector3D Matrix4::transformDirection(const Vector3D& vector) const {
	return Vector3D(
		vector.getX() * data[0][0] +
		vector.getY() * data[0][1] +
		vector.getZ() * data[0][2],

		vector.getX() * data[1][0] +
		vector.getY() * data[1][1] +
		vector.getZ() * data[1][2],

		vector.getX() * data[2][0] +
		vector.getY() * data[2][1] +
		vector.getZ() * data[2][2]
	);
}

Vector3D Matrix4::transformInverseDirection(const Vector3D& vector) const {
	return Vector3D(
		vector.getX() * data[0][0] +
		vector.getY() * data[1][0] +
		vector.getZ() * data[2][0],

		vector.getX() * data[0][1] +
		vector.getY() * data[1][1] +
		vector.getZ() * data[2][1],

		vector.getX() * data[0][2] +
		vector.getY() * data[1][2] +
		vector.getZ() * data[2][2]
		);
}

Vector3D Matrix4::worldToLocal(const Vector3D& world, const Matrix4& transform)
{
	return transform.transformInverse(world);
}

Vector3D Matrix4::localToWorldDir(const Vector3D& local, const Matrix4& transform)
{
	return transform.transformDirection(local);
}

Vector3D Matrix4::worldToLocalDir(const Vector3D& world, const Matrix4& transform)
{
	return transform.transformInverseDirection(world);
}