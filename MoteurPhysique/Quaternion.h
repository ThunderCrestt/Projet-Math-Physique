#pragma once
#include <array>
class Quaternion
{

public:
	union {
		struct {
			/**
			*Contient la composante r�el du quaternion
			*/
			float r;
			/**
			* Contient la premi�re composante complexe du quaternion
			*/
			float i;
			/**
			* Contient la deuxi�me composante complexe du quaternion.
			*/
			float j;
				/**
				* Contient la trois�me composante complexe du quaternion
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


