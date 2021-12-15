#ifndef CYCLONE_COLLISION_FINE_H
#define CYCLONE_COLLISION_FINE_H

#include "Contact.h"
#include "Vector3D.h"
#include "CollisionData.h"
    // D�claration avanc� des classes aux m�thodes statiques
    class IntersectionTests;
    class CollisionDetector;

    /**
     * Repr�sente une primitive
     */
    class CollisionPrimitive
    {
    public:
        /**
         *Cette classe est utilis� pour simplifier les collisionDetector 
         */
        friend class IntersectionTests;
        friend class CollisionDetector;

        /**
         * Tle rigiBody repr�sent� par la primitive
         */
        RigidBody* body;

        /**
         * l'offset de la primitive par rapport au rigidBody
         */
        Matrix4 offset;

        /**
         * CalculIntene
         */
        void calculateInternals();

        /**
         * fonction purement ici pour rendre pratique le getAxis
         */
        Vector3D getAxis(unsigned index) const
        {
            return transform.getAxisVector(index);
        }

        /**
            *retourne la transformMatrix calcul� � partir du rigidBody et de l'offset
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
         * contient la matrice de transformation
         * */
        Matrix4 transform;
    };

    /**
     * repr�sente une primitive en forme de sph�re
     */
    class CollisionSphere : public CollisionPrimitive
    {
    public:
        /**
         * rayon de la sph�re
         */
        float radius;
        //TODO : create constructeur 
        CollisionSphere(){}
        CollisionSphere( RigidBody& rb, const Matrix4& offset,float radius);

    };

    /**
     * pas une primitive : n'a pas de rigidBody il est juste utilis� pour repr�senter les objets non mouvants (mur ...)
     */
    class CollisionPlane
    {
    public:
        /**
         * la normal du plan
         */
        Vector3D direction;

        /**
         * la distance du plan depuis l'origine
         */
        float offset;
    };

    /**
     * repr�sente un rigidBody en forme de boite
     */
    class CollisionBox : public CollisionPrimitive
    {
    public:
        /**
         * contient les demi longueur sur chaque axe
         */
        Vector3D halfSize;
    };

   

    /**
    * d�tecte les collisions de mani�re diff�rentes en fonctions des primitives
    */
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

    /**
    * Juste une petite classe de test qui les conduit rapidement
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

        static bool boxAndHalfSpace(
            const CollisionBox& box,
            const CollisionPlane& plane);
    };
#endif // CYCLONE_COLLISION_FINE_H
