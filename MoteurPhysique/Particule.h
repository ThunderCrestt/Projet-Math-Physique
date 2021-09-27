#pragma once
#include "Vector3D.h"
class ParticuleSystem;
class Particule
{
private :
	float _mass;
	float _damping;// coef de décélération on va dire =0.7, mais dans phase 1 damping=1
	Vector3D _position;
	Vector3D _speed;
	Vector3D _acceleration; //is a constant
public:
	Particule(float mass, float damping, Vector3D initialPosition, Vector3D initialSpeed, Vector3D acceleration,ParticuleSystem &particuleSystem);
	//get the inverse mass of this particule
	float getInversMass();
	//get the mass of this particule
	float getMass();
	//get the damping of this particule
	float getDamping();

	//get the position vector of this particule
	Vector3D getPosition();
	//get the velocity vector of this particule
	Vector3D getSpeed();
	//get the acceleration of this particule
	Vector3D getAcceleration();

	//set the mass(mass) of the particule
	void setMass(float mass);
	//set the damping(damping) of this particule
	void setDamping(float damping);
	//set the position vector(vector) of this particule
	void setPosition(Vector3D const& vector);
	//set the speed vector(vector) of this particule
	void setSpeed(Vector3D const& vector);
	//set the acceleration vector(vector) of this particule
	void setAcceleration(Vector3D const& vector);



	//compute at each frame what is the next position/velocity of this particule.
	void integrer(float time);
};

