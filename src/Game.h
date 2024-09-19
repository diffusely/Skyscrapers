#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "State.h"
#include "MainMenuState.h"
#include "Matrix.h"

#include <stack>
#include <iostream>
#include <fstream>

class Game
{
public:
	Game();
	~Game();

	//Run game
	void run();

private:	

	//|**************|
	//|Game functions|  
	//|**************|
	
	void start_game();


	//Test pritn

	void print();

	//Update and Render
	void update();
	void render();
	void update_dt();
	
	//Event
	void game_event();
	void update_mouse_pos();

private:
	//window
	sf::RenderWindow* window;

	//Read parameters
	std::fstream fin;

	//Matrix
	std::vector<Matrix*> game_matrix;

	//Dt
	sf::Clock dtClock;
	float dt;

	//State
	std::stack<State*> states;

	//Mouse pos
	sf::Vector2i mouse_pos;

	//Initializaiton
	void init_window();
	void init_icon();
	void init_states();
	void init_read();
};

