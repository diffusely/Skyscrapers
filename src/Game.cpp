#include "Game.h"

Game::Game()
{
    init_read();
    init_window(); 
    init_icon();
    init_states();
}

Game::~Game()
{
    delete this->window;

    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }

    for (auto it : game_matrix)
    {
        delete it;
    }
}

void Game::run()
{
    while (window->isOpen())
    {
        this->update();
        this->render();
    }
}

void Game::start_game()
{
}

void Game::print()
{
    for (auto& it : game_matrix)
    {
        it->print();
    }
}

void Game::update()
{
    

    if (!this->states.empty())
    {
        this->states.top()->update(this->dt);

        if (this->states.top()->get_quit())
        {
            this->states.top()->end_state();
            delete this->states.top();
            this->states.pop();
        }
    }
game_event(); 
    update_dt();
    update_mouse_pos();
   

    
}

void Game::render()
{
    window->clear(sf::Color::White);
   
    if (!this->states.empty())
        this->states.top()->render(window);

    


    window->display();
}

void Game::update_dt()
{
    this->dt = this->dtClock.restart().asSeconds();
}


void Game::game_event()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
       /* if (event.type == sf::Event::Resized) 
        {
            sf::FloatRect test(0.0f, 0.0f, event.size.width, event.size.height);
            window->setView(sf::View(test));
        }*/

        //Press key 
        if (event.type == sf::Event::KeyPressed) 
        {
            char key = event.key.code;
            this->states.top()->input_number(key);
        }
    }
}

void Game::update_mouse_pos()
{
    sf::Mouse mouse;

   /* this->mouse_pos = mouse.getPosition();*/

   /* std::cout << mouse_pos.x <<
         " " <<mouse_pos.y << '\n';*/
}

void Game::init_window()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1200, 800), "Skyscrapers", 
        sf::Style::Titlebar | sf::Style::Close);
}

void Game::init_icon()
{
    sf::Image icon;
    if (!icon.loadFromFile("Resource/Icon/skyscrapers.png"));
    this->window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void Game::init_states()
{
    this->states.push(new MainMenuState(this->window, &this->states, this->game_matrix));
}

void Game::init_read()
{
    int value;
    this->fin.open("Bin/Matrix.txt", std::ios::in);
    if (!fin)
        std::cout << "ERROR::FIN";



    for (int i = 0; i < 576; i++)
    {
        std::vector<std::vector<int>> temp(4, std::vector<int>(4));

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                fin >> value;
                temp[i][j] = value;
            }
        }

        game_matrix.push_back(new Matrix(temp));
    }

}
