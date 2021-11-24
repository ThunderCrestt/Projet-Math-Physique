#pragma once
#include <array>
#ifndef QUATERNION
#define QUATERNION

 // !

#include "Vector3D.h"
class Quaternion
{

public:
	union {
		struct {
			/**
			*Contient la composante réel du quaternion
			*/
			float r;
			/**
			* Contient la première composante complexe du quaternion
			*/
			float i;
			/**
			* Contient la deuxième composante complexe du quaternion.
			*/
			float j;
				/**
				* Contient la troisème composante complexe du quaternion
				*/
			float k;
		};
		/**
		* Contient le quaternion en forme d'array
		*/
		std::array<float,4> data;
	};
	Quaternion(float r, float i, float j, float k)
	{
		this->r = r;
		this->i = i;
		this->j = j;
		this->k = k;
		data[0] = r;
		data[1] = i;
		data[2] = j;
		data[3] = k;

	} 
	/**
	*Normalise le quaternion
	*/
	void normalize();
	void operator *=(const Quaternion& multiplier);

	/**
	*tourne le quaternion par un vecteur.
	*/
	void rotateByVector(const Vector3D & vector,float scale)
	{
		Quaternion q(0, vector.getX() * scale, vector.getY() * scale,
			vector.getZ() * scale);
		(*this) *= q;
		normalize();
	}

	/*
	* ajoute au quaternion un vecteur par un scalaire
	*/
	void addScaledVector(const Vector3D& vector, float scale)
	{
		Quaternion q(0,
			vector.getX() * scale,
			vector.getY() * scale,
			vector.getZ() * scale);
		q *= *this;
		r += q.r * ((float)0.5);
		i += q.i * ((float)0.5);
		j += q.j * ((float)0.5);
		k += q.k * ((float)0.5);
		normalize();
	}


};


#endif