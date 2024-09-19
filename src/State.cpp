#include "State.h"

State::State(sf::RenderWindow* window, std::stack<State*>* states)
{
	this->window_size.x = 1200; 
	this->window_size.y = 800;
	this->window = window;
	this->states = states;
	this->quit = false;
}

State::~State()
{
	
}

const bool& State::get_quit() const
{
	return this->quit;
}

void State::end_state()
{
	this->quit = true;
}

void State::update_mouse_positions()
{
	this->mouse_pos_screen = sf::Mouse::getPosition();
	this->mouse_pos_window = sf::Mouse::getPosition(*this->window);
	this->mouse_pos_view = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->window_size = window->getSize();
}

