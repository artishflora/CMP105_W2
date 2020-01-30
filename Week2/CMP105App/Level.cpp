#include "Level.h"
#include <string>
#include <iostream>

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	mousePos.x = input->getMouseX();
	mousePos.y = input->getMouseY();
	_mousePos.setString("mouse coordinates: " + std::to_string(mousePos.x) + ", " + std::to_string(mousePos.y));
	dragging = false;
	click = false;

	font.loadFromFile("font/arial.ttf");
	_mousePos.setCharacterSize(20);
	_mousePos.setFillColor(sf::Color::Magenta);
	_mousePos.setFont(font);
	_mousePos.setPosition(sf::Vector2f(0, 0));

	mpos_circ.setFillColor(sf::Color::Green);
	mpos_circ.setOutlineColor(sf::Color::Red);
	mpos_circ.setOutlineThickness(50.f);
	mpos_circ.setRadius(50);
}

Level::~Level()
{
	input = nullptr;
}

// handle user input
void Level::handleInput()
{
	if (input->isKeyDown(sf::Keyboard::W))
	{
		input->setKeyUp(sf::Keyboard::W);
		std::cout << "Hello ->W<-orld." << std::endl;
	}
	if ((input->isKeyDown(sf::Keyboard::J)) && (input->isKeyDown(sf::Keyboard::K)) && (input->isKeyDown(sf::Keyboard::L)))
	{
		input->setKeyUp(sf::Keyboard::J);
		input->setKeyUp(sf::Keyboard::K);
		input->setKeyUp(sf::Keyboard::L);
		std::cout << "Un-hello world." << std::endl;
	}

	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		window->close();
	}

	if (input->isMouseLDown())
	{
		if (!dragging)
		{
			dragstart.x = input->getMouseX();
			dragstart.y = input->getMouseY();
			dragging = true;
		}
	}
	else if (!input->isMouseLDown() && dragging)
	{
		dragend.x = input->getMouseX();
		dragend.y = input->getMouseY();
		dragging = false;
		dragDistance(dragstart, dragend);
	}

	if (input->isMouseRDown())
	{
		if (!click) click = true;
	}
	else if (!input->isMouseRDown() && click)
	{
		mpos_circ.setPosition((input->getMouseX()-mpos_circ.getRadius()), (input->getMouseY()-mpos_circ.getRadius()));
		click = false;
	}
}

void Level::dragDistance(sf::Vector2i start, sf::Vector2i finish)
{
	int dist_x = abs(start.x - finish.x);
	int dist_y = abs(start.y - finish.y);
	double dist = sqrt((dist_x * dist_x) + (dist_y * dist_y));
	std::cout << "Starting coordinates: " << start.x << ", " << start.y << std::endl;
	std::cout << "Ending coordinates: " << finish.x << ", " << finish.y << std::endl;
	std::cout << "Distance dragged: " << std::to_string(dist) << std::endl;
}

// Update game objects
void Level::update()
{
	mousePos.x = input->getMouseX();
	mousePos.y = input->getMouseY();
	_mousePos.setString("mouse coordinates: " + std::to_string(mousePos.x) + ", " + std::to_string(mousePos.y));
}

// Render level
void Level::render()
{
	beginDraw();

	window->draw(_mousePos);
	window->draw(mpos_circ);

	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}