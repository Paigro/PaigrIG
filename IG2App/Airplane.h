#pragma once

#include "IG2Object.h"
#include "Helix.h"


class Airplane : public IG2Object
{
private:

	Entity* wingLEnt = nullptr; // Ala izquierda del avion.
	Entity* wingREnt = nullptr; // Ala derecha del avion.
	Entity* ninjaEnt = nullptr; // Ninja del avion.
	Entity* fuselageEnt = nullptr; // El fuselaje del avion.
	Entity* tailEnt = nullptr; // El timon de cola del avion.

	Ogre::SceneNode* helixLNode = nullptr; // Nodo de la helice izquierda.
	Ogre::SceneNode* helixRNode = nullptr; // Nodo de la helice derecha.

public:

	//------Constructoras y destructoras:

	// Cosntructora de Airplane.
	Airplane(Vector3 pos, Ogre::SceneNode* airplaneNode, Ogre::SceneManager* sceneMg);
	// Destructora de Airplane.
	~Airplane();


	//------Para rotar las helices:

	// Rota las helices en Z.
	void rotateHelix();
};