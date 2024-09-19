#include "Button.h"

Button::Button(
	float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_color, sf::Color line_color, sf::Color line_active_color)
{
	this->button_states = BTN_IDL;
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(this->idle_color);
	this->shape.setOutlineThickness(2);
	this->shape.setOutlineColor(line_color);

	

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height + 3
	);


	//Color
	this->text_idle_color = text_idle_color;
	this->text_hover_color = text_hover_color;
	this->text_active_color = text_active_color;

	this->idle_color = idle_color;
	this->line_color = line_color;
	this->line_active_color = line_active_color;

	

}

Button::~Button()
{

}

const bool Button::is_pressed() const
{
	if (this->button_states == BTN_ACTIVE)
		return true;

	return false;
}

void Button::update(const sf::Vector2f mouse_pos)
{
	//update the booleand for hover and pressed

	//idle

	this->button_states = BTN_IDL;
	//Hover 

	if (this->shape.getGlobalBounds().contains(mouse_pos))
	{
		this->button_states = BTN_HOVER;

		//pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->button_states = BTN_ACTIVE;
			start = true;
		}
	}

	switch (this->button_states)
	{
	case BTN_IDL:
		this->shape.setFillColor(this->idle_color);
		this->text.setFillColor(this->text_idle_color);
		break;

	case BTN_HOVER:
		this->text.setFillColor(this->text_hover_color);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->line_active_color);
		this->text.setFillColor(this->text_active_color);
		break;

	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		break;
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}


