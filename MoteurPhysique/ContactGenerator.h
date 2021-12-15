#pragma once

#include "Contact.h"
#include <vector>
class ContactGenerator
{
public:

    virtual unsigned addContact(std::vector<Contact*>* contact, unsigned limit) const = 0;
};