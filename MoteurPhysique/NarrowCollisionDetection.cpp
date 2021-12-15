#include "NarrowCollisionDetection.h"
#include <memory.h>
#include <assert.h>
#include <cstdlib>
#include <cstdio>
#include <typeinfo>
void CollisionPrimitive::calculateInternals()
{
    transform = body->getTransformMatrix() * offset;
}

CollisionPrimitive::CollisionPrimitive( RigidBody& rb, const Matrix4& offset)
{
    this->body = &rb;
    this->offset = offset;
}
CollisionSphere::CollisionSphere( RigidBody& rb, const Matrix4& offset,float radius) : CollisionPrimitive()
{
    
    this->body = &rb;
    this->offset = offset;
    this->radius = radius;
}
static inline float transformToAxis(
    const CollisionBox& box,
    const Vector3D& axis
)
{
    return
        box.halfSize.getX() * abs(axis.scalarProduct(box.getAxis(0))) +
        box.halfSize.getY() * abs(axis.scalarProduct(box.getAxis(1))) +
        box.halfSize.getZ() * abs(axis.scalarProduct(box.getAxis(2)));
}



//collision Detector implémentation
unsigned CollisionDetector::generateContact(CollisionPrimitive* prim1, CollisionPrimitive* prim2, CollisionData* data)
{
    //TODO : choose wich function to call
    CollisionSphere exSphere;
    CollisionBox exBox;
    CollisionPlane exPlane;
    bool isSameObject = typeid(prim1) == typeid(prim2);
    bool isPrim1Shpere = typeid(prim1) == typeid(exSphere);
    bool isPrim1Plane = typeid(prim1) == typeid(exPlane);
    bool isPrim1Box = typeid(prim1) == typeid(exBox);
    bool isPrim2Shpere = typeid(prim2) == typeid(exSphere);
    bool isPrim2Plane = typeid(prim2) == typeid(exPlane);
    bool isPrim2Box = typeid(prim2) == typeid(exBox);
    if (isSameObject && isPrim1Shpere)
    {
        //sphereAndSphere(*prim1, *prim2, data);
    }
    if (isSameObject && isPrim1Box)
    {

    }
    return 1;
}



unsigned CollisionDetector::sphereAndTruePlane(
    const CollisionSphere& sphere,
    const CollisionPlane& plane,
    CollisionData* data
)
{


    // sauvegarde de la position de la sphère
    Vector3D position = sphere.getAxis(3);

    // Trouve la distance entre le plan et la sphère
    float centreDistance = plane.direction.scalarProduct(position) - plane.offset;

    // Est on dans le rayon de la sphère 
    if (centreDistance * centreDistance > sphere.radius * sphere.radius)
    {
        return 0;
    }

    // de quel côté du plan est on ?
    Vector3D normal = plane.direction;
    float penetration = -centreDistance;
    if (centreDistance < 0)
    {
        normal = normal * -1;
        penetration = -penetration;
    }
    penetration += sphere.radius;

    // On créer le contact et la collisionData
    //TODO : change collisionData
    Contact* contact = new Contact();
    contact->contactNormal = normal;
    contact->penetration = penetration;
    contact->contactPoint = position - plane.direction.multiplyByScalar(centreDistance);
    contact->setBodyData(sphere.body, NULL,
        data->friction, data->restitution);
    data->contacts = contact;
    data->addContacts(1);
    return 1;
}




unsigned CollisionDetector::sphereAndHalfSpace(
    const CollisionSphere& sphere,
    const CollisionPlane& plane,
    CollisionData* data
)
{


    // sauvegarde de la position de la sphère
    Vector3D position = sphere.getAxis(3);

    //On trouve la distance entre le plan et la sphère
    float ballDistance =
        plane.direction.scalarProduct(position) -
        sphere.radius - plane.offset;

    if (ballDistance >= 0) return 0;

    // On créer le contact et la collisionData
    Contact* contact = new Contact();
    contact->contactNormal = plane.direction;
    contact->penetration = -ballDistance;
    contact->contactPoint =
        position - plane.direction.multiplyByScalar(ballDistance + sphere.radius);
    contact->setBodyData(sphere.body, NULL,
        data->friction, data->restitution);
    data->contacts = contact;
    data->addContacts(1);
    return 1;
}

unsigned CollisionDetector::sphereAndSphere(
    const CollisionSphere& one,
    const CollisionSphere& two,
    CollisionData* data
)
{
    // Sauvegarde des positions des sphères
    Vector3D positionOne = one.getAxis(3);
    Vector3D positionTwo = two.getAxis(3);

    // Calcul du vecteur entre les deux sphères
    Vector3D midline = positionOne - positionTwo;
    float size = midline.getNorm();

    // On regarde si le vecteur midline est assez grand
    if (size <= 0.0f || size >= one.radius + two.radius)
    {
        return 0;
    }

    // On créer la normal manuellement
    Vector3D normal = midline * (((float)1.0f) / size);

    // On créer le contact et la collisionData
    Contact* contact = new Contact();
    contact->contactNormal = normal;
    contact->contactPoint = positionOne + midline * (float)0.5f;
    contact->penetration = (one.radius + two.radius - size);
    contact->setBodyData(one.body, two.body,
        data->friction, data->restitution);
    data->contacts = contact;
    data->addContacts(1);
    return 1;
}




/*
 * Cette fonction permet de vérifier si deux boites se superposent sur l'axe donnée axis,
 * toCentre est un vecteur entre les deux centres des boites
 */
static inline float penetrationOnAxis(
    const CollisionBox& one,
    const CollisionBox& two,
    const Vector3D& axis,
    const Vector3D& toCentre
)
{
    float oneProject = transformToAxis(one, axis);
    float twoProject = transformToAxis(two, axis);

    // On projète sur l'axe
    float distance = abs(toCentre.scalarProduct(axis));

    // retourne à quel point les objets se superposent
    return oneProject + twoProject - distance;
}


static inline bool tryAxis(
    const CollisionBox& one,
    const CollisionBox& two,
    Vector3D axis,
    const Vector3D& toCentre,
    unsigned index,

    float& smallestPenetration,
    unsigned& smallestCase
)
{
    // On doit bien avoir un axe normaliser
    if (axis.getSquareNorm() < 0.0001) return true;
    axis.normalize();

    float penetration = penetrationOnAxis(one, two, axis, toCentre);

    if (penetration < 0) return false;
    if (penetration < smallestPenetration) {
        smallestPenetration = penetration;
        smallestCase = index;
    }
    return true;
}

void fillPointFaceBoxBox(
    const CollisionBox& one,
    const CollisionBox& two,
    const Vector3D& toCentre,
    CollisionData* data,
    unsigned best,
    float pen
)
{

    //cette méthode est appelé quand on sait qu'un vertex de la boite est en contact avec la deuxième boite
    Contact* contact = new Contact();

   
    //on sait sur quel axe la collision a lieu mais on doit savoir sur quel face de la boite
    Vector3D normal = one.getAxis(best);
    if (one.getAxis(best) * toCentre > 0)
    {
        normal = normal * -1.0f;
    }

    //travail pour trouver le vertex avec lequel on collide
    Vector3D vertex = two.halfSize;
    if ((two.getAxis(0).scalarProduct(normal)) < 0) { vertex.setX(vertex.getX() * -1); }
    if ((two.getAxis(1).scalarProduct(normal)) < 0) { vertex.setY(vertex.getY() * -1); }
    if ((two.getAxis(2).scalarProduct(normal)) < 0) { vertex.setZ(vertex.getZ() * -1); }
    // On créer le contact et la collisionData
    contact->contactNormal = normal;
    contact->penetration = pen;
    contact->contactPoint = two.getTransform() * vertex;
    contact->setBodyData(one.body, two.body,
        data->friction, data->restitution);
    data->contacts = contact;

}

static inline Vector3D contactPoint(
    const Vector3D& pOne,
    const Vector3D& dOne,
    float oneSize,
    const Vector3D& pTwo,
    const Vector3D& dTwo,
    float twoSize,
    //si true and que contact en dehors des coins alors on utilise qu'un point et non deux
    bool useOne)
{
    Vector3D toSt, cOne, cTwo;
    float dpStaOne, dpStaTwo, dpOneTwo, smOne, smTwo;
    float denom, mua, mub;

    smOne = dOne.getSquareNorm();
    smTwo = dTwo.getSquareNorm();
    dpOneTwo = dTwo.scalarProduct(dOne);

    toSt = pOne - pTwo;
    dpStaOne = dOne * toSt;
    dpStaTwo = dTwo * toSt;

    denom = smOne * smTwo - dpOneTwo * dpOneTwo;

    //un denominateur à zero indique des lignes paralelle
    if (abs(denom) < 0.0001f) {
        return useOne ? pOne : pTwo;
    }

    mua = (dpOneTwo * dpStaTwo - smTwo * dpStaOne) / denom;
    mub = (smOne * dpStaTwo - dpOneTwo * dpStaOne) / denom;

    //si tous les coins ont leur point en dehors de la figure alors on un a edge-face contact
    if (mua > oneSize ||
        mua < -oneSize ||
        mub > twoSize ||
        mub < -twoSize)
    {
        return useOne ? pOne : pTwo;
    }
    else
    {
        cOne = pOne + dOne * mua;
        cTwo = pTwo + dTwo * mub;

        return cOne * 0.5 + cTwo * 0.5;
    }
}

// définition bien utile dans toute l'implémentation de boxAndBox

#define CHECK_OVERLAP(axis, index) \
    if (!tryAxis(one, two, (axis), toCentre, (index), pen, best)) return 0;

unsigned CollisionDetector::boxAndBox(
    const CollisionBox& one,
    const CollisionBox& two,
    CollisionData* data
)
{
    // trouve le vecteur entre les deux centres des boites
    Vector3D toCentre = two.getAxis(3) - one.getAxis(3);

    //On commence par dire qu'il n'y pas de contact
    float pen = 15; //REAL_MAX
    unsigned best = 0xffffff;

    // Now we check each axes, returning if it gives us
    // a separating axis, and keeping track of the axis with
    // the smallest penetration otherwise.

    //on vient regarder sur chaque axe si il nous donne un axe séparatoire 
    CHECK_OVERLAP(one.getAxis(0), 0);
    CHECK_OVERLAP(one.getAxis(1), 1);
    CHECK_OVERLAP(one.getAxis(2), 2);

    CHECK_OVERLAP(two.getAxis(0), 3);
    CHECK_OVERLAP(two.getAxis(1), 4);
    CHECK_OVERLAP(two.getAxis(2), 5);

    // Store the best axis-major, in case we run into almost
    // parallel edge collisions later
    unsigned bestSingleAxis = best;

    CHECK_OVERLAP(one.getAxis(0) % two.getAxis(0), 6);
    CHECK_OVERLAP(one.getAxis(0) % two.getAxis(1), 7);
    CHECK_OVERLAP(one.getAxis(0) % two.getAxis(2), 8);
    CHECK_OVERLAP(one.getAxis(1) % two.getAxis(0), 9);
    CHECK_OVERLAP(one.getAxis(1) % two.getAxis(1), 10);
    CHECK_OVERLAP(one.getAxis(1) % two.getAxis(2), 11);
    CHECK_OVERLAP(one.getAxis(2) % two.getAxis(0), 12);
    CHECK_OVERLAP(one.getAxis(2) % two.getAxis(1), 13);
    CHECK_OVERLAP(one.getAxis(2) % two.getAxis(2), 14);

    // on vveut être sur d'avoir un résultat
    assert(best != 0xffffff);

    // on sait désormais qu'il y a une collision et sur quel axe avec la plus petite pénétration. on choisit désormait comment on résout ce cas
    if (best < 3)
    {
        //Un vertex de one est sur une face de two
        fillPointFaceBoxBox(one, two, toCentre, data, best, pen);
        data->addContacts(1);
        return 1;
    }
    else if (best < 6)
    {
        //Un vertex de one est sur une face de two
        fillPointFaceBoxBox(two, one, toCentre * -1.0f, data, best - 3, pen);
        data->addContacts(1);
        return 1;
    }
    else
    {
        //on a un edge-edge contact, on cherche sur quel axe
        best -= 6;
        unsigned oneAxisIndex = best / 3;
        unsigned twoAxisIndex = best % 3;
        Vector3D oneAxis = one.getAxis(oneAxisIndex);
        Vector3D twoAxis = two.getAxis(twoAxisIndex);
        Vector3D axis = oneAxis % twoAxis;
        axis.normalize();

        // l'axe doit pointer de la boite 1 à la boite 2
        if (axis * toCentre > 0) axis = axis * -1.0f;

        Vector3D ptOnOneEdge = one.halfSize;
        Vector3D ptOnTwoEdge = two.halfSize;
        for (unsigned i = 0; i < 3; i++)
        {
            if (i == oneAxisIndex) ptOnOneEdge[i] = 0;
            else if (one.getAxis(i) * axis > 0) ptOnOneEdge[i] = -ptOnOneEdge[i];

            if (i == twoAxisIndex) ptOnTwoEdge[i] = 0;
            else if (two.getAxis(i) * axis < 0) ptOnTwoEdge[i] = -ptOnTwoEdge[i];
        }

        //on les met dans les coordonnées world
        ptOnOneEdge = one.transform * ptOnOneEdge;
        ptOnTwoEdge = two.transform * ptOnTwoEdge;

        // on a un point et une direction on doit trouver le point le plus proche des demis distances
        Vector3D vertex = contactPoint(
            ptOnOneEdge, oneAxis, one.halfSize[oneAxisIndex],
            ptOnTwoEdge, twoAxis, two.halfSize[twoAxisIndex],
            bestSingleAxis > 2
        );

        // We can fill the contact.
        Contact* contact = new Contact();

        contact->penetration = pen;
        contact->contactNormal = axis;
        contact->contactPoint = vertex;
        contact->setBodyData(one.body, two.body,
            data->friction, data->restitution);
        data->addContacts(1);
        data->contacts = contact;
        return 1;
    }
    return 0;
}
#undef CHECK_OVERLAP




unsigned CollisionDetector::boxAndPoint(
    const CollisionBox& box,
    const Vector3D& point,
    CollisionData* data
)
{
    //on récupère les coordonnées de la boite
    Vector3D relPt = box.transform.transformInverse(point);

    Vector3D normal;

    // on vérifie sur chaque axe la pénétration minimum
    float min_depth = box.halfSize.getX() - abs(relPt.getX());
    if (min_depth < 0) return 0;
    normal = box.getAxis(0) * ((relPt.getX() < 0) ? -1 : 1);

    float depth = box.halfSize.getY() - abs(relPt.getY());
    if (depth < 0) return 0;
    else if (depth < min_depth)
    {
        min_depth = depth;
        normal = box.getAxis(1) * ((relPt.getY() < 0) ? -1 : 1);
    }

    depth = box.halfSize.getZ() - abs(relPt.getZ());
    if (depth < 0) return 0;
    else if (depth < min_depth)
    {
        min_depth = depth;
        normal = box.getAxis(2) * ((relPt.getZ() < 0) ? -1 : 1);
    }

    // Compile the contact
    Contact* contact = new Contact();
    contact->contactNormal = normal;
    contact->contactPoint = point;
    contact->penetration = min_depth;

    // on ne sait pas a quel rigidbody le point appartient on met alors à null
    contact->setBodyData(box.body, NULL,
        data->friction, data->restitution);
    data->contacts = contact;
    data->addContacts(1);
    return 1;
}

unsigned CollisionDetector::boxAndSphere(
    const CollisionBox& box,
    const CollisionSphere& sphere,
    CollisionData* data
)
{
    //on récupère les coordonnées de la boite
    Vector3D centre = sphere.getAxis(3);
    Vector3D relCentre = box.transform.transformInverse(centre);

    // peut on éléminer certains contacts 
    if (abs(relCentre.getX()) - sphere.radius > box.halfSize.getX() ||
        abs(relCentre.getY()) - sphere.radius > box.halfSize.getY() ||
        abs(relCentre.getZ()) - sphere.radius > box.halfSize.getZ())
    {
        return 0;
    }

    Vector3D closestPt(0, 0, 0);
    float dist;

    dist = relCentre.getX();
    if (dist > box.halfSize.getX()) dist = box.halfSize.getX();
    if (dist < -box.halfSize.getX()) dist = -box.halfSize.getX();
    closestPt.setX(dist);

    dist = relCentre.getY();
    if (dist > box.halfSize.getY()) dist = box.halfSize.getY();
    if (dist < -box.halfSize.getY()) dist = -box.halfSize.getY();
    closestPt.setY(dist);

    dist = relCentre.getZ();
    if (dist > box.halfSize.getZ()) dist = box.halfSize.getZ();
    if (dist < -box.halfSize.getZ()) dist = -box.halfSize.getZ();
    closestPt.setZ(dist);

    // est on en contact
    dist = (closestPt - relCentre).getSquareNorm();
    if (dist > sphere.radius * sphere.radius) return 0;

    // Compile the contact
    Vector3D closestPtWorld = box.transform.transform(closestPt);

    Contact* contact = new Contact();
    contact->contactNormal = (closestPtWorld - centre);
    contact->contactNormal.normalize();
    contact->contactPoint = closestPtWorld;
    contact->penetration = sphere.radius - sqrt(dist);
    contact->setBodyData(box.body, sphere.body,
        data->friction, data->restitution);
    data->contacts = contact;

    data->addContacts(1);
    return 1;
}

unsigned CollisionDetector::boxAndHalfSpace(
    const CollisionBox& box,
    const CollisionPlane& plane,
    CollisionData* data
)
{
    // Check les intersections
    if (!IntersectionTests::boxAndHalfSpace(box, plane))
    {
        return 0;
    }


    //on a une intersection, on cherche les points d'intersection
    static float mults[8][3] = { {1,1,1},{-1,1,1},{1,-1,1},{-1,-1,1},
                               {1,1,-1},{-1,1,-1},{1,-1,-1},{-1,-1,-1} };

    Contact* contact = data->contacts;
    unsigned contactsUsed = 0;
    for (unsigned i = 0; i < 8; i++) {

        // calcul de la position des vertex
        Vector3D vertexPos(mults[i][0], mults[i][1], mults[i][2]);
        vertexPos = vertexPos.composantProduct(box.halfSize);
        vertexPos = box.transform.transform(vertexPos);

        // calcul de la distance depuis le plan
        float vertexDistance = vertexPos * plane.direction;

        // on compare à la distance plan
        if (vertexDistance <= plane.offset)
        {
            // on créer le contact

            // The contact point is halfway between the vertex and the
            // plane - we multiply the direction by half the separation
            // distance and add the vertex location.
            contact->contactPoint = plane.direction;
            contact->contactPoint = contact->contactPoint * (vertexDistance - plane.offset);
            contact->contactPoint = contact->contactPoint + vertexPos;
            contact->contactNormal = plane.direction;
            contact->penetration = plane.offset - vertexDistance;

            // Write the appropriate data
            contact->setBodyData(box.body, NULL,
                data->friction, data->restitution);

            // Move onto the next contact
            contact++;
            contactsUsed++;
            if (contactsUsed == (unsigned)data->contactsLeft) return contactsUsed;
        }
    }
    data->contacts = contact;
    data->addContacts(contactsUsed);
    return contactsUsed;
}


//TODO : generateContact(prim1,prim2,collisionData) est équivalent à toutes les fonctions suivantes
bool IntersectionTests::sphereAndHalfSpace(const CollisionSphere& sphere, const CollisionPlane& plane)
{
    // trouve la distance depuis l'origine
    CollisionPlane plan = plane;
    float ballDistance = (plan.direction.scalarProduct(sphere.getAxis(3))) - sphere.radius;

    // y a t il une intersection ?
    return ballDistance <= plane.offset;
}

bool IntersectionTests::sphereAndSphere(
    const CollisionSphere& one,
    const CollisionSphere& two)
{
    // calcul du vecteur décrit entre les objets
    Vector3D midline = one.getAxis(3) - two.getAxis(3);

    //est il assez grand ?
    return midline.getSquareNorm() <
        (one.radius + two.radius) * (one.radius + two.radius);
}


/**
 * Cette fonction regarde si deux boites sont superposé sur l'axe donné
 */
static inline bool overlapOnAxis(
    const CollisionBox& one,
    const CollisionBox& two,
    const Vector3D& axis,
    const Vector3D& toCentre
)
{

    float oneProject = transformToAxis(one, axis);
    float twoProject = transformToAxis(two, axis);

    // On projète sur notre axe
    float distance = abs(toCentre.scalarProduct(axis));

    // y a il superposition ?
    return (distance < oneProject + twoProject);
}

#define TEST_OVERLAP(axis) overlapOnAxis(one, two, (axis), toCentre)

bool IntersectionTests::boxAndBox(
    const CollisionBox& one,
    const CollisionBox& two
)
{
    //Vecteur entre les deux centres
    Vector3D toCentre = two.getAxis(3) - one.getAxis(3);

    return (
        // On regarde sur les axe de one d'abord
        TEST_OVERLAP(one.getAxis(0)) &&
        TEST_OVERLAP(one.getAxis(1)) &&
        TEST_OVERLAP(one.getAxis(2)) &&

        // Puis sur ceux de two
        TEST_OVERLAP(two.getAxis(0)) &&
        TEST_OVERLAP(two.getAxis(1)) &&
        TEST_OVERLAP(two.getAxis(2)) &&

        // Produit en croix
        TEST_OVERLAP(one.getAxis(0) % two.getAxis(0)) &&
        TEST_OVERLAP(one.getAxis(0) % two.getAxis(1)) &&
        TEST_OVERLAP(one.getAxis(0) % two.getAxis(2)) &&
        TEST_OVERLAP(one.getAxis(1) % two.getAxis(0)) &&
        TEST_OVERLAP(one.getAxis(1) % two.getAxis(1)) &&
        TEST_OVERLAP(one.getAxis(1) % two.getAxis(2)) &&
        TEST_OVERLAP(one.getAxis(2) % two.getAxis(0)) &&
        TEST_OVERLAP(one.getAxis(2) % two.getAxis(1)) &&
        TEST_OVERLAP(one.getAxis(2) % two.getAxis(2))
        );
}
#undef TEST_OVERLAP

bool IntersectionTests::boxAndHalfSpace(
    const CollisionBox& box,
    const CollisionPlane& plane
)
{
    // Work out the projected radius of the box onto the plane direction
    float projectedRadius = transformToAxis(box, plane.direction);

    // Work out how far the box is from the origin
    float boxDistance =
        plane.direction.scalarProduct(
            box.getAxis(3)) -
        projectedRadius;

    // Check for the intersection
    return boxDistance <= plane.offset;
}
