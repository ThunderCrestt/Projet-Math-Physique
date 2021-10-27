#include "ParticuleContactResolver.h"
#include "ParticuleContact.h"

ParticuleContactResolver::ParticuleContactResolver(unsigned iterations)
{
	this->iterations = iterations;
	this->iterationsUsed = 0;
}
void ParticuleContactResolver::setIterations(unsigned iterations)
{
	this->iterations = iterations;
}
void ParticuleContactResolver::resolveContacts(std::vector<ParticuleContact*> contactArray, unsigned numContacts, int duration)
{
	iterationsUsed = 0;
	while (iterationsUsed < iterations)
	{
		float max = 0;
		unsigned maxIndex = numContacts;
		for (unsigned i = 0; i < numContacts; i++)
		{
			int sepVel = contactArray[i]->calculerVs();
			if (sepVel < max)
			{
				max = sepVel;
				maxIndex = i;
			}
		}

		contactArray[maxIndex]->resolve(duration);
		iterationsUsed++;
	}
}