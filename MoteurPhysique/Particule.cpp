#include "Particule.h"
#include "ParticuleSystem.h"

Particule::Particule(float mass, float damping, Vector3D initialPosition, Vector3D initialSpeed, Vector3D acceleration, ParticuleSystem& particuleSystem) :_mass(mass),_damping(damping){
	this->_position = Vector3D(initialPosition.getX(), initialPosition.getY(), initialPosition.getZ());
	this->_speed = Vector3D(initialSpeed.getX(), initialSpeed.getY(), initialSpeed.getZ());
	this->_acceleration = Vector3D(acceleration.getX(), acceleration.getY(), acceleration.getZ());
	this->_system = &particuleSystem;
	particuleSystem.addParticule(*this);
}

Particule::~Particule()
{
	this->_system->removeParticule(*this);
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
	if (mass != 0)
	{
		this->_mass = mass;
	}
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

void Particule::setupVectors(Vector3D position, Vector3D speed, Vector3D acceleration)
{
	this->setPosition(position);
	this->setSpeed(speed);
	this->setAcceleration(acceleration);
}


void Particule::integrer(float time)
{
	//update de la position
	this->setPosition(getPosition() + getSpeed() * time + getAcceleration() * (pow(time, 2) / 2)); //a verif
	
	//update de la vélocité
	this->setSpeed(getSpeed()*getDamping() + getAcceleration() * time);
	
	//update de l'accélération
	//pour l'instant accélération constante

	//appel de l'update graphique après l'appel de cette fonction
}