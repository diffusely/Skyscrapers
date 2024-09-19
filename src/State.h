#pragma once
#include <SFML/Graphics.hpp>
#include "stack"


class State
{
public:

	State(sf::RenderWindow*, std::stack<State*>* states);
	virtual ~State();

	const bool& get_quit() const;

	void end_state();

	//virtual 
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = NULL) = 0;
	virtual void input_number(char) = 0;
	virtual void update_mouse_positions();
	

protected:

	std::stack<State*>* states;

	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;

	std::map<std::string, sf::Texture> textures;

	//poss
	sf::Vector2i mouse_pos_screen;
	sf::Vector2i mouse_pos_window;
	sf::Vector2f mouse_pos_view;

	sf::Vector2u window_size;

private:

};
