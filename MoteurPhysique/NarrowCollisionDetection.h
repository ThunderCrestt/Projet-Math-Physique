#ifndef CYCLONE_COLLISION_FINE_H
#define CYCLONE_COLLISION_FINE_H

#include "Contact.h"
#include "Vector3D.h"
#include "CollisionData.h"
    // Forward declarations of primitive friends
    class IntersectionTests;
    class CollisionDetector;

    /**
     * Represents a primitive to detect collisions against.
     */
    class CollisionPrimitive
    {
    public:
        /**
         * This class exists to help the collision detector
         * and intersection routines, so they should have
         * access to its data.
         */
        friend class IntersectionTests;
        friend class CollisionDetector;

        /**
         * The rigid body that is represented by this primitive.
         */
        RigidBody* body;

        /**
         * The offset of this primitive from the given rigid body.
         */
        Matrix4 offset;

        /**
         * Calculates the internals for the primitive.
         */
        void calculateInternals();

        /**
         * This is a convenience function to allow access to the
         * axis vectors in the transform for this primitive.
         */
        Vector3D getAxis(unsigned index) const
        {
            return transform.getAxisVector(index);
        }

        /**
         * Returns the resultant transform of the primitive, calculated from
         * the combined offset of the primitive and the transform
         * (orientation + position) of the rigid body to which it is
         * attached.
         */
        const Matrix4& getTransform() const
        {
            return transform;
        }
        //TODO : create constructeur y
        CollisionPrimitive()
        {

        }
        CollisionPrimitive( RigidBody& rb, const Matrix4& offset);



    protected:
        /**
         * The resultant transform of the primitive. This is
         * calculated by combining the offset of the primitive
         * with the transform of the rigid body.
         */
        Matrix4 transform;
    };

    /**
     * Represents a rigid body that can be treated as a sphere
     * for collision detection.
     */
    class CollisionSphere : public CollisionPrimitive
    {
    public:
        /**
         * The radius of the sphere.
         */
        float radius;
        //TODO : create constructeur 
        CollisionSphere(){}
        CollisionSphere( RigidBody& rb, const Matrix4& offset,float radius);

    };

    /**
     * The plane is not a primitive: it doesn't represent another
     * rigid body. It is used for contacts with the immovable
     * world geometry.
     */
    class CollisionPlane
    {
    public:
        /**
         * The plane normal
         */
        Vector3D direction;

        /**
         * The distance of the plane from the origin.
         */
        float offset;
    };

    /**
     * Represents a rigid body that can be treated as an aligned bounding
     * box for collision detection.
     */
    class CollisionBox : public CollisionPrimitive
    {
    public:
        /**
         * Holds the half-sizes of the box along each of its local axes.
         */
        Vector3D halfSize;
    };

    /**
     * A wrapper class that holds fast intersection tests. These
     * can be used to drive the coarse collision detection system or
     * as an early out in the full collision tests below.
     */
    class IntersectionTests
    {
    public:

        static bool sphereAndHalfSpace(
            const CollisionSphere& sphere,
            const CollisionPlane& plane);

        static bool sphereAndSphere(
            const CollisionSphere& one,
            const CollisionSphere& two);

        static bool boxAndBox(
            const CollisionBox& one,
            const CollisionBox& two);

        /**
         * Does an intersection test on an arbitrarily aligned box and a
         * half-space.
         *
         * The box is given as a transform matrix, including
         * position, and a vector of half-sizes for the extend of the
         * box along each local axis.
         *
         * The half-space is given as a direction (i.e. unit) vector and the
         * offset of the limiting plane from the origin, along the given
         * direction.
         */
        static bool boxAndHalfSpace(
            const CollisionBox& box,
            const CollisionPlane& plane);
    };


    class CollisionDetector
    {
    public:
        static unsigned generateContact(CollisionPrimitive* prim1, CollisionPrimitive* prim2, CollisionData* data);


        static unsigned sphereAndHalfSpace(
            const CollisionSphere& sphere,
            const CollisionPlane& plane,
            CollisionData* data
        );

        static unsigned sphereAndTruePlane(
            const CollisionSphere& sphere,
            const CollisionPlane& plane,
            CollisionData* data
        );

        static unsigned sphereAndSphere(
            const CollisionSphere& one,
            const CollisionSphere& two,
            CollisionData* data
        );

        /**
         * Does a collision test on a collision box and a plane representing
         * a half-space (i.e. the normal of the plane
         * points out of the half-space).
         */
        static unsigned boxAndHalfSpace(
            const CollisionBox& box,
            const CollisionPlane& plane,
            CollisionData* data
        );

        static unsigned boxAndBox(
            const CollisionBox& one,
            const CollisionBox& two,
            CollisionData* data
        );

        static unsigned boxAndPoint(
            const CollisionBox& box,
            const Vector3D& point,
            CollisionData* data
        );

        static unsigned boxAndSphere(
            const CollisionBox& box,
            const CollisionSphere& sphere,
            CollisionData* data
        );
    };


#endif // CYCLONE_COLLISION_FINE_H
