#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <OgreEntity.h>
#include <OgreSkeletonInstance.h>
#include <OgreBone.h>
#include <OgreKeyFrame.h>
#include <OgreBillboardSet.h>
#include <OgreParticleSystem.h>
#include <sstream>
#include <iostream>
#include <string>
//#include "DataSizes.h"
#include "Airplane.h"


class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener {

public:
	explicit IG2App() : IG2ApplicationContext("IG2App") { };
	virtual ~IG2App() { };

protected:
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual void shutdown();
	virtual void setup();
	virtual void setupScene();
	virtual void frameRendered(const Ogre::FrameEvent& evt);

private:

	//static const Vector3 CAMERA_INIT_POSITION;

	// Scene manager and tray system
	Ogre::SceneManager* mSM = nullptr;
	OgreBites::TrayManager* mTrayMgr = nullptr;

	// Camera
	Ogre::SceneNode* mCamNode = nullptr;
	OgreBites::CameraMan* mCamMgr = nullptr;


	//-----Practica para el examen:

	//----Reloj:

	Ogre::SceneNode* clockNode = nullptr; // Nodo que contiene todo el reloj.
	Ogre::SceneNode* numbersNode = nullptr; // Nodo que contiene los "numeros".
	Ogre::SceneNode* handsNode = nullptr; // Nodo que contiene las manecillas del reloj. Todas.

	Ogre::SceneNode* hoursNode = nullptr; // Nodo que contiene la manecilla de las horas.
	Ogre::SceneNode* minutesNode = nullptr; // Nodo que contiene la manecilla de los minutos.
	Ogre::SceneNode* secondsNode = nullptr; // Nodo que contiene la manecilla de los segundos. 

	//----Avion:

	Ogre::SceneNode* airplaneNode = nullptr; // Nodo que contiene el avion.
	Airplane* airplane = nullptr;

	//----Materiales, luces y sombras:

	Ogre::SceneNode* planeNode = nullptr; // Nodo que tiene el plano.
	Ogre::SceneNode* headNode = nullptr; // Nodo que tiene el ogreHead.
	Ogre::SceneNode* sphereNode = nullptr; // Nodo que tiene una esfera.
};

#endif