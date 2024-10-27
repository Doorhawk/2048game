#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"



class WindowManager {
public:
	WindowManager();
	void updateWindow();

private:
	
	void drawGame();



	sf::Color get_color(int);
	void changeSize(int);
	void createWindow(int, int);
	void controlButtons(sf::Event);
	void drawFrame();

	void restartGame();


	int tileSize;
	int height;
	int width;
	int gameDifficult;
	int gameSizeX;
		int gameSizeY;
	Game2048 game;
	sf::RenderWindow window;
	sf::Font font;
};