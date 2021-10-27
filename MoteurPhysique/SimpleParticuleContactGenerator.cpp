#include "SimpleParticuleContactGenerator.h"
#include <iostream>

SimpleParticuleContactGenerator::SimpleParticuleContactGenerator(float radius, std::vector<Particule*> particules) : m_radius(radius)
{
	this->particules = particules;
}

void SimpleParticuleContactGenerator::setParticules(std::vector<Particule*> particules)
{
	this->particules = particules;
}

unsigned SimpleParticuleContactGenerator::addContact(std::vector<ParticuleContact*>* contacts) const{
	int iteration = 0;
	for (int i = 0; i < particules.size(); i++) {
		for (int j = 0; j < particules.size(); j++) {
			if (i == j) continue;
			float distance = (particules[i]->getPosition() - particules[j]->getPosition()).getNorm();
			//si la particule est dans le rayon de l'autre particule on créer la normale on calcul l'interpénétration et on créer le contact
			if (distance < m_radius) {
				Vector3D normal = particules[1]->getPosition() - particules[0]
					->getPosition();
				float truc = m_radius - distance;
				ParticuleContact* c = new ParticuleContact(particules[i], particules[j], 1.5, normal, m_radius - distance);

				//si le contact existe ou non déjà
				bool contactAlreadyExist = false;
				for (int i = 0; i < contacts->size(); i++) {
					if (contacts->at(i) == c) {
						contactAlreadyExist = true; break;
					}
				}

				if (!contactAlreadyExist) {
					contacts->push_back(c);
					iteration++;
				}
			}
		}
	}
	return iteration;
}