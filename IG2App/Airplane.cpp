#include "Airplane.h"


Airplane::Airplane(Vector3 pos, Ogre::SceneNode* airplaneNode, Ogre::SceneManager* sceneMg)
	: IG2Object(pos, airplaneNode, sceneMg)
{
	fuselageEnt = sceneMg->createEntity("sphere.mesh");
	SceneNode* fuselageNode = airplaneNode->createChildSceneNode();
	fuselageNode->attachObject(fuselageEnt);
	fuselageNode->setScale(1, 1, 5);

	tailEnt = sceneMg->createEntity("cube.mesh");
	SceneNode* tailNode = airplaneNode->createChildSceneNode();
	tailNode->attachObject(tailEnt);
	tailNode->setScale(0.3, 3, 1);
	tailNode->setPosition(0, 60, -200);
	tailNode->pitch(Degree(-45));

	wingLEnt = sceneMg->createEntity("cube.mesh");
	SceneNode* wingLNode = airplaneNode->createChildSceneNode();
	wingLNode->attachObject(wingLEnt);
	wingLNode->setScale(4, 0.1, 1.5);
	wingLNode->setPosition(200, 0, 0);
	wingLNode->yaw(Degree(20));

	wingREnt = sceneMg->createEntity("cube.mesh");
	SceneNode* wingRNode = airplaneNode->createChildSceneNode();
	wingRNode->attachObject(wingREnt);
	wingRNode->setScale(4, 0.1, 1.5);
	wingRNode->setPosition(-200, 0, 0);
	wingRNode->yaw(Degree(-20));

	ninjaEnt = sceneMg->createEntity("ninja.mesh");
	SceneNode* ninjaNode = airplaneNode->createChildSceneNode();
	ninjaNode->attachObject(ninjaEnt);
	ninjaNode->setPosition(0, -40, 200);
	ninjaNode->yaw(Degree(180));

	helixLNode= airplaneNode->createChildSceneNode();
	Helix* helixLEnt = new Helix(pos, helixLNode, sceneMg, 6, 60);
	helixLNode->setScale(0.2, 0.2, 0.2);
	helixLNode->setPosition(250, 0, 75);
	helixLNode->yaw(Degree(20));
	
	helixRNode= airplaneNode->createChildSceneNode();
	Helix* helixREnt = new Helix(pos, helixRNode, sceneMg, 6, 60);
	helixRNode->setScale(0.2, 0.2, 0.2);
	helixRNode->setPosition(-250, 0, 75);
	helixRNode->yaw(Degree(-20));
}

Airplane::~Airplane()
{

}

void Airplane::rotateHelix()
{
	helixLNode->roll(Degree(5));
	helixRNode->roll(Degree(5));
}