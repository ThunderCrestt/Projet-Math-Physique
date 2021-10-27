#include "Vector3D.h"
#include "Particule.h"
#include"ParticuleContact.h"
#include "ParticuleContactGenerator.h"
#include <vector>
class PlaneSurface2DContactGenerator : public ParticuleContactGenerator
{

	//cette classe assez simple permet de définir des surfaces planes en 2D à l'aide de deux vecteurs, 
	//on a donc les composantes Y ou X qui sont égales pour les deux vecteurs
public:
	Vector3D leftVector;
	Vector3D rightVector;
	Vector3D liaison;
	Vector3D normal;
	float restitution;
	std::vector<Particule*> particules;
	PlaneSurface2DContactGenerator(Vector3D leftVector,Vector3D rightVector, std::vector<Particule*>particules,float restitution);
	unsigned addContact(std::vector<ParticuleContact*>* contacts,unsigned limit) const;

};

