#include "Particule.h"

Particule::Particule(float mass, float damping, Vector3D initialPosition, Vector3D initialSpeed, Vector3D initialAcceleration) :_mass(mass),_damping(damping){
	this->_position = Vector3D(initialPosition.getX(), initialPosition.getY(), initialPosition.getZ());
	this->_speed = Vector3D(initialSpeed.getX(), initialSpeed.getY(), initialSpeed.getZ());
	this->_acceleration = Vector3D(initialAcceleration.getX(), initialAcceleration.getY(), initialAcceleration.getZ());

}


float Particule::getInversMass() 
{
	if (this->_mass != 0)
	{
		return 1 / _mass;
	}
	return -1;
}

float Particule::getMass()
{
	return _mass;
}

float Particule::getDamping()
{
	return _damping;
}
Vector3D Particule::getPosition()
{
	return _position;
}
Vector3D Particule::getSpeed()
{
	return _speed;
}
Vector3D Particule::getAcceleration()
{
	return _acceleration;
}

void Particule::setMass(float mass) 
{
	this->_mass = mass;
}
void Particule::setDamping(float damping)
{
	this->_damping = damping;
}
void Particule::setPosition(Vector3D const& vector)
{
	this->_position = vector;
}
void Particule::setSpeed(Vector3D const& vector)
{
	this->_speed = vector;
}
void Particule::setAcceleration(Vector3D const& vector)
{
	this->_acceleration = vector;
}

void Particule::integrer(float time)
{

}