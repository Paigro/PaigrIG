#include "Helix.h"

Helix::Helix(Vector3 pos, Ogre::SceneNode* helixNode, Ogre::SceneManager* sceneMg, int nBlades, int radius)
	: IG2Object(pos, helixNode, sceneMg)
{
	// Las palas de la helice.
	for (int i = 0; i < nBlades; i++)
	{
		float angle = Math::TWO_PI * i / nBlades;

		float x = radius * cos(angle);
		float y = radius * sin(angle);
		float z = pos.z;

		Blade* newBlade = new Blade(Vector3(x, y, z), helixNode->createChildSceneNode(), sceneMg);
		newBlade->roll(Degree(-90));
		newBlade->roll(Degree((360 / nBlades) * i));
		vBlades.push_back(newBlade);
	}

	// El cilindro central.
	cylinderEnt = sceneMg->createEntity("Barrel.mesh");
	SceneNode* cylinderNode = helixNode->createChildSceneNode();
	cylinderNode->attachObject(cylinderEnt);
	cylinderNode->setScale(10, 8, 10);
	cylinderNode->pitch(Degree(90));
}

Helix::~Helix()
{

}