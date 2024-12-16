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
	if (CLOCK_EXERCISE)
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
	if (AIRPLANE_EXERCISE)
	{
		switch (evt.keysym.sym)
		{
		case SDLK_w:
			airplane->rotateHelix();
			break;
		}
	}

	// Teclas de la animacion:
	if (ANIMATION_EXERCISE)
	{
		switch (evt.keysym.sym)
		{
		case SDLK_a:
			if (!attachedLeftSword)
			{
				sinbadEnt->attachObjectToBone("Handle.L", swordLeftEnt);
				attachedLeftSword = true;
			}
			else
			{
				sinbadEnt->detachObjectFromBone(swordLeftEnt);
				attachedLeftSword = false;
			}
			break;
		case SDLK_d:
			if (!attachedRightSword)
			{
				sinbadEnt->attachObjectToBone("Handle.R", swordRightEnt);
				attachedRightSword = true;
			}
			else
			{
				sinbadEnt->detachObjectFromBone(swordRightEnt);
				attachedRightSword = false;
			}
			break;
		case SDLK_w:
			if (isDancing)
			{
				animationStateDance->setEnabled(false);
				animationStateDance->setLoop(false);
			}
			else
			{
				animationStateDance->setEnabled(true);
				animationStateDance->setLoop(true);
			}
			isDancing = !isDancing;

			animationStateRunBase->setEnabled(false);
			animationStateRunBase->setLoop(false);

			animationStateRunTop->setEnabled(false);
			animationStateRunTop->setLoop(false);

			animationState->setEnabled(false);
			animationState->setLoop(false);

			break;

		case SDLK_s:
			if (isRunning)
			{
				animationStateRunBase->setEnabled(false);
				animationStateRunBase->setLoop(false);

				animationStateRunTop->setEnabled(false);
				animationStateRunTop->setLoop(false);
			}
			else
			{
				animationStateRunBase->setEnabled(true);
				animationStateRunBase->setLoop(true);

				animationStateRunTop->setEnabled(true);
				animationStateRunTop->setLoop(true);
			}
			isRunning = !isRunning;

			animationStateDance->setEnabled(false);
			animationStateDance->setLoop(false);

			animationState->setEnabled(false);
			animationState->setLoop(false);
			break;
		case SDLK_q:
			if (isWalking)
			{
				animationState->setEnabled(false);
				animationState->setLoop(false);

				animationStateRunBase->setEnabled(false);
				animationStateRunBase->setLoop(false);

				animationStateRunTop->setEnabled(false);
				animationStateRunTop->setLoop(false);
			}
			else
			{
				animationState->setEnabled(true);
				animationState->setLoop(true);

				animationStateRunBase->setEnabled(true);
				animationStateRunBase->setLoop(true);

				animationStateRunTop->setEnabled(true);
				animationStateRunTop->setLoop(true);
			}
			isWalking = !isWalking;

			animationStateDance->setEnabled(false);
			animationStateDance->setLoop(false);
			break;
		default:
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

	//-------------------------------CLOCK------------------------------------
	// Creating the clock.

	if (CLOCK_EXERCISE)
	{
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
		secondsHandNode->roll(Degree(-180));
	}

#pragma endregion	

#pragma region airplane:

	//----------------------------AIRPLANE-------------------------------------
	// Creating the airplane.

	if (AIRPLANE_EXERCISE)
	{
		airplaneNode = mSM->getRootSceneNode()->createChildSceneNode();
		airplane = new Airplane({ 0,0,0 }, airplaneNode, mSM);
	}

#pragma endregion

#pragma region materiales, luces y sombras:

	//----------------------------MATERIALS------------------------------------
	// Creating the material scene.

	if (MATERIALS_EXERCISE)
	{
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
	}

#pragma endregion

#pragma region animacion:

	//-------------------------ANIMATION-------------------------------------
	// Creating animations:

	if (ANIMATION_EXERCISE)
	{
		sinbadEnt = mSM->createEntity("Sinbad.mesh");
		sinbadNode = mSM->getRootSceneNode()->createChildSceneNode();
		sinbadNode->attachObject(sinbadEnt);
		sinbadNode->scale(30, 30, 30);
		sinbadNode->setPosition(0, 25, 0); // On the floor!
		sinbadNode->setInitialState();

		// Creating two swords
		swordLeftEnt = mSM->createEntity("Sword.mesh");
		swordRightEnt = mSM->createEntity("Sword.mesh");

		// Obtain the names of all the animations in Sinbad.mesh
	//    AnimationStateSet * aux = sinbadEnt->getAllAnimationStates();
	//    auto it = aux->getAnimationStateIterator().begin();
	//    while (it != aux->getAnimationStateIterator().end()){
	//        auto s = it->first;
	//        ++it;
	//        cout << "Animation name (Sinbad.mesh): " << s << endl;
	//    }

		// Obtain the names of all the bones in Sinbad.mesh
	//    SkeletonInstance * skeleton = sinbadEnt->getSkeleton();
	//    int numBones = skeleton->getNumBones();
	//    for (int i=0; i<numBones; i++){
	//        cout << "Bone name (Sinbad.mesh): " << skeleton->getBone(i)->getName() << endl;
	//    }


		//------------------------------------------------------------------------
		// Animation of Sinbad
		animationStateDance = sinbadEnt->getAnimationState("Dance");
		animationStateRunBase = sinbadEnt->getAnimationState("RunBase");
		animationStateRunTop = sinbadEnt->getAnimationState("RunTop");

		// Set keyframes here...
		int movementLength = 500;
		Real duration = 12.0;

		Vector3 keyframePos(0, 0, 0);
		Quaternion keyFrameRot(Degree(0), Vector3(0, 1, 0));
		Vector3 keyFrameScale(1, 1, 1); // Sinbad ya esta escalado a (30, 30, 30), suficiente...


		Animation* animation = mSM->createAnimation("sinbadWalking", duration);
		animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
		NodeAnimationTrack* track = animation->createNodeTrack(0);
		track->setAssociatedNode(sinbadNode);
		TransformKeyFrame* kf;


		// Keyframe 0: init state.
		kf = track->createNodeKeyFrame(0);
		kf->setTranslate(keyframePos);
		kf->setRotation(keyFrameRot);
		kf->setScale(keyFrameScale);


		// Keyframe 0.5: rotacion hacia la derecha.
		kf = track->createNodeKeyFrame(0.5);
		keyFrameRot = Quaternion(Degree(90), Vector3(0, 1, 0)); // Rotamos 90º en Y hacia X.
		kf->setTranslate(keyframePos);
		kf->setRotation(keyFrameRot);
		kf->setScale(keyFrameScale);


		// Keyframe 1: ir a la derecha.
		kf = track->createNodeKeyFrame(3);
		keyframePos += Ogre::Vector3::UNIT_X * movementLength; // Movemos movementLength hacia la X.
		kf->setTranslate(keyframePos);
		kf->setRotation(keyFrameRot);
		kf->setScale(keyFrameScale);


		// Keyframe 1.5: rotar a la izquierda.
		kf = track->createNodeKeyFrame(3.5);
		keyFrameRot = Quaternion(Degree(-90), Vector3(0, 1, 0)); // Rotamos 180º en Y hacia -X.
		kf->setTranslate(keyframePos);
		kf->setRotation(keyFrameRot);
		kf->setScale(keyFrameScale);

		
		// Keyframe 2: volver al inicio.
		kf = track->createNodeKeyFrame(6);
		keyframePos += Ogre::Vector3::NEGATIVE_UNIT_X * movementLength; // Movemos movementLength hacia la -X.
		kf->setTranslate(keyframePos);
		kf->setRotation(keyFrameRot);
		kf->setScale(keyFrameScale);


		// Keyframe 3: mas a la izquierda.
		kf = track->createNodeKeyFrame(8.5);
		keyframePos += Ogre::Vector3::NEGATIVE_UNIT_X * movementLength; // Movemos movementLength hacia la -X.
		kf->setTranslate(keyframePos);
		kf->setRotation(keyFrameRot);
		kf->setScale(keyFrameScale);


		// Keyframe 3.5: rotar a la izquierda.
		kf = track->createNodeKeyFrame(9);
		keyFrameRot = Quaternion(Degree(90), Vector3(0, 1, 0)); // Rotamos 180º en Y hacia X.
		kf->setTranslate(keyframePos);
		kf->setRotation(keyFrameRot);
		kf->setScale(keyFrameScale);


		// Keyframe 4: volver al inicio.
		kf = track->createNodeKeyFrame(11.5);
		keyframePos += Ogre::Vector3::UNIT_X * movementLength;
		kf->setTranslate(keyframePos);
		kf->setRotation(keyFrameRot);
		kf->setScale(keyFrameScale);
		
		
		// Keyframe 4.5: Ponerse de frente
		kf = track->createNodeKeyFrame(12);
		keyFrameRot = Quaternion(Degree(0), Vector3(0, 1, 0)); // Rotamos 90º en Y hacia X.
		kf->setTranslate(keyframePos);
		kf->setRotation(keyFrameRot);
		kf->setScale(keyFrameScale);


		// Our defined animation
		animationState = mSM->createAnimationState("sinbadWalking");
		animationState->setLoop(true);
		animationState->setEnabled(true);
	}

#pragma endregion

}

void IG2App::frameRendered(const Ogre::FrameEvent& evt)
{
	// Example of NodeAnimationTrack
	//------------------------------------------------------------------------
	// TODO...


	// Example of Sinbad's animation (running and dancing)
	//------------------------------------------------------------------------
	if (isDancing)
	{
		animationStateDance->addTime(evt.timeSinceLastFrame);
	}
	if (isRunning)
	{
		animationStateRunBase->addTime(evt.timeSinceLastFrame);
		animationStateRunTop->addTime(evt.timeSinceLastFrame);
	}
	if (isWalking)
	{
		animationState->addTime(evt.timeSinceLastFrame);
		animationStateRunBase->addTime(evt.timeSinceLastFrame);
		animationStateRunTop->addTime(evt.timeSinceLastFrame);
	}
}