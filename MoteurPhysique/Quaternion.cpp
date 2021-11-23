#include "Quaternion.h"

void Quaternion::normalize()
{
	float d = r * r + i * i + j * j + k * k;
	if (d == 0)
	{
		r = 1;
		return;
	}
	d = ((float)1.0) / (float)sqrt(d);
	r *= d;
	i *= d;
	j *= d;
	k *= d;
}


void  Quaternion::operator *=(const Quaternion& toMultiply)
{
	Quaternion q = *this;
	r = q.r * toMultiply.r - q.i * toMultiply.i -
		q.j * toMultiply.j - q.k * toMultiply.k;
	i = q.r * toMultiply.i + q.i * toMultiply.r +
		q.j * toMultiply.k - q.k * toMultiply.j;
		j = q.r * toMultiply.j + q.j * toMultiply.r +
		q.k * toMultiply.i - q.i * toMultiply.k;
	k = q.r * toMultiply.k + q.k * toMultiply.r +
		q.i * toMultiply.j - q.j * toMultiply.i;

	normalize();
}
