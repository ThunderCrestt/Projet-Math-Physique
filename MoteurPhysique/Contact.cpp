#include "Contact.h"
/*
 * Implementation file for the contact resolution system.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under licence. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software licence.
 */

#include <memory.h>
#include <assert.h>


// Contact implementation

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
    // Collisions with the world never cause a body to wake up.
    if (!body[1]) return;

    bool body0awake = body[0]->getAwake();
    bool body1awake = body[1]->getAwake();

    // Wake up only the sleeping one
    if (body0awake ^ body1awake) {
        if (body0awake) body[1]->setAwake();
        else body[0]->setAwake();
    }
}

/*
 * Swaps the bodies in the current contact, so body 0 is at body 1 and
 * vice versa. This also changes the direction of the contact normal,
 * but doesn't update any calculated internal data. If you are calling
 * this method manually, then call calculateInternals afterwards to
 * make sure the internal data is up to date.
 */
void Contact::swapBodies()
{
    contactNormal = contactNormal*-1;

    RigidBody* temp = body[0];
    body[0] = body[1];
    body[1] = temp;
}

/*
 * Constructs an arbitrary orthonormal basis for the contact.  This is
 * stored as a 3x3 matrix, where each vector is a column (in other
 * words the matrix transforms contact space into world space). The x
 * direction is generated from the contact normal, and the y and z
 * directionss are set so they are at right angles to it.
 */
inline
void Contact::calculateContactBasis()
{
    Vector3D contactTangent[2];

    // Check whether the Z-axis is nearer to the X or Y axis
    if (abs(contactNormal.getX()) > abs(contactNormal.getY()))
    {
        // Scaling factor to ensure the results are normalised
        const float s = (float)1.0f / sqrt(contactNormal.getZ() * contactNormal.getZ() +
            contactNormal.getX() * contactNormal.getX());

        // The new X-axis is at right angles to the world Y-axis
        contactTangent[0].setX(  contactNormal.getZ() * s);
        contactTangent[0].setY(0);
        contactTangent[0].setZ(-contactNormal.getX() * s);

        // The new Y-axis is at right angles to the new X- and Z- axes
        contactTangent[1].setX(contactNormal.getY() * contactTangent[0].getX());
        contactTangent[1].setY( contactNormal.getZ() * contactTangent[0].getX() -
            contactNormal.getX() * contactTangent[0].getZ());
        contactTangent[1].setZ(-contactNormal.getY() * contactTangent[0].getX());
    }
    else
    {
        // Scaling factor to ensure the results are normalised
        const float s = (float)1.0f / sqrt(contactNormal.getZ() * contactNormal.getZ() +
            contactNormal.getY() * contactNormal.getY());

        // The new X-axis is at right angles to the world X-axis
        contactTangent[0].setX(0);
        contactTangent[0].setY(-contactNormal.getZ() * s);
        contactTangent[0].setZ(contactNormal.getY() * s);

        // The new Y-axis is at right angles to the new X- and Z- axes
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

    // Work out the velocity of the contact point.
    Vector3D velocity =
        thisBody->getRotation() % relativeContactPosition[bodyIndex];
    velocity = velocity+ thisBody->getVelocity();

    // Turn the velocity into contact-coordinates.
    Vector3D contactVelocity = contactToWorld.transformTranspose(velocity);

    // Calculate the ammount of velocity that is due to forces without
    // reactions.
    Vector3D accVelocity = thisBody->getLastFrameAcceleration() * duration;

    // Calculate the velocity in contact-coordinates.
    accVelocity = contactToWorld.transformTranspose(accVelocity);

    // We ignore any component of acceleration in the contact normal
    // direction, we are only interested in planar acceleration
    accVelocity.setX(0);

    // Add the planar velocities - if there's enough friction they will
    // be removed during velocity resolution
    contactVelocity =contactVelocity+ accVelocity;

    // And return it
    return contactVelocity;
}


void Contact::calculateDesiredDeltaVelocity(float duration)
{
    const static float velocityLimit = (float)0.25f;

    // Calculate the acceleration induced velocity accumulated this frame
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

    // If the velocity is very slow, limit the restitution
    float thisRestitution = restitution;
    if (abs(contactVelocity.getX()) < velocityLimit)
    {
        thisRestitution = (float)0.0f;
    }

    // Combine the bounce velocity with the removed
    // acceleration velocity.
    desiredDeltaVelocity =
        -contactVelocity.getX()
        - thisRestitution * (contactVelocity.getX() - velocityFromAcc);
}


void Contact::calculateInternals(float duration)
{
    // Check if the first object is NULL, and swap if it is.
    if (!body[0]) swapBodies();
    assert(body[0]);

    // Calculate an set of axis at the contact point.
    calculateContactBasis();

    // Store the relative position of the contact relative to each body
    relativeContactPosition[0] = contactPoint - body[0]->getPosition();
    if (body[1]) {
        relativeContactPosition[1] = contactPoint - body[1]->getPosition();
    }

    // Find the relative velocity of the bodies at the contact point.
    contactVelocity = calculateLocalVelocity(0, duration);
    if (body[1]) {
        contactVelocity =contactVelocity- calculateLocalVelocity(1, duration);
    }

    // Calculate the desired change in velocity for resolution
    calculateDesiredDeltaVelocity(duration);
}

void Contact::applyVelocityChange(Vector3D velocityChange[2],
    Vector3D rotationChange[2])
{
    // Get hold of the inverse mass and inverse inertia tensor, both in
    // world coordinates.
    Matrix3 inverseInertiaTensor[2];
    body[0]->getInverseInertiaTensorWorld(&inverseInertiaTensor[0]);
    if (body[1])
        body[1]->getInverseInertiaTensorWorld(&inverseInertiaTensor[1]);

    // We will calculate the impulse for each contact axis
    Vector3D impulseContact;

    if (friction == (float)0.0)
    {
        // Use the short format for frictionless contacts
        impulseContact = calculateFrictionlessImpulse(inverseInertiaTensor);
    }
    else
    {
        // Otherwise we may have impulses that aren't in the direction of the
        // contact, so we need the more complex version.
        impulseContact = calculateFrictionImpulse(inverseInertiaTensor);
    }

    // Convert impulse to world coordinates
    Vector3D impulse = contactToWorld.transform(impulseContact);

    // Split in the impulse into linear and rotational components
    Vector3D impulsiveTorque = relativeContactPosition[0] % impulse;
    rotationChange[0] = inverseInertiaTensor[0].transform(impulsiveTorque);
    velocityChange[0].clear();
    velocityChange[0]=velocityChange[0]+ impulse*body[0]->getInverseMass();

    // Apply the changes
    body[0]->addVelocity(velocityChange[0]);
    body[0]->addRotation(rotationChange[0]);

    if (body[1])
    {
        // Work out body one's linear and angular changes
        Vector3D impulsiveTorque = impulse % relativeContactPosition[1];
        rotationChange[1] = inverseInertiaTensor[1].transform(impulsiveTorque);
        velocityChange[1].clear();
        velocityChange[1].addScaledVector(impulse, -body[1]->getInverseMass());

        // And apply them.
        body[1]->addVelocity(velocityChange[1]);
        body[1]->addRotation(rotationChange[1]);
    }
}

inline
Vector3D Contact::calculateFrictionlessImpulse(Matrix3* inverseInertiaTensor)
{
    Vector3D impulseContact;

    // Build a vector that shows the change in velocity in
    // world space for a unit impulse in the direction of the contact
    // normal.
    Vector3D deltaVelWorld = relativeContactPosition[0] % contactNormal;
    deltaVelWorld = inverseInertiaTensor[0].transform(deltaVelWorld);
    deltaVelWorld = deltaVelWorld % relativeContactPosition[0];

    // Work out the change in velocity in contact coordiantes.
    float deltaVelocity = deltaVelWorld * contactNormal;

    // Add the linear component of velocity change
    deltaVelocity += body[0]->getInverseMass();

    // Check if we need to the second body's data
    if (body[1])
    {
        // Go through the same transformation sequence again
        Vector3D deltaVelWorld = relativeContactPosition[1] % contactNormal;
        deltaVelWorld = inverseInertiaTensor[1].transform(deltaVelWorld);
        deltaVelWorld = deltaVelWorld % relativeContactPosition[1];

        // Add the change in velocity due to rotation
        deltaVelocity += deltaVelWorld * contactNormal;

        // Add the change in velocity due to linear motion
        deltaVelocity += body[1]->getInverseMass();
    }

    // Calculate the required size of the impulse
    impulseContact.setX( desiredDeltaVelocity / deltaVelocity);
    impulseContact.setY(0);
    impulseContact.setZ( 0);
    return impulseContact;
}

inline
Vector3D Contact::calculateFrictionImpulse(Matrix3* inverseInertiaTensor)
{
    Vector3D impulseContact;
    float inverseMass = body[0]->getInverseMass();

    // The equivalent of a cross product in matrices is multiplication
    // by a skew symmetric matrix - we build the matrix for converting
    // between linear and angular quantities.
    Matrix3 impulseToTorque;
    impulseToTorque.setSkewSymmetric(relativeContactPosition[0]);

    // Build the matrix to convert contact impulse to change in velocity
    // in world coordinates.
    Matrix3 deltaVelWorld = impulseToTorque;
    deltaVelWorld = deltaVelWorld*inverseInertiaTensor[0];
    deltaVelWorld = deltaVelWorld * impulseToTorque;
    deltaVelWorld = deltaVelWorld * -1;

    // Check if we need to add body two's data
    if (body[1])
    {
        // Set the cross product matrix
        impulseToTorque.setSkewSymmetric(relativeContactPosition[1]);

        // Calculate the velocity change matrix
        Matrix3 deltaVelWorld2 = impulseToTorque;
        deltaVelWorld2 = deltaVelWorld2 * inverseInertiaTensor[1];
        deltaVelWorld2 = deltaVelWorld2 * impulseToTorque;
        deltaVelWorld2 = deltaVelWorld2 * -1.0f;

        // Add to the total delta velocity.
        deltaVelWorld = deltaVelWorld+ deltaVelWorld2;

        // Add to the inverse mass
        inverseMass += body[1]->getInverseMass();
    }

    // Do a change of basis to convert into contact coordinates.
    Matrix3 deltaVelocity = contactToWorld.transpose();
    deltaVelocity = deltaVelocity* deltaVelWorld;
    deltaVelocity = deltaVelocity*contactToWorld;

    // Add in the linear velocity change
    deltaVelocity.data[0][0] = inverseMass;
    deltaVelocity.data[1][0] = inverseMass;
    deltaVelocity.data[2][0] = inverseMass;

    // Invert to get the impulse needed per unit velocity
    Matrix3 impulseMatrix = deltaVelocity.inverse();

    // Find the target velocities to kill
    Vector3D velKill(desiredDeltaVelocity,
        -contactVelocity.getY(),
        -contactVelocity.getZ());

    // Find the impulse to kill target velocities
    impulseContact = impulseMatrix.transform(velKill);

    // Check for exceeding friction
    float planarImpulse = sqrt(
        impulseContact.getY() * impulseContact.getY() +
        impulseContact.getZ() * impulseContact.getZ()
    );
    if (planarImpulse > impulseContact.getX() * friction)
    {
        // We need to use dynamic friction
        impulseContact.setY(impulseContact.getY()/ planarImpulse);
        impulseContact.setZ(impulseContact.getZ() / planarImpulse);

        impulseContact.setX(deltaVelocity.data[0][0] +
            deltaVelocity.data[0][1] * friction * impulseContact.getY() +
            deltaVelocity.data[0][2] * friction * impulseContact.getZ());
        impulseContact.setX( desiredDeltaVelocity / impulseContact.getX());
        impulseContact.setY( impulseContact.getY()* friction * impulseContact.getX());
        impulseContact.setZ(impulseContact.getZ() * friction * impulseContact.getX());
    }
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