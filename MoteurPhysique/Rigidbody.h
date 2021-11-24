#include "Vector3D.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "Quaternion.h"

#ifndef  RIGIDBODY
#define RIGIDBODY


class RigidBody
{

private:

    float _inverseMass;
    float _damping;
    float _angularDamping;
    
	Vector3D _position;
	Vector3D _speed;
    Vector3D _acceleration; 
    Vector3D _rotation;
    Vector3D _accumForce;
    Vector3D _accumTorque;

   Matrix3 _inverseInertiaTensorL;
   Matrix3 _inverseInertiaTensorW;
   Matrix4 _transformMatrix;
   Quaternion _orientation;

public:

    RigidBody(Vector3D* position, Quaternion orientation, float mass, float damping, float angularDamping, Matrix3 tenseurInertie);


    //getter si besoin
    float getInverseMass();
	float getDamping();
    float getMass();

    Vector3D getPosition();
	Vector3D getVelocity();
	Vector3D getAcceleration();

    Matrix4 getTransformMatrix();
    Quaternion getOrientation();


    //setter si besoin
    void setInverseMass(float inverseMass);
	void setDamping(float damping);
	void setPosition(Vector3D const& vector);
	void setVelocity(Vector3D const& vector);
	void setAcceleration(Vector3D const& vector);
    void setInverseInertiaTensor(const Matrix3& inertiaTensor);
    void setTransformMatrix(Matrix4 matrix);
    void setOrientation(Quaternion orientation);


    //méthod pour la gestion du rigidbody
    void integrer(float time);
	void addForce(const Vector3D& vector);
    void addForceAtPoint ( Vector3D& force , Vector3D& point );
    void addForceAtBodyPoint ( Vector3D& force , Vector3D& point );


    void calculateDerivedData();
    void clearAccumulator();  

    
    void calculateTransformMatrix(Matrix4& transformMatrix, const Vector3D& position, const Quaternion& orientation);
    void tenseurInertiaLocalToWorld(Matrix3& inertiaTenseur);
    Matrix3 convertMatrix4to3(Matrix4 matrix);
}; 

#endif // ! RIGIDBODY
