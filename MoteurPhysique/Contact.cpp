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
