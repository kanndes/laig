#include <iostream>
#include "XMLscene.h"
#include "scene.h"
#include "CGFapplication.h"

int main(int argc, char* argv[])
{
	CGFapplication app = CGFapplication(); 
	app.init(&argc, argv);
	app.setScene(new scene());
	app.setInterface(new CGFinterface());
	app.run();
	return 0;
}