#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include <string.h>
#include <iostream>


class Level{
public:
	Level(sf::RenderWindow* hwnd, Input* in);
	~Level();

	sf::Text _mousePos;
	sf::Vector2i mousePos;
	std::string _mPos;
	sf::Font font;
	bool dragging;
	sf::Vector2i dragstart;
	sf::Vector2i dragend;
	sf::CircleShape mpos_circ;
	bool click;

	void handleInput();
	void update();
	void render();
	void dragDistance(sf::Vector2i, sf::Vector2i);

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;

	// Add your object here
};