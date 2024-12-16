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

const bool CLOCK_EXERCISE = false; // Si aparece el ejercicio del reloj o no.
const bool AIRPLANE_EXERCISE = false; // Si aparece el ejercicio del avion o no.
const bool MATERIALS_EXERCISE = false; // Si aparece el ejercicio de materiales, luces y sombras o no.
const bool ANIMATION_EXERCISE = false; // Si aparece el ejercicio de animaciones o no.
const bool PARTICLESYSTEM_EXERCISE = false; // Si aparece el ejercicio de sistemas de particulas o no.
const bool MULTITEXTURES_EXERCISE = false; // Si aparece el ejercicio de multitexturas o no.
const bool SHADERS_EXERCISE = true; // Si aparece el ejercicio de shaders o no.


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
	Ogre::SceneManager* mSM = nullptr; // Scene Manager.
	OgreBites::TrayManager* mTrayMgr = nullptr;

	// Camera
	Ogre::SceneNode* mCamNode = nullptr; // Nodo de la camara.
	OgreBites::CameraMan* mCamMgr = nullptr; // Camara.


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

	//----Animacion:

	// Animation state
	Ogre::AnimationState* animationState; // Caminado.

	// Animation states for Sinbad
	Ogre::AnimationState* animationStateDance; // Baile.
	Ogre::AnimationState* animationStateRunBase; // Carrera parte de abajo.
	Ogre::AnimationState* animationStateRunTop; // Carrera parte de arriba.

	// Flags to control the animations
	bool isDancing = false; // Si esta bailando o no.
	bool isRunning = false; // Si esta corriendo o no.
	bool isWalking = false; // Si esta caminando o no.
	bool attachedLeftSword = false; // Si tiene la espada izquierda o no.
	bool attachedRightSword = false; // Si tiene la espada derecha o no.

	// Sinbad and swords
	Ogre::SceneNode* sinbadNode = nullptr; // Nodo que contiene a Sinbad.
	Ogre::Entity* sinbadEnt = nullptr; // Entidad de Sinbad.
	Ogre::Entity* swordLeftEnt = nullptr; // Entidad de la espada izquierda.
	Ogre::Entity* swordRightEnt = nullptr; // Entidad de la espada derecha.

	//----Sistemas de particulas:

	ParticleSystem* pSys = nullptr; // Sistema de particulas de humo.

	Ogre::SceneNode* pSNode = nullptr; // Nodo que tiene al sistema de particulas de humo.


	Entity* sphereTailEnt = nullptr; // Esfera que va a rotar y tiene un trail. 

	ParticleSystem* tailPsys = nullptr; // Sistemas de particulas que hara de trail de la esfera.

	Ogre::SceneNode* sphereTailNode = nullptr; // Nodo que tiene a la esfera
	Ogre::SceneNode* ghostNode = nullptr; // Nodo fantasma que tiene a la esfera y que rotaremos.

	//------Shaders:

	Entity* orangeSphereEnt = nullptr; // Entidad esfera uv a la que le aplicaremos shaders.
	Ogre::SceneNode* orangeSphereNode = nullptr; // Nodo que tiene a la esfera uv a la que le aplicaremos shaders.
};

#endif