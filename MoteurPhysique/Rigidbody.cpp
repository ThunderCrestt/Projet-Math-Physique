#include "RigidBody.h"

RigidBody::RigidBody(Vector3D *position, Quaternion orientation, float mass, float damping, float angularDamping, Matrix3 tenseurInertie) : _position(*position), _orientation(orientation), _inverseMass(1 / mass), _damping(damping), _angularDamping(angularDamping),
_accumForce(Vector3D(0, 0, 0)), _accumTorque(Vector3D(0, 0, 0)){
	this->setInverseInertiaTensor(tenseurInertie);
}


float RigidBody::getInverseMass()
{
	return _inverseMass;
}
float RigidBody::getDamping()
{
	return _damping;
}

Vector3D RigidBody::getPosition()
{
	return _position;
}
Vector3D RigidBody::getVelocity()
{
	return _speed;
}
Vector3D RigidBody::getAcceleration()
{
	return _acceleration;
}


void RigidBody::setInverseMass(float inverseMass) 
{
	if (inverseMass != 0)
	{
		this->_inverseMass = inverseMass;
	}
}
void RigidBody::setDamping(float damping)
{
	this->_damping = damping;
}

void RigidBody::setPosition(Vector3D const& vector)
{
	this->_position = vector;
}
void RigidBody::setVelocity(Vector3D const& vector)
{
	this->_speed = vector;
}
void RigidBody::setAcceleration(Vector3D const& vector)
{
	this->_acceleration = vector;
}


void RigidBody::integrer(float time)
{

    Vector3D _linearAccel =_accumForce  * _inverseMass ;
    Vector3D _angularAccel = inverseInertiaTensor * _accumTorque;
    
    _speed = _speed +_linearAccel * time;
    _rotation = _rotation +_angularAccel * time;

    //Impose Drag 
    _speed = _speed* pow(_damping, time);
    _rotation = _rotation*pow(_angularDamping, time) ;

    
    _position =_position+ _speed * (time);
    //_orientation = _orientation +_rotation * time;
	_orientation.addScaledVector(_rotation, time);
    //Impose Drag 
    _speed = _speed* pow(_damping, time);
    _rotation = _rotation*pow(_angularDamping, time) ;

    // Normalise the orientation, and update the matrice
	calculateDerivedData();
    // Clear accumulators.
    clearAccumulator();

}
void RigidBody::clearAccumulator()
{
	 _accumForce = Vector3D(0,0,0);
    _accumTorque = Vector3D(0,0,0);
    _orientation.normalize();
}
void RigidBody::addForce(Vector3D& force)
{
	_accumForce = _accumForce+ force;
}
void RigidBody::addForceAtBodyPoint(Vector3D& force, Vector3D& point)
{
	Vector3D pointMonde = _transformMatrix*point;
    addForceAtPoint(force, point);
}
void RigidBody::addForceAtPoint(Vector3D& force, Vector3D& point)
{
	_accumForce = _accumForce+ force;
}


//Code à décommenter lors de l'implémentation des matrices,quaternion


Matrix4 RigidBody::getTransformMatrix()
{
	return _transformMatrix;
}

void RigidBody::setInverseInertiaTensor(const Matrix3 &inertiaTensor)
{
	inverseInertiaTensor.setInverse(inertiaTensor);
}

void RigidBody::setTransformMatrix(Matrix4 matrix)
{
	this->_transformMatrix = matrix;
}

void RigidBody::calculateDerivedData()
{
// Calculate the transform matrix for the body.
calculateTransformMatrix(_transformMatrix, _position, _orientation);
}

void RigidBody::calculateTransformMatrix(Matrix4 &transformMatrix,const Vector3D &position,const Quaternion &orientation)
{
	transformMatrix.data[0][0] = 1 - 2 * orientation.j * orientation.j -
		2 * orientation.k * orientation.k;

	transformMatrix.data[0][1] = 2 * orientation.i * orientation.j -
		2 * orientation.r * orientation.k;

	transformMatrix.data[0][2] = 2 * orientation.i * orientation.k +
		2 * orientation.r * orientation.j;

	transformMatrix.data[0][3] = position.getX();

	transformMatrix.data[1][0] = 2 * orientation.i * orientation.j +
		2 * orientation.r * orientation.k;

	transformMatrix.data[1][1] = 1 - 2 * orientation.i * orientation.i -
		2 * orientation.k * orientation.k;

	transformMatrix.data[1][2] = 2 * orientation.j * orientation.k -
		2 * orientation.r * orientation.i;

	transformMatrix.data[1][3] = position.getY();

	transformMatrix.data[2][0] = 2 * orientation.i * orientation.k -
		2 * orientation.r * orientation.j;

	transformMatrix.data[2][1] = 2 * orientation.j * orientation.k +
		2 * orientation.r * orientation.i;

	transformMatrix.data[2][2] = 1 - 2 * orientation.i * orientation.i -
		2 * orientation.j * orientation.j;

	transformMatrix.data[2][3] = position.getZ();
}
