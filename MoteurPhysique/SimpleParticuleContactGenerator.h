#include "ParticuleContactGenerator.h"
#include <vector>
#include <algorithm>

class SimpleParticuleContactGenerator : public ParticuleContactGenerator {
public:
	SimpleParticuleContactGenerator(float radius, std::vector<Particule*> particules);
	SimpleParticuleContactGenerator() = default;

	void setParticules(std::vector<Particule*> particules);

	//Radius of the particles
	float m_radius;

	std::vector<Particule*> particules;

	unsigned addContact(std::vector<ParticuleContact*>* contacts) const;

};