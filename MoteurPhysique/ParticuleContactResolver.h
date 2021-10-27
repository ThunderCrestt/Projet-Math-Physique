#include "Particule.h""
#include "ParticuleContact.h"
class ParticuleContactResolver
{
private:
	unsigned iterations;
	unsigned iterationsUsed;

public:
	ParticuleContactResolver(unsigned iterations);
	void setIterations(unsigned iterations);
	void resolveContacts(ParticuleContact* contactArray, unsigned numContacts, int duration);


};
