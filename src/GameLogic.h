#pragma once

#include <SFML/Graphics.hpp>

#include <Windows.h>

#include <vector>
#include <string>

enum button_states1 { BTN_IDL1 = 0, BTN_WARNING1, BTN_ACTIVE1, BTN_NONE };


class GameLogic
{
public:
	GameLogic(float x, float y, float size, bool rotation,
		sf::Font* font, std::string text, unsigned character_size,
		sf::Color text_idle_color, sf::Color text_active_color, sf::Color text_warning_color,
		sf::Color idle_color, sf::Color line_color);
	virtual ~GameLogic();

	GameLogic(float x, float y, float width, float height,
		sf::Font* font, std::string text, unsigned character_size,
		sf::Color text_idle_color, sf::Color idle_color, sf::Color line_color);

	const bool is_pressed() const;

	const bool is_pressed_bounds(const sf::Vector2f mouse_pos) const;

	void update(const sf::Vector2f mouse_pos);
	void render(sf::RenderTarget* target);
	void setText(std::string text);
	
	void refresh_buttons();
	void refresh_pressed();
	void set_pressed(bool);

	bool get_pressed();
	std::string get_text();

private:

	short unsigned button_states1;
	short unsigned button_states2;


	static bool pressed;
	static bool pressed3;

	bool pressed1 = false;

	sf::RectangleShape shape;
	sf::ConvexShape convex;
	sf::Font* font;
	sf::Text text;

	sf::Color text_idle_color;
	sf::Color text_active_color;
	sf::Color text_warning_color;

	sf::Color line_idle_color;
	sf::Color line_active_color;

	sf::Color idle_color;
	sf::Color line_color;

	void init_value();
};

