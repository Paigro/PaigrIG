#include "IG2App.h"

using namespace Ogre;
using namespace std;


// Initial position for the camera
const Vector3 CAMERA_INIT_POSITION = { 0, 700, 1600 };


bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt) {

	// ESC key finished the rendering...
	if (evt.keysym.sym == SDLK_ESCAPE)
	{
		getRoot()->queueEndRendering();
	}

	// Teclas del reloj:
	if (clockNode != nullptr)
	{
		switch (evt.keysym.sym)
		{
		case SDLK_a:
			clockNode->roll(Degree(5));
			break;
		case SDLK_d:
			clockNode->roll(Degree(-5));
			break;
		case SDLK_w:
			hoursNode->roll(Degree(-1));
			break;
		case SDLK_s:
			hoursNode->roll(Degree(-1));
			break;
		}
	}

	// Teclas del avion:
	if (airplaneNode != nullptr)
	{
		switch (evt.keysym.sym)
		{
		case SDLK_w:
			airplane->rotateHelix();
			break;
		}
	}

	return true;
}

void IG2App::shutdown() {

	mShaderGenerator->removeSceneManager(mSM);
	mSM->removeRenderQueueListener(mOverlaySystem);

	mRoot->destroySceneManager(mSM);

	delete mTrayMgr;
	mTrayMgr = nullptr;
	delete mCamMgr;
	mCamMgr = nullptr;

	// do not forget to call the base
	IG2ApplicationContext::shutdown();
}

void IG2App::setup(void) {

	// do not forget to call the base first
	IG2ApplicationContext::setup();

	// Create the scene manager
	mSM = mRoot->createSceneManager();

	// Register our scene with the RTSS
	mShaderGenerator->addSceneManager(mSM);

	mSM->addRenderQueueListener(mOverlaySystem);
	mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);
	mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
	addInputListener(mTrayMgr);

	// Adds the listener for this object
	addInputListener(this);
	setupScene();
}

void IG2App::setupScene(void)
{

#pragma region camera, light and shadows:

	//---------------------------CAMERA---------------------------------------
	// Creating the camera:

	Camera * cam = mSM->createCamera("Cam");
	cam->setNearClipDistance(1);
	cam->setFarClipDistance(10000);
	cam->setAutoAspectRatio(true);

	mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
	mCamNode->attachObject(cam);

	mCamMgr = new OgreBites::CameraMan(mCamNode);
	addInputListener(mCamMgr);
	mCamMgr->setStyle(OgreBites::CS_ORBIT);
	mCamNode->setPosition(CAMERA_INIT_POSITION);
	mCamNode->lookAt(Ogre::Vector3(0, 200, 0), Ogre::Node::TS_WORLD);

	// And tell it to render into the main window
	Viewport* vp = getRenderWindow()->addViewport(cam);
	vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));


	//-----------------------------LIGHT--------------------------------------
	// Creating the light (Directional light):

	//mSM->setAmbientLight(Ogre::ColourValue(0.3,0.3,0.3));

	Ogre::Light* directionalLight = mSM->createLight("DirectionalLight");
	directionalLight->setType(Light::LT_DIRECTIONAL);
	directionalLight->setDiffuseColour(1.0f, 1.0f, 1.0f);

	// Node with the light attached
	Ogre::SceneNode* nodeDir = mSM->getRootSceneNode()->createChildSceneNode();
	nodeDir->setDirection(Ogre::Vector3(0, -1, -1));
	nodeDir->attachObject(directionalLight);

	//-----------------------------SHADOW-------------------------------------
	// Setting up the shadows

	//mSM->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

#pragma endregion

#pragma region clock:

	/*//-------------------------------CLOCK------------------------------------
	// Creating the clock.

	clockNode = mSM->getRootSceneNode()->createChildSceneNode("clockNode");
	SceneNode* centerNode = clockNode->createChildSceneNode("centerNode");
	Entity* centerEnt = mSM->createEntity("sphere.mesh");
	centerNode->attachObject(centerEnt);
	centerNode->setScale(0.4, 0.4, 0.4);
	numbersNode = clockNode->createChildSceneNode("numbersNode");

	float r = 500;

	for (int i = 0; i < 12; i++)
	{
		float angle = Math::TWO_PI * i / 12;

		float x = r * cos(angle);
		float y = r * sin(angle);
		float z = 0;

		Entity* ent = mSM->createEntity("sphere.mesh");
		SceneNode* sNode = numbersNode->createChildSceneNode("hour" + to_string(i));
		sNode->attachObject(ent);
		sNode->setPosition(x, y, z);

		if (i % 2 != 0)
		{
			sNode->setScale(sNode->getScale() / 2);
		}
	}

	handsNode = clockNode->createChildSceneNode("handsNode");

	hoursNode = handsNode->createChildSceneNode("hoursNode");
	minutesNode = handsNode->createChildSceneNode("minutesNode");
	secondsNode = handsNode->createChildSceneNode("secondsNode");

	Entity* hoursEnt = mSM->createEntity("cube.mesh");
	SceneNode* hoursHandNode = hoursNode->createChildSceneNode("hoursHandNode");
	hoursHandNode->attachObject(hoursEnt);
	hoursHandNode->setPosition(100, 0, 0);
	hoursHandNode->setScale(2, 0.35, 0.35);

	Entity* minutesEnt = mSM->createEntity("cube.mesh");
	SceneNode* minutesHandNode = minutesNode->createChildSceneNode("minutesHandNode");
	minutesHandNode->attachObject(minutesEnt);
	minutesHandNode->setPosition(0, 120, 0);
	minutesHandNode->setScale(3, 0.25, 0.25);
	minutesHandNode->roll(Degree(-90));

	Entity* secondsEnt = mSM->createEntity("cube.mesh");
	SceneNode* secondsHandNode = secondsNode->createChildSceneNode("secondsHandNode");
	secondsHandNode->attachObject(secondsEnt);
	secondsHandNode->setPosition(-150, 0, 0);
	secondsHandNode->setScale(4, 0.15, 0.15);
	secondsHandNode->roll(Degree(-180));*/

#pragma endregion	

#pragma region airplane:

	//----------------------------AIRPLANE-------------------------------------
	// Creating the airplane.

	//airplaneNode = mSM->getRootSceneNode()->createChildSceneNode();
	//airplane = new Airplane({ 0,0,0 }, airplaneNode, mSM);

#pragma endregion

#pragma region materiales, luces y sombras:

	MeshManager::getSingleton().createPlane("mPlane1080x800",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(Vector3::UNIT_Y, 0),
		1080, 800, 100, 80,
		true, 1, 1.0, 1.0, Vector3::UNIT_Z);
	Ogre::Entity* planeEnt = mSM->createEntity("mPlane1080x800");
	planeEnt->setMaterialName("waterAnimMaterial");
	planeNode = mSM->getRootSceneNode()->createChildSceneNode();
	planeNode->attachObject(planeEnt);

	headNode = mSM->getRootSceneNode()->createChildSceneNode();
	Entity* headEnt = mSM->createEntity("ogrehead.mesh");
	headNode->attachObject(headEnt);
	headNode->setPosition(-100, 50, 0);

	sphereNode = mSM->getRootSceneNode()->createChildSceneNode();
	Entity* sphereEnt = mSM->createEntity("uv_sphere.mesh");
	sphereEnt->setMaterialName("frostOrangeSphere");
	sphereNode->attachObject(sphereEnt);
	sphereNode->setPosition(100, 50, 0);
	sphereNode->setScale(0.5, 0.5, 0.5);


#pragma endregion

}

void IG2App::frameRendered(const Ogre::FrameEvent& evt)
{



}