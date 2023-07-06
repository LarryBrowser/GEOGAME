#include <iostream>
#include "Game.h"
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
int main(int argc, char* argv[])
{
	Game game;
	game.run();
	/*sf::RenderWindow window(sf::VideoMode(720, 480), "WORKKKKK", 1);
	while (window.isOpen())
	{
		window.clear();
		window.display();
	}*/
	return 0;
}