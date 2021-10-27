#pragma once
#include "Vector3D.h"
class ParticuleWorld;
class Particule
{
private :
	float _mass;
	float _damping;// coef de décélération on va dire =0.7, mais dans phase 1 damping=1
	Vector3D _position;
	Vector3D _speed;
	Vector3D _acceleration; //is a constant
	Vector3D _accumForce;
	float _rayon;
	//ParticuleSystem *_system;
public:
	Particule(float mass, float damping, Vector3D initialPosition, Vector3D initialSpeed, Vector3D acceleration,float rayon);
	~Particule();
	//get the inverse mass of this particule
	float getInversMass();
	//get the mass of this particule
	float getMass();
	//get the damping of this particule
	float getDamping();
	float getRayon();
	//get the position vector of this particule
	Vector3D getPosition();
	//get the velocity vector of this particule
	Vector3D getVelocity();
	//get the acceleration of this particule
	Vector3D getAcceleration();

	//set the mass(mass) of the particule
	void setMass(float mass);
	//set the damping(damping) of this particule
	void setDamping(float damping);
	//set the position vector(vector) of this particule
	void setPosition(Vector3D const& vector);
	//set the speed vector(vector) of this particule
	void setVelocity(Vector3D const& vector);
	//set the acceleration vector(vector) of this particule
	void setAcceleration(Vector3D const& vector);
	//set the position,speed and acceleration of the particule, usefull when changing projectile
	void setupVectors(Vector3D position, Vector3D speed, Vector3D acceleration);



	//compute at each frame what is the next position/velocity of this particule.
	void integrer(float time);
	void clearAccumulator();
	void addForce(const Vector3D& vector);

};

