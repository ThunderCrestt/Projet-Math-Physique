#ifndef ParticuleContactResolver_h
#define ParticuleContactResolver_h

#include "Particule.h"
#include "ParticuleContact.h"
#include <vector>



class ParticuleContactResolver
{

private:
	unsigned iterations;
	unsigned iterationsUsed;

public:
	ParticuleContactResolver(unsigned iterations);
	void setIterations(unsigned iterations);
	void resolveContacts(std::vector<ParticuleContact*> contactArray, unsigned numContacts, int duration);


};

#endif // !ParticuleContactResolver.h
