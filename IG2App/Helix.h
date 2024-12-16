#pragma once

#include "IG2Object.h"
#include "Blade.h"


class Helix : public IG2Object
{
private:

	std::vector<Blade*> vBlades; // Vector de palas de la helices.

	Entity* cylinderEnt = nullptr; // Cilindro en el centro de las palas.

public:

	//------Constructoras y destructoras:

	// Cosntructora de Helix.
	Helix(Vector3 pos, Ogre::SceneNode* helixNode, Ogre::SceneManager* sceneMg, int nBlades, int radius);
	// Destructora de Helix.
	~Helix();
};