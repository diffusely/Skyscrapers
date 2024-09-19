#pragma once

#include "State.h"
#include "Button.h"
#include "GameLogic.h"
#include "Matrix.h"


class MainMenuState
	: public State
{
public:

    MainMenuState(sf::RenderWindow* window,  std::stack<State*>* states, 
        std::vector<Matrix*> matrix);

    virtual ~MainMenuState();

    //Start game
    void start_game();

    //Functions
    int right_towern_count();
    virtual void input_number(char);
    bool chack_win();
    void update_dt();
    void init_clock();

    //Game numbers functions
    void right_number();
    void left_number();
    void up_number();
    void down_number();

    //render and update
    void update_buttons();
    void update(const float&);
    void render_buttons(sf::RenderTarget* target = NULL);
    void render(sf::RenderTarget* target = NULL);
    
 

protected:

    sf::Texture background_texture;
    sf::RectangleShape background;
    sf::Font font;


    //Start, Undo , New puzzle
    std::map<std::string, Button*> buttons;

    //Game Buttons
    std::map<std::string, GameLogic*> game_buttons;
    std::map<std::string, GameLogic*> shape_buttons;

    //Matrix
    std::vector<Matrix*> matrix;

    //Number Towern
    std::vector<std::string> Towern;

    //Number Matrix
    std::vector<std::string> MatrixNumber;

    //Game Matrix
    std::vector<std::string> Game_Matrix;

    //Game Time
    sf::Clock clock;
    float dt;

    //Timer
    sf::Text minut;
    sf::Text second;
    sf::Text timer;

    //Rand matrix number
    int rand_number;

    //win error text
    sf::Text win;
    sf::Text error;

    //Game bool
    bool start = false;
    bool is_error = false;
    bool is_win = false;

    //Init
    void init_fonts();
    void init_buttons();
    void init_text();
    void init_matrix();
    void init_matrix_number();
    void init_win_error_text();
};

