#pragma once
/**
 * A helper structure that contains information for the detector to use
 * in building its contact data.
 */

#include "Contact.h"
 //TODO : à mettre dans un autre fichier 
struct CollisionData
{

    /** Holds the contact array to write into. */
    Contact* contacts;

    /** Holds the maximum number of contacts the array can take. */
    int contactsLeft;

    /** Holds the number of contacts found so far. */
    unsigned contactCount;

    /** Holds the friction value to write into any collisions. */
    float friction;

    /** Holds the restitution value to write into any collisions. */
    float restitution;

    /**
     * Checks if there are more contacts available in the contact
     * data.
     */
    bool hasMoreContacts()
    {
        return contactsLeft > 0;
    }

    /**
     * Resets the data so that it has no used contacts recorded.
     */
    void reset(unsigned maxContacts)
    {
        contactsLeft = maxContacts;
        contactCount = 0;
        contacts = 0; //TODO: was contactArray that was deleted
    }

    /**
     * Notifies the data that the given number of contacts have
     * been added.
     */
    void addContacts(unsigned count)
    {
        // Reduce the number of contacts remaining, add number used
        contactsLeft -= count;
        contactCount += count;

        // Move the array forward
        contacts += count;
    }
};