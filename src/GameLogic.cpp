#include "GameLogic.h"

GameLogic::GameLogic(float x, float y, float size, bool rotation,
    sf::Font* font, std::string text, unsigned character_size,
    sf::Color text_idle_color, sf::Color text_active_color, sf::Color text_warning_color,
    sf::Color idle_color, sf::Color line_color)
{
    this->button_states2 = BTN_NONE;
    this->button_states1 = BTN_IDL1;
    init_value();
    this->convex.setFillColor(idle_color);
    this->convex.setOutlineColor(line_color);

    if (!rotation)
    {
        convex.setPoint(0, sf::Vector2f(x, y));
        convex.setPoint(1, sf::Vector2f(x, y + size));
        convex.setPoint(2, sf::Vector2f(x + size, y + size));
        convex.setPoint(3, sf::Vector2f(x + 1.5 * size, y + 0.5 * size));
        convex.setPoint(4, sf::Vector2f(x + size, y));
    }
    else
    {
        convex.setPoint(0, sf::Vector2f(x, y));
        convex.setPoint(1, sf::Vector2f(x + size, y));
        convex.setPoint(2, sf::Vector2f(x + size, y + size));
        convex.setPoint(3, sf::Vector2f(x + 0.5 * size, y + 1.5 * size));
        convex.setPoint(4, sf::Vector2f(x, y + size));
    }
   
    


    this->shape.setPosition(x, y);
    this->shape.setSize(sf::Vector2f(1.5 * size, size));
    this->shape.setFillColor(sf::Color::Transparent);


    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(text_idle_color);
    this->text.setCharacterSize(character_size);
    this->text.setPosition(
        x + (size / 2.f) - this->text.getGlobalBounds().width / 2.f,
        y + (size / 2.f) - this->text.getGlobalBounds().height + 3
    );


    this->text_idle_color = text_idle_color;
    this->text_active_color = text_active_color;
    this->text_warning_color = text_warning_color;

    this->idle_color = idle_color;
    this->line_color = line_color;

}

GameLogic::~GameLogic()
{
}

GameLogic::GameLogic(float x, float y, float width, float height,
    sf::Font* font,  std::string text, unsigned character_size,
    sf::Color text_idle_color, sf::Color idle_color, sf::Color line_color)
{
    this->button_states1 = BTN_NONE;
    this->button_states2 = BTN_IDL1;

    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setFillColor(sf::Color::White);
    this->shape.setOutlineThickness(3);
    this->shape.setOutlineColor(idle_color);

   

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

    this->line_idle_color = idle_color;
    this->line_active_color = line_color;
  
}

const bool GameLogic::is_pressed() const
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        return true;
    }
    return false;
}

const bool GameLogic::is_pressed_bounds(const sf::Vector2f mouse_pos) const
{
    if (this->shape.getGlobalBounds().contains(mouse_pos)  && 
        sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        return true;
    }
    return false;
}

void GameLogic::update(const sf::Vector2f mouse_pos)
{

    if (this->shape.getGlobalBounds().contains(mouse_pos) 
        && this->button_states1 != BTN_WARNING1 && sf::Mouse::isButtonPressed(sf::Mouse::Left) 
        && !pressed && button_states1 != BTN_NONE)
    {
        pressed = true;
        pressed1 = true;
    }

    if (pressed1 && !sf::Mouse::isButtonPressed(sf::Mouse::Left) && button_states1 != BTN_NONE)
    {
        if (this->button_states1 == BTN_IDL1)
            this->button_states1 = BTN_ACTIVE1;
        else
            this->button_states1 = BTN_IDL1;
        pressed1 = false;
        pressed = false;
    }

    
    if (this->shape.getGlobalBounds().contains(mouse_pos) 
        && sf::Mouse::isButtonPressed(sf::Mouse::Left)
        && !pressed && button_states2 != BTN_NONE)
    {
        pressed3 = true;
        pressed1 = true;
    }

    if (pressed1 && !sf::Mouse::isButtonPressed(sf::Mouse::Left) && button_states2 != BTN_NONE)
    {
        if (this->button_states2 == BTN_IDL1)
            this->button_states2 = BTN_ACTIVE1;
    }
 
    

    if (this->button_states1 != BTN_NONE)
    {
        switch (this->button_states1)
        {
        case BTN_IDL1:
            this->text.setFillColor(this->text_idle_color);
            break;

        case BTN_ACTIVE1:
            this->text.setFillColor(this->text_active_color);
            break;

        default:
            this->convex.setFillColor(sf::Color::Red);
            this->text.setFillColor(sf::Color::Blue);
            break;
        }
    }
    else
    {
        switch (this->button_states2)
        {
        case BTN_IDL1:
            this->shape.setOutlineColor(this->line_idle_color);
            break;

        case BTN_ACTIVE1:
            this->shape.setOutlineColor(this->line_active_color);
            break;
        }
    }
   
}

void GameLogic::render(sf::RenderTarget* target)
{
    target->draw(this->shape);
    target->draw(this->convex);
    target->draw(this->text);
    
}

void GameLogic::setText(std::string text)
{
    this->text.setString(text);
}

void GameLogic::refresh_buttons()
{
    if (button_states1 != BTN_NONE)
        this->button_states1 = BTN_IDL1;
    else
    {
        this->button_states2 = BTN_IDL1;
        this->pressed1 = false;
        this->pressed3 = false;
    }
        
}

void GameLogic::refresh_pressed()
{
    this->button_states2 = BTN_IDL1;
    this->pressed1 = false;
    this->pressed3 = false;
}

void GameLogic::set_pressed(bool temp)
{
    this->pressed1 = temp;
}

bool GameLogic::get_pressed()
{
    return this->pressed1;
}

std::string GameLogic::get_text()
{
    return this->text.getString();
}

void GameLogic::init_value()
{
    convex.setPointCount(5);
    convex.setOutlineThickness(2);
}
