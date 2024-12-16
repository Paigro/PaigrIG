#include "Blade.h"


Blade::Blade(Vector3 pos, Ogre::SceneNode* bladeNode, Ogre::SceneManager* sceneMg)
	: IG2Object(pos, bladeNode, sceneMg)
{
	Entity* bladeEnt = sceneMg->createEntity("cube.mesh");
	bladeNode->attachObject(bladeEnt);

	bladeNode->setScale(0.5, 5, 0.2);

	Entity* headEnt = sceneMg->createEntity("ogrehead.mesh");
	SceneNode* headNode = bladeNode->createChildSceneNode();
	headNode->attachObject(headEnt);
	headNode->setPosition(0, 40, 60);
	headNode->setScale(2, 0.5, 0.1);
}

Blade::~Blade()
{

}