#pragma once
#include <array>
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
		* Holds the quaternion data in array form.
		*/
		std::array<float,4> data;
	};
	Quaternion(float r, float i, float j, float k)
	{
		this->r = r;
		this->i = i;
		this->j = j;
		this->k = k;

	}
	void normalize();

};


