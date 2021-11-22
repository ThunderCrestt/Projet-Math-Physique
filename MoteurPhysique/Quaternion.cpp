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