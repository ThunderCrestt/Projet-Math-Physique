#pragma once
#ifndef CYCLONE_CONTACTS_H
#define CYCLONE_CONTACTS_H

#include "RigidBody.h"
#include "Vector3D.h"

    class ContactResolver;


    //Cette classe represente 2 corps en contact. Le but est de relever deux contact et de venir 
    //changer les impulsions des corps pour réagir au contact

    class Contact
    {
        //Accès a la classe contactResolver
        friend class ContactResolver;

    public:
        //les deux rigid body liés au contact
        RigidBody* body[2];

        //coefficient de friction au contact 
        float friction;

        //coefficient de restitution au contact
        float restitution;

        //position du contact dans world
        Vector3D contactPoint;

        //Direction du contact en coordonées "world"
        Vector3D contactNormal;

        // profondeur de penetration au point de contact
        float penetration;

        //set les variables qui ne dependent normalement pas du point de contact
        void setBodyData(RigidBody* one, RigidBody* two,
            float friction=0, float restitution=1);

    protected:

        //matrice de transformation pour passer du referenciel contact a world (les colonnes donnent un ensemble de vecteurs orthonormal)
        Matrix3 contactToWorld;

        //Vitesse de fermeture au point de contact
        Vector3D contactVelocity;

        //velocité desiré pour resoudre le contact
        float desiredDeltaVelocity;

        //position spatial dans world qui est relative au centre de chaque rigidbody
        Vector3D relativeContactPosition[2];

    protected:

        //calcul des données interne (appelé avant que l'algorithme tente de resoude quoi que ce soit)
        void calculateInternals(float duration);

        //renverse le contact
        void swapBodies();

        //update l'état "awake" des rigidBodies qui intervienne dans le contact
        void matchAwakeState();

        //calcul et set la valeur interne de delta velocity
        void calculateDesiredDeltaVelocity(float duration);

        //calcul et retourne la velocité du point de contact sur le rigidBody donnée
        Vector3D calculateLocalVelocity(unsigned bodyIndex, float duration);

        //calcul une base orthonormale pour le point de contact
        void calculateContactBasis();


    };

   




#endif