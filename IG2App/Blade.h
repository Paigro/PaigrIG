#pragma once
#include "IG2Object.h"


class Blade : public IG2Object
{
private:

public:

	//------Constructoras y destructoras:

	// Constructora de Blade.
	Blade(Vector3 pos,Ogre::SceneNode* bladeNode, Ogre::SceneManager* sceneMg);
	// Destructora ed blade.
	~Blade();
};