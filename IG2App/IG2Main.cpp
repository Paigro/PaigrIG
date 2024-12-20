#include "IG2App.h"

int main(int argc, char* argv[])
{
	IG2App app;

	try {
		srand((unsigned)time(NULL));
		app.initApp();
		app.getRoot()->startRendering();
	}
	catch (Ogre::Exception& e) {
		Ogre::LogManager::getSingleton().logMessage("\n\n------------------\nAn exception has occured: " + e.getFullDescription() + "\n------------------\n" + "\n\n");
	}
	app.closeApp();
	return 0;
}