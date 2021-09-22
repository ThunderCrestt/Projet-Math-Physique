#pragma once
#include "Vector3D.h"
class Particule
{
private :
	float _mass;
	float _damping;// coef de décélération on va dire =0.7
	Vector3D _position;
	Vector3D _speed;
	Vector3D _acceleration;
public:
	Particule(float mass, float damping, Vector3D initialPosition, Vector3D initialSpeed, Vector3D initialAcceleration);
	float getInversMass();
	float getMass();
	float getDamping();
	Vector3D getPosition();
	Vector3D getSpeed();
	Vector3D getAcceleration();

	void setMass(float mass);
	void setDamping(float damping);
	void setPosition(Vector3D const& vector);
	void setSpeed(Vector3D const& vector);
	void setAcceleration(Vector3D const& vector);




	void integrer(float time);
};

