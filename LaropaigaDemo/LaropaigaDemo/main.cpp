#include <Bengine2/IMainGame.h>
#include "App.h"
#include <iostream>

//TODO:
//		add chests to the screen
//		destroy chest upon interaction
//		add one of the objects inside
//		create inventory
//		add item to inventory upon interaction with chest

int main(int argc, char** argv) {
	App app;
	std::cout << "Before Run";
	app.run();

	return 0;
}