#include "Vector3D.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "Quaternion.h"
class RigidBody
{

private:

    float _inverseMass;
    float _damping;
	float _linearDamping;
    float _angularDamping;
    

	Vector3D _position;
	Vector3D _speed;
    Vector3D _acceleration; 
    Vector3D _rotation;
    Vector3D _accumForce;
    Vector3D _accumTorque;

//Code à décommenter lors de l'implémentation des matrices,quaternion

   Matrix3 inverseInertiaTensor;
   Matrix4 _transformMatrix;
   Quaternion _orientation;

public:

   

    //getter si besoin
    float getInverseMass();
	float getDamping();
    float getLinearDamping();

    Vector3D getPosition();
	Vector3D getVelocity();
	Vector3D getAcceleration();



    //setter si besoin
    void setInverseMass(float inverseMass);
	void setDamping(float damping);
    void setLinearDamping(float lineardamping);
	void setPosition(Vector3D const& vector);
	void setVelocity(Vector3D const& vector);
	void setAcceleration(Vector3D const& vector);
   


    //méthod pour la gestion du rigidbody
    void integrer(float time);
	void addForce(Vector3D& vector);
    void addForceAtPoint ( Vector3D& force , Vector3D& point );
    void addForceAtBodyPoint ( Vector3D& force , Vector3D& point );

    

    void calculateDerivedData();
    void clearAccumulator();  


//Code à décommenter lors de l'implémentation des matrices,quaternion

    RigidBody(Vector3D position, Quaternion orientation, float mass, float damping, float angularDamping, Matrix3 tenseurInertie);
    Matrix4 getTransformMatrix();
    Quaternion getOrientation();
    void setInverseInertiaTensor(const Matrix3 &inertiaTensor);
    void setTransformMatrix(Matrix4 matrix);
    void setOrientation();
    void calculateTransformMatrix(Matrix4& transformMatrix, const Vector3D& position, const Quaternion& orientation);

};