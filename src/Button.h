#pragma once
#include <string>
#include <SFML/Graphics.hpp>



enum button_states { BTN_IDL = 0, BTN_HOVER, BTN_ACTIVE };

class Button
{
public:

	Button(float x, float y, float width, float height,
		sf::Font* font, std::string text, unsigned character_size,
		sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
		sf::Color idle_color, sf::Color line_color, sf::Color line_active_color);

	

	virtual ~Button();

	const bool is_pressed() const;

	void update(const sf::Vector2f mouse_pos);
	void render(sf::RenderTarget* target);

private:

	short unsigned button_states;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color text_idle_color;
	sf::Color text_hover_color;
	sf::Color text_active_color;

	sf::Color idle_color;


	sf::Color line_active_color;
	sf::Color line_color;


	bool start = false;
};

