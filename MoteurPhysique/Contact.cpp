#include "Contact.h"
#include <memory.h>
#include <assert.h>


// implémentation du contact

void Contact::setBodyData(RigidBody* one, RigidBody* two,
    float friction, float restitution)
{
    Contact::body[0] = one;
    Contact::body[1] = two;
    Contact::friction = friction;
    Contact::restitution = restitution;
}

void Contact::matchAwakeState()
{
    //les collisions avec le monde ne cause pas le rigidBody de se reveiller.
    if (!body[1]) return;

    bool body0awake = body[0]->getAwake();
    bool body1awake = body[1]->getAwake();

    // On réveil que ceux qui sont endormi
    if (body0awake ^ body1awake) {
        if (body0awake) body[1]->setAwake();
        else body[0]->setAwake();
    }
}

/*
 * on échange les rigidBody
 */
void Contact::swapBodies()
{
    contactNormal = contactNormal*-1;

    RigidBody* temp = body[0];
    body[0] = body[1];
    body[1] = temp;
}

/*
 * Construit une base orthonormale pour le contact.
 * la base est stocké dans une matrice 3 ou chaque colonne représente un vecteur
 * X est calculé selon la normale et Y et Z sont calculé selon la règle de la main droite
 */
inline
void Contact::calculateContactBasis()
{
    Vector3D contactTangent[2];

    //Est ce que z est plus proche de x ou y ?
    if (abs(contactNormal.getX()) > abs(contactNormal.getY()))
    {
        // un facteur pour normalisé
        const float s = (float)1.0f / sqrt(contactNormal.getZ() * contactNormal.getZ() +
            contactNormal.getX() * contactNormal.getX());

        //le nouveau axe X est perpendiculaire à l'axe world Y
        contactTangent[0].setX(  contactNormal.getZ() * s);
        contactTangent[0].setY(0);
        contactTangent[0].setZ(-contactNormal.getX() * s);

        //le nouveau axe Y est perpendiculaire au nouveau X et Z
        contactTangent[1].setX(contactNormal.getY() * contactTangent[0].getX());
        contactTangent[1].setY( contactNormal.getZ() * contactTangent[0].getX() -
            contactNormal.getX() * contactTangent[0].getZ());
        contactTangent[1].setZ(-contactNormal.getY() * contactTangent[0].getX());
    }
    else
    {
        // un facteur pour normalisé
        const float s = (float)1.0f / sqrt(contactNormal.getZ() * contactNormal.getZ() +
            contactNormal.getY() * contactNormal.getY());

        //le nouveau axe X est perpendiculaire à l'axe world Y
        contactTangent[0].setX(0);
        contactTangent[0].setY(-contactNormal.getZ() * s);
        contactTangent[0].setZ(contactNormal.getY() * s);

        //le nouveau axe Y est perpendiculaire au nouveau X et Z
        contactTangent[1].setX( contactNormal.getY() * contactTangent[0].getZ() -
            contactNormal.getZ() * contactTangent[0].getY());
        contactTangent[1].setY( -contactNormal.getX() * contactTangent[0].getZ());
        contactTangent[1].setZ( contactNormal.getX() * contactTangent[0].getY());
    }

    // Make a matrix from the three vectors.
    contactToWorld.setComponents(
        contactNormal,
        contactTangent[0],
        contactTangent[1]);
}

Vector3D Contact::calculateLocalVelocity(unsigned bodyIndex, float duration)
{
    RigidBody* thisBody = body[bodyIndex];

    //calcul de la vélocité au point de contact
    Vector3D velocity =
        thisBody->getRotation() % relativeContactPosition[bodyIndex];
    velocity = velocity+ thisBody->getVelocity();

    // la vélocité est transformé dans la base de  coordonnées du contact
    Vector3D contactVelocity = contactToWorld.transformTranspose(velocity);

    Vector3D accVelocity = thisBody->getLastFrameAcceleration() * duration;

    // la vélocité est transformé dans la base de  coordonnées du contact
    accVelocity = contactToWorld.transformTranspose(accVelocity);


    accVelocity.setX(0);


    contactVelocity =contactVelocity+ accVelocity;

    return contactVelocity;
}


void Contact::calculateDesiredDeltaVelocity(float duration)
{
    const static float velocityLimit = (float)0.25f;

    // on calcul la vélocité depuis l'accélération de cette frame
    float velocityFromAcc = 0;

    if (body[0]->getAwake())
    {
        velocityFromAcc +=
            body[0]->getLastFrameAcceleration() * duration * contactNormal;
    }

    if (body[1] && body[1]->getAwake())
    {
        velocityFromAcc -=
            body[1]->getLastFrameAcceleration() * duration * contactNormal;
    }

    // si vélocité très faible on limite la restitution
    float thisRestitution = restitution;
    if (abs(contactVelocity.getX()) < velocityLimit)
    {
        thisRestitution = (float)0.0f;
    }

    // on combine les vélocités
    desiredDeltaVelocity =
        -contactVelocity.getX()
        - thisRestitution * (contactVelocity.getX() - velocityFromAcc);
}


void Contact::calculateInternals(float duration)
{
    //si premier objet null on swap
    if (!body[0]) swapBodies();
    assert(body[0]);

    calculateContactBasis();

    // sauvegarde de la position du contact en fonction du rigidBody
    relativeContactPosition[0] = contactPoint - body[0]->getPosition();
    if (body[1]) {
        relativeContactPosition[1] = contactPoint - body[1]->getPosition();
    }

    //cherche la vélocité des body au point de contact
    contactVelocity = calculateLocalVelocity(0, duration);
    if (body[1]) {
        contactVelocity =contactVelocity- calculateLocalVelocity(1, duration);
    }

    // calcul le changement de vélocité pour la résolution
    calculateDesiredDeltaVelocity(duration);
}

void Contact::applyVelocityChange(Vector3D velocityChange[2],
    Vector3D rotationChange[2])
{
    //contient les inverseInteriaTensor en coordonnées monde
    Matrix3 inverseInertiaTensor[2];
    body[0]->getInverseInertiaTensorWorld(&inverseInertiaTensor[0]);
    if (body[1])
        body[1]->getInverseInertiaTensorWorld(&inverseInertiaTensor[1]);

    // on calcul une impulsion pour chaque contact
    Vector3D impulseContact;


        // on utilise un format plus simple si pas de friction
        impulseContact = calculateFrictionlessImpulse(inverseInertiaTensor);
    


    //On convertit l'impulsion en coordonnées monde
    Vector3D impulse = contactToWorld.transform(impulseContact);

    // On sépare la composante linéaire et rotationnel de l'impulsion
    Vector3D impulsiveTorque = relativeContactPosition[0] % impulse;
    rotationChange[0] = inverseInertiaTensor[0].transform(impulsiveTorque);
    velocityChange[0].clear();
    velocityChange[0]=velocityChange[0]+ impulse*body[0]->getInverseMass();

    // on applique la vélocité
    body[0]->addVelocity(velocityChange[0]);
    body[0]->addRotation(rotationChange[0]);

    if (body[1])
    {
        Vector3D impulsiveTorque = impulse % relativeContactPosition[1];
        rotationChange[1] = inverseInertiaTensor[1].transform(impulsiveTorque);
        velocityChange[1].clear();
        velocityChange[1].addScaledVector(impulse, -body[1]->getInverseMass());

        body[1]->addVelocity(velocityChange[1]);
        body[1]->addRotation(rotationChange[1]);
    }
}

inline
Vector3D Contact::calculateFrictionlessImpulse(Matrix3* inverseInertiaTensor)
{
    Vector3D impulseContact;

    Vector3D deltaVelWorld = relativeContactPosition[0] % contactNormal;
    deltaVelWorld = inverseInertiaTensor[0].transform(deltaVelWorld);
    deltaVelWorld = deltaVelWorld % relativeContactPosition[0];

    //calcul la vélocité en coordonnées locale ( contact)
    float deltaVelocity = deltaVelWorld * contactNormal;

    // ajout de la composante linéaire à la vitesse
    deltaVelocity += body[0]->getInverseMass();

    // Check si on a besoin du body 2
    if (body[1])
    {
        // même transformation
        Vector3D deltaVelWorld = relativeContactPosition[1] % contactNormal;
        deltaVelWorld = inverseInertiaTensor[1].transform(deltaVelWorld);
        deltaVelWorld = deltaVelWorld % relativeContactPosition[1];

        // Ajout des changement du à la rotation
        deltaVelocity += deltaVelWorld * contactNormal;

        //ajout des changement du aux mouvements linéaires
        deltaVelocity += body[1]->getInverseMass();
    }

    // calcul de l'impulsion
    impulseContact.setX( desiredDeltaVelocity / deltaVelocity);
    impulseContact.setY(0);
    impulseContact.setZ( 0);
    return impulseContact;
}

void Contact::applyPositionChange(Vector3D linearChange[2],
    Vector3D angularChange[2],
    float penetration)
{
    const float angularLimit = (float)0.2f;
    float angularMove[2];
    float linearMove[2];

    float totalInertia = 0;
    float linearInertia[2];
    float angularInertia[2];

    // We need to work out the inertia of each object in the direction
    // of the contact normal, due to angular inertia only.
    for (unsigned i = 0; i < 2; i++) if (body[i])
    {
        Matrix3 inverseInertiaTensor;
        body[i]->getInverseInertiaTensorWorld(&inverseInertiaTensor);

        // Use the same procedure as for calculating frictionless
        // velocity change to work out the angular inertia.
        Vector3D angularInertiaWorld =
            relativeContactPosition[i] % contactNormal;
        angularInertiaWorld =
            inverseInertiaTensor.transform(angularInertiaWorld);
        angularInertiaWorld =
            angularInertiaWorld % relativeContactPosition[i];
        angularInertia[i] =
            angularInertiaWorld * contactNormal;

        // The linear component is simply the inverse mass
        linearInertia[i] = body[i]->getInverseMass();

        // Keep track of the total inertia from all components
        totalInertia += linearInertia[i] + angularInertia[i];

        // We break the loop here so that the totalInertia value is
        // completely calculated (by both iterations) before
        // continuing.
    }

    // Loop through again calculating and applying the changes
    for (unsigned i = 0; i < 2; i++) if (body[i])
    {
        // The linear and angular movements required are in proportion to
        // the two inverse inertias.
        float sign = (i == 0) ? 1 : -1;
        angularMove[i] =
            sign * penetration * (angularInertia[i] / totalInertia);
        linearMove[i] =
            sign * penetration * (linearInertia[i] / totalInertia);

        // To avoid angular projections that are too great (when mass is large
        // but inertia tensor is small) limit the angular move.
        Vector3D projection = relativeContactPosition[i];
        projection.addScaledVector(
            contactNormal,
            -relativeContactPosition[i].scalarProduct(contactNormal)
        );

        // Use the small angle approximation for the sine of the angle (i.e.
        // the magnitude would be sine(angularLimit) * projection.magnitude
        // but we approximate sine(angularLimit) to angularLimit).
        float maxMagnitude = angularLimit * projection.getNorm();

        if (angularMove[i] < -maxMagnitude)
        {
            float totalMove = angularMove[i] + linearMove[i];
            angularMove[i] = -maxMagnitude;
            linearMove[i] = totalMove - angularMove[i];
        }
        else if (angularMove[i] > maxMagnitude)
        {
            float totalMove = angularMove[i] + linearMove[i];
            angularMove[i] = maxMagnitude;
            linearMove[i] = totalMove - angularMove[i];
        }

        // We have the linear amount of movement required by turning
        // the rigid body (in angularMove[i]). We now need to
        // calculate the desired rotation to achieve that.
        if (angularMove[i] == 0)
        {
            // Easy case - no angular movement means no rotation.
            angularChange[i].clear();
        }
        else
        {
            // Work out the direction we'd like to rotate in.
            Vector3D targetAngularDirection =
                relativeContactPosition[i].vectorProduct(contactNormal);

            Matrix3 inverseInertiaTensor;
            body[i]->getInverseInertiaTensorWorld(&inverseInertiaTensor);

            // Work out the direction we'd need to rotate to achieve that
            angularChange[i] =
                inverseInertiaTensor.transform(targetAngularDirection) *
                (angularMove[i] / angularInertia[i]);
        }

        // Velocity change is easier - it is just the linear movement
        // along the contact normal.
        linearChange[i] = contactNormal * linearMove[i];

        // Now we can start to apply the values we've calculated.
        // Apply the linear movement
        Vector3D pos;
        body[i]->getPosition(&pos);
        pos.addScaledVector(contactNormal, linearMove[i]);
        body[i]->setPosition(pos);

        // And the change in orientation
        Quaternion q;
        body[i]->getOrientation(&q);
        q.addScaledVector(angularChange[i], ((float)1.0));
        body[i]->setOrientation(q);

        // We need to calculate the derived data for any body that is
        // asleep, so that the changes are reflected in the object's
        // data. Otherwise the resolution will not change the position
        // of the object, and the next collision detection round will
        // have the same penetration.
        if (!body[i]->getAwake()) body[i]->calculateDerivedData();
    }
}