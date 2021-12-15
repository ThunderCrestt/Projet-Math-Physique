#include "RigidBody.h"

RigidBody::RigidBody(Vector3D *position, Quaternion orientation, float mass, float damping, float angularDamping, Matrix3 tenseurInertie) : _position(*position), _orientation(orientation), _inverseMass(1 / mass), _damping(damping), _angularDamping(angularDamping),
_accumForce(Vector3D(0, 0, 0)), _accumTorque(Vector3D(0, 0, 0)){
	this->setInverseInertiaTensor(tenseurInertie);
}
void RigidBody::setAwake(const bool awake)
{
	if (awake) {
		isAwake = true;

		// Add a bit of motion to avoid it falling asleep immediately.
		motion = sleepEpsilon * 2.0f;
	}
	else {
		isAwake = false;
		this->getVelocity().clear();
		this->getRotation().clear();
	}
}
bool RigidBody::getAwake()
{
	return isAwake;
}

void RigidBody::addVelocity(const Vector3D& deltaVelocity)
{
	_speed = _speed + deltaVelocity;
}

void RigidBody::addRotation(const Vector3D& deltaRotation)
{
	_rotation = _rotation+ deltaRotation;
}
Vector3D RigidBody::getRotation()
{
	return this->_rotation;
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
void RigidBody::getPosition(Vector3D* position) const
{
	*position = RigidBody::_position;
}	
Vector3D RigidBody::getVelocity()
{
	return _speed;
}
Vector3D RigidBody::getAcceleration()
{
	return _acceleration;
}

float  RigidBody::getMass()
{
	return 1 / _inverseMass;
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

void RigidBody::setRotation(const float x, const float y, const float z)
{
	_rotation.setX(x);
	_rotation.setY(y);
	_rotation.setZ(z);
}
void RigidBody::setRotation(const Vector3D& rotation)
{
	RigidBody::_rotation = rotation;
}
void RigidBody::setAcceleration(Vector3D const& vector)
{
	this->_acceleration = vector;
}


void RigidBody::integrer(float time)
{

    Vector3D _linearAccel =_accumForce  * _inverseMass ;
    Vector3D _angularAccel = _inverseInertiaTensorW * _accumTorque;
    
    _speed = _speed +_linearAccel * time;
    _rotation = _rotation +_angularAccel * time;


    
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
	
	if (canSleep) {
		float currentMotion = _speed.scalarProduct(_speed) +
			_rotation.scalarProduct(_rotation);

		float bias = pow(0.5, time);
		motion = bias * motion + (1 - bias) * currentMotion;

		if (motion < sleepEpsilon) setAwake(false);
		else if (motion > 10 * sleepEpsilon) motion = 10 * sleepEpsilon;
	}

}
void RigidBody::getLastFrameAcceleration(Vector3D* acceleration) const
{
	*acceleration = lastFrameAcceleration;
}

Vector3D RigidBody::getLastFrameAcceleration() const
{
	return lastFrameAcceleration;
}
void RigidBody::clearAccumulator()
{
	 _accumForce = Vector3D(0,0,0);
    _accumTorque = Vector3D(0,0,0);
    _orientation.normalize();
}
void RigidBody::addForce(const Vector3D& force)
{
	_accumForce = _accumForce+ force;
}
void RigidBody::addForceAtBodyPoint(Vector3D& force, Vector3D& point)
{
	Vector3D pointMonde = _transformMatrix*point;
    addForceAtPoint(force, pointMonde);
}
void RigidBody::addForceAtPoint(Vector3D& force, Vector3D& point)
{
	addForce( force);
	_accumTorque = _accumTorque+ (point - _position).vectorProduct(force);
}


//Code à décommenter lors de l'implémentation des matrices,quaternion
Matrix3 RigidBody::getInverseInertiaTensor() const
{
	return this->_inverseInertiaTensorL;
}

void RigidBody::getInverseInertiaTensorWorld(Matrix3* inverseInertiaTensor) const
{
	*inverseInertiaTensor =  this->_inverseInertiaTensorW;

}

Matrix3 RigidBody::getInverseInertiaTensorWorld() const
{
	return this->_inverseInertiaTensorW;
}

Matrix4 RigidBody::getTransformMatrix()
{
	return _transformMatrix;
}

Quaternion RigidBody::getOrientation()
{
	return _orientation;
}
void RigidBody::getOrientation(Quaternion* orientation) const
{
	*orientation = RigidBody::_orientation;
}

Quaternion RigidBody::getOrientation() const
{
	return _orientation;
}

void RigidBody::getOrientation(Matrix3* matrix) const
{
	getOrientation(matrix->data);
}
void RigidBody::getOrientation(std::array<std::array<float, 3>, 3> matrix) const
{
	matrix[0][0] = _transformMatrix.data[0][0];
	matrix[0][1] = _transformMatrix.data[0][1];
	matrix[0][2] = _transformMatrix.data[0][2];

	matrix[1][0] = _transformMatrix.data[1][0];
	matrix[1][1] = _transformMatrix.data[1][1];
	matrix[1][2] = _transformMatrix.data[1][2];

	matrix[2][0] = _transformMatrix.data[2][0];
	matrix[2][1] = _transformMatrix.data[2][1];
	matrix[2][2] = _transformMatrix.data[2][2];
}


void RigidBody::setInverseInertiaTensor(const Matrix3 &inertiaTensor)
{
	_inverseInertiaTensorL.setInverse(inertiaTensor);
}

void RigidBody::setTransformMatrix(Matrix4 matrix)
{
	this->_transformMatrix = matrix;
}

void RigidBody::setOrientation(Quaternion orientation)
{
	this->_orientation = orientation;
}

void RigidBody::calculateDerivedData()
{
// Calculate the transform matrix for the body.
calculateTransformMatrix(_transformMatrix, _position, _orientation);
}

void RigidBody::tenseurInertiaLocalToWorld(Matrix3& inertiaTenseurWorld)
{
	_inverseInertiaTensorW = convertMatrix4to3(_transformMatrix)* inertiaTenseurWorld ;
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

Matrix3 RigidBody::convertMatrix4to3(Matrix4 matrix)
{
	return Matrix3({ {{matrix.data[0][0],matrix.data[0][1],matrix.data[0][2]},{matrix.data[1][0],matrix.data[1][1],matrix.data[1][2]},{matrix.data[2][0],matrix.data[2][1],matrix.data[2][2]}} });
}
