#include "MainMenuState.h"


MainMenuState::MainMenuState(sf::RenderWindow* window, std::stack<State*>* states, std::vector<Matrix*> matrix)
	: State(window, states), Game_Matrix(16," ")
{
	srand(time(0));
	this->rand_number = rand() % 576;
	this->matrix = matrix;
	this->init_fonts();
	this->init_buttons();
	
	//Tower
	this->left_number();
	this->right_number();
	this->up_number();
	this->down_number();
	this->init_text();

	//Game Matrix
	this->init_matrix_number();
	this->init_matrix();

	init_clock();
	init_win_error_text();
}

MainMenuState::~MainMenuState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	for (auto it = this->game_buttons.begin(); it != this->game_buttons.end(); ++it)
	{
		delete it->second;
	}
}

void MainMenuState::right_number()
{
	int counter = 0;
	int max_val;
	std::vector<std::vector<int>> temp = this->matrix[rand_number]->getVector();

	

	for (int i = 0; i < 4; i++)
	{
		counter = 1;
		max_val = temp[i][3];
		for (int j = 0; j < 4; j++)
		{
			if (max_val < temp[i][3 - j])
			{
				max_val = temp[i][3 - j];
				counter++;
			}
		}
		std::string a = std::to_string(counter);
		this->Towern.push_back(a);
	} 
}

void MainMenuState::left_number()
{
	int counter = 0;
	int max_val;
	std::vector<std::vector<int>> temp = this->matrix[rand_number]->getVector();


	for (int i = 0; i < 4; i++)
	{
		counter = 1;
		max_val = temp[i][0];
		for (int j = 0; j < 4; j++)
		{
			if (max_val < temp[i][j])
			{
				max_val = temp[i][j];
				counter++;
			}
		}
		std::string a = std::to_string(counter);
		this->Towern.push_back(a);
	}
	
}

void MainMenuState::up_number()
{
	int counter = 0;
	int max_val;
	std::vector<std::vector<int>> temp = this->matrix[rand_number]->getVector();

	

	for (int i = 0; i < 4; i++)
	{
		counter = 1;
		max_val = temp[0][i];
		for (int j = 0; j < 4; j++)
		{
			if (max_val < temp[j][i])
			{
				max_val = temp[j][i];
				counter++;
			}
		}
		std::string a = std::to_string(counter);
		this->Towern.push_back(a);
	}
}

void MainMenuState::down_number()
{
	int counter = 0;
	int max_val;
	std::vector<std::vector<int>> temp = this->matrix[rand_number]->getVector();



	for (int i = 0; i < 4; i++)
	{
		counter = 1;
		max_val = temp[3][i];
		for (int j = 0; j < 4; j++)
		{
			if (max_val < temp[3 - j][i])
			{
				max_val = temp[3 - j][i];
				counter++;
			}
		}
		std::string a = std::to_string(counter);
		this->Towern.push_back(a);
	}
	
}

void MainMenuState::update_buttons()
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mouse_pos_view);
	}


	for (auto& it : this->game_buttons)
	{
		it.second->update(this->mouse_pos_view);
	}

	if (start) 
	{
		for (auto& it : this->shape_buttons)
		{
			if (it.second->is_pressed_bounds(this->mouse_pos_view))
			{
				for (auto& it1 : this->shape_buttons)
				{
	
					it1.second->refresh_pressed();

				}
				Sleep(100);
				it.second->set_pressed(true);
		
			}
			it.second->update(this->mouse_pos_view);
		}
	}
}

void MainMenuState::update(const float& dt)
{
	this->update_mouse_positions();
	this->update_buttons();
	this->start_game();
	update_dt();
}

void MainMenuState::render_buttons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

	for (auto& it : this->game_buttons)
	{
		it.second->render(target);
	}


	for (auto& it : this->shape_buttons)
	{
		it.second->render(target);
	}
	
	
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->window->draw(this->timer)
		;
	if (is_error)this->window->draw(this->error);
	if (is_win)this->window->draw(this->win);

	this->render_buttons(target);
}

void MainMenuState::start_game()
{
	if (this->buttons["Start"]->is_pressed() && !this->is_win)
	{
		this->timer.setFillColor(sf::Color::Black);
		this->start = true;
		
	}

	if (this->buttons["New Puzzle"]->is_pressed())
	{
		
		Sleep(100);
		this->rand_number = rand() % 576;

		this->is_win = false;
		this->is_error = false;

		this->Towern.clear();
	

		for (auto& it1 : this->shape_buttons)
		{
			it1.second->refresh_pressed();
			it1.second->update(this->mouse_pos_view);
		}
		

		this->start = false;
		this->timer.setString("00:00");
		this->timer.setFillColor(sf::Color::Black);
		this->minut.setFillColor(sf::Color::Black);
		this->second.setFillColor(sf::Color::Black);

		for (auto &it : game_buttons)
		{
			it.second->refresh_buttons();
		}

		for (auto& it : shape_buttons)
		{
			it.second->refresh_buttons();
		}

		//Towern
		this->left_number();
		this->right_number();
		this->up_number();
		this->down_number();
		this->init_text();

		//Matrix
		this->init_matrix_number();
		this->init_matrix();
		
		
		
	}

	if (this->buttons["Done"]->is_pressed())
	{
		Sleep(50);
		if (this->chack_win())
		{
			start = false;
			this->timer.setFillColor(sf::Color::Green);
			this->is_win = true;
			this->is_error = false;
		}	
		else
		{
			this->is_error = true;
		}
			
	}
}

int MainMenuState::right_towern_count()
{
	int counter = 0;
	int max_val;
	std::vector<std::vector<int>> temp = this->matrix[rand_number]->getVector();

	for (int i = 0; i < 4; i++)
	{
		counter = 1;
		max_val = temp[i][3];
		for (int j = 0; j < 4; j++)
		{
			if (max_val < temp[i][3 - j])
			{
				max_val = temp[i][3 - j];
				counter++;
			}
		}
		std::string a = std::to_string(counter);
		this->Towern.push_back(a);
	}
}

void MainMenuState::input_number(char key)
{
	int count = 0;

	for (auto& it : shape_buttons)
	{
		if (it.second->get_pressed() && 
			(static_cast<int>(key) == 27 ||static_cast<int>(key) == 28 || 
				static_cast<int>(key) == 29 ||	static_cast<int>(key) == 30))
		{
		
			switch (key)
			{
			case 27:
				if (it.second->get_text() == "1")
				{
					this->Game_Matrix[count] = " ";
					it.second->setText("");
				}
				else
				{
					this->Game_Matrix[count] = "1";
					it.second->setText("1");
				}
				break;
			case 28:
				if (it.second->get_text() == "2")
				{
					this->Game_Matrix[count] = " ";
					it.second->setText("");
				}
				else
				{
					this->Game_Matrix[count] = "2";
					it.second->setText("2");
				}
				break;
			case 29:
				if (it.second->get_text() == "3")
				{
					this->Game_Matrix[count] = " ";
					it.second->setText("");
				}
				else
				{
					this->Game_Matrix[count] = "3";
					it.second->setText("3");
				}
				break;
			case 30:
				if (it.second->get_text() == "4")
				{
					this->Game_Matrix[count] = " ";
					it.second->setText("");
				}
				else
				{
					this->Game_Matrix[count] = "4";
					it.second->setText("4");
				}
				break;
			default:
				break;
			}
		}
		++count;
	}
}

bool MainMenuState::chack_win()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (this->Game_Matrix != this->MatrixNumber)
				return false;
		}
	}
	return true;
}

void MainMenuState::update_dt()
{
	static int count = 0;
	static int minute = 0;

	if (start)
	{
		dt = this->clock.getElapsedTime().asSeconds();

		if (dt >= 1)
		{
			this->clock.restart();
			count++;
		}

		if (count == 60)
		{
			count = 0;
			minute++;
		}

		if (minute == 60)
		{
			minute = 0;
		}

		if (count < 10)
			this->second.setString("0" + std::to_string(count));
		else
			this->second.setString(std::to_string(count));

		if (minute < 10)
			this->minut.setString("0" + std::to_string(minute) + ":");
		else
			this->minut.setString(std::to_string(minute) + ":");
		
		this->timer.setString(minut.getString() + second.getString());
	}
	else
	{
		count = 0;
		minute = 0;
	}
}

void MainMenuState::init_clock()
{
	this->second.setFont(this->font);
	this->second.setFillColor(sf::Color::Blue);

	this->timer.setPosition(550, 55);
	this->timer.setFont(this->font);
	this->timer.setFillColor(sf::Color::Blue);

	this->minut.setFont(this->font);
	this->minut.setFillColor(sf::Color::Blue);
}


void MainMenuState::init_text()
{
	this->game_buttons["1_Left"]->setText(Towern[0]);
	this->game_buttons["2_Left"]->setText(Towern[1]);
	this->game_buttons["3_Left"]->setText(Towern[2]);
	this->game_buttons["4_Left"]->setText(Towern[3]);

	this->game_buttons["1_Right"]->setText(Towern[4]);
	this->game_buttons["2_Right"]->setText(Towern[5]);
	this->game_buttons["3_Right"]->setText(Towern[6]);
	this->game_buttons["4_Right"]->setText(Towern[7]);

	this->game_buttons["1_Up"]->setText(Towern[8]);
	this->game_buttons["2_Up"]->setText(Towern[9]);
	this->game_buttons["3_Up"]->setText(Towern[10]);
	this->game_buttons["4_Up"]->setText(Towern[11]);

	this->game_buttons["1_Down"]->setText(Towern[12]);
	this->game_buttons["2_Down"]->setText(Towern[13]);
	this->game_buttons["3_Down"]->setText(Towern[14]);
	this->game_buttons["4_Down"]->setText(Towern[15]);
}

void MainMenuState::init_matrix()
{
	this->shape_buttons["1"]->setText("");
	this->shape_buttons["2"]->setText("");
	this->shape_buttons["3"]->setText("");
	this->shape_buttons["4"]->setText("");
	this->shape_buttons["5"]->setText("");
	this->shape_buttons["6"]->setText("");
	this->shape_buttons["7"]->setText("");
	this->shape_buttons["8"]->setText("");
	this->shape_buttons["9"]->setText("");
	this->shape_buttons["a"]->setText("");
	this->shape_buttons["b"]->setText("");
	this->shape_buttons["c"]->setText("");
	this->shape_buttons["d"]->setText("");
	this->shape_buttons["e"]->setText("");
	this->shape_buttons["f"]->setText("");
	this->shape_buttons["w"]->setText("");
}

void MainMenuState::init_matrix_number()
{
	if (!MatrixNumber.empty())
		MatrixNumber.clear();

	std::vector<std::vector<int>> temp = this->matrix[rand_number]->getVector();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			this->MatrixNumber.push_back(std::to_string(temp[i][j]));
		}
	}
}

void MainMenuState::init_win_error_text()
{
	this->win.setPosition(360, 20);
	this->win.setCharacterSize(20);
	this->win.setFont(this->font);
	this->win.setFillColor(sf::Color::Green);
	this->win.setString("Congratulations! You have solved the puzzle");


	this->error.setPosition(400, 20);
	this->error.setCharacterSize(20);
	this->error.setFont(this->font);
	this->error.setFillColor(sf::Color::Red);
	this->error.setString("You have errors in the solution.");
}



void MainMenuState::init_fonts()
{
	if (!this->font.loadFromFile("Fonts/LEMONMILK-RegularItalic.otf"))
		throw("ERROR::FONT");
}


void MainMenuState::init_buttons()
{
	
	this->buttons["Start"] = new Button(480, 600, 80, 30, &this->font, "Start", 20,
		sf::Color(100, 100, 100), sf::Color(10, 10, 10), sf::Color(150, 150, 150), 
		sf::Color(sf::Color::White), sf::Color(sf::Color::Blue), sf::Color(20, 20, 20, 0));

	this->buttons["New Puzzle"] = new Button(570, 600, 130, 30, &this->font, "New Puzzle", 20,
		sf::Color(100, 100, 100), sf::Color(10, 10, 10), sf::Color(150, 150, 150),
		sf::Color(sf::Color::White), sf::Color(sf::Color::Blue), sf::Color(20, 20, 20, 0));

	this->buttons["Done"] = new Button(480, 550, 220, 30, &this->font, "Done", 20,
		sf::Color(100, 100, 100), sf::Color(10, 10, 10), sf::Color(150, 150, 150),
		sf::Color(sf::Color::White), sf::Color(sf::Color::Blue), sf::Color(20, 20, 20, 0));


	this->shape_buttons["1"] = new GameLogic(480, 200, 40, 40, &this->font, "0", 30,
		sf::Color(sf::Color::Black), sf::Color(sf::Color::Black), sf::Color(sf::Color::Blue));


	this->shape_buttons["2"] = new GameLogic(540, 200, 40, 40, &this->font, "0", 30,
		sf::Color(sf::Color::Black), sf::Color(sf::Color::Black), sf::Color(sf::Color::Blue));

	this->shape_buttons["3"] = new GameLogic(600, 200, 40, 40, &this->font, "0", 30,
		sf::Color(sf::Color::Black), sf::Color(sf::Color::Black), sf::Color(sf::Color::Blue));

	this->shape_buttons["4"] = new GameLogic(660, 200, 40, 40, &this->font, "0", 30,
		sf::Color(sf::Color::Black), sf::Color(sf::Color::Black), sf::Color(sf::Color::Blue));

	this->shape_buttons["5"] = new GameLogic(480, 260, 40, 40, &this->font, "0", 30,
		sf::Color(sf::Color::Black), sf::Color(sf::Color::Black), sf::Color(sf::Color::Blue));

	this->shape_buttons["6"] = new GameLogic(540, 260, 40, 40, &this->font, "0", 30,
		sf::Color(sf::Color::Black), sf::Color(sf::Color::Black), sf::Color(sf::Color::Blue));

	this->shape_buttons["7"] = new GameLogic(600, 260, 40, 40, &this->font, "0", 30,
		sf::Color(sf::Color::Black), sf::Color(sf::Color::Black), sf::Color(sf::Color::Blue));

	this->shape_buttons["8"] = new GameLogic(660, 260, 40, 40, &this->font, "0", 30,
		sf::Color(sf::Color::Black), sf::Color(sf::Color::Black), sf::Color(sf::Color::Blue));

	this->shape_buttons["9"] = new GameLogic(480, 320, 40, 40, &this->font, "0", 30,
		sf::Color(sf::Color::Black), sf::Color(sf::Color::Black), sf::Color(sf::Color::Blue));

	this->shape_buttons["a"] = new GameLogic(540, 320, 40, 40, &this->font, "0", 30,
		sf::Color(sf::Color::Black), sf::Color(sf::Color::Black), sf::Color(sf::Color::Blue));

	this->shape_buttons["b"] = new GameLogic(600, 320, 40, 40, &this->font, "0", 30,
		sf::Color(sf::Color::Black), sf::Color(sf::Color::Black), sf::Color(sf::Color::Blue));

	this->shape_buttons["c"] = new GameLogic(660, 320, 40, 40, &this->font, "0", 30,
		sf::Color(sf::Color::Black), sf::Color(sf::Color::Black), sf::Color(sf::Color::Blue));

	this->shape_buttons["d"] = new GameLogic(480, 380, 40, 40, &this->font, "0", 30,
		sf::Color(sf::Color::Black), sf::Color(sf::Color::Black), sf::Color(sf::Color::Blue));

	this->shape_buttons["e"] = new GameLogic(540, 380, 40, 40, &this->font, "0", 30,
		sf::Color(sf::Color::Black), sf::Color(sf::Color::Black), sf::Color(sf::Color::Blue));

	this->shape_buttons["f"] = new GameLogic(600, 380, 40, 40, &this->font, "0", 30,
		sf::Color(sf::Color::Black), sf::Color(sf::Color::Black), sf::Color(sf::Color::Blue));

	this->shape_buttons["w"] = new GameLogic(660, 380, 40, 40, &this->font, "0", 30,
		sf::Color(sf::Color::Black), sf::Color(sf::Color::Black), sf::Color(sf::Color::Blue));
	
		;	//Game buttons
	
	//Left
	this->game_buttons["1_Left"] = new GameLogic(400, 200, 40, false, &this->font, "0", 30,
		sf::Color(sf::Color::Black), sf::Color(200, 200, 200), sf::Color(sf::Color::Red),
		sf::Color(160, 160, 160), sf::Color(sf::Color::Black));

	this->game_buttons["2_Left"] = new GameLogic(400, 260, 40, false, &this->font, "0", 30,
		sf::Color(sf::Color::Black), sf::Color(200, 200, 200), sf::Color(sf::Color::Red),
		sf::Color(160, 160, 160), sf::Color(sf::Color::Black));

	this->game_buttons["3_Left"] = new GameLogic(400, 320, 40, false, &this->font, "0", 30,
		sf::Color(sf::Color::Black), sf::Color(200, 200, 200), sf::Color(sf::Color::Red),
		sf::Color(160, 160, 160), sf::Color(sf::Color::Black));

	this->game_buttons["4_Left"] = new GameLogic(400, 380, 40, false, &this->font, "0", 30,
		sf::Color(sf::Color::Black), sf::Color(200, 200, 200), sf::Color(sf::Color::Red),
		sf::Color(160, 160, 160), sf::Color(sf::Color::Black));







	//Right

	this->game_buttons["1_Right"] = new GameLogic(780, 240, -40, false, &this->font, "0", 30,
		sf::Color(sf::Color::Black), sf::Color(200, 200, 200), sf::Color(sf::Color::Red),
		sf::Color(160, 160, 160), sf::Color(sf::Color::Black));

	this->game_buttons["2_Right"] = new GameLogic(780, 300, -40, false, &this->font, "0", 30,
		sf::Color(sf::Color::Black), sf::Color(200, 200, 200), sf::Color(sf::Color::Red),
		sf::Color(160, 160, 160), sf::Color(sf::Color::Black));

	this->game_buttons["3_Right"] = new GameLogic(780, 360, -40, false, &this->font, "0", 30,
		sf::Color(sf::Color::Black), sf::Color(200, 200, 200), sf::Color(sf::Color::Red),
		sf::Color(160, 160, 160), sf::Color(sf::Color::Black));

	this->game_buttons["4_Right"] = new GameLogic(780, 420, -40, false, &this->font, "0", 30,
		sf::Color(sf::Color::Black), sf::Color(200, 200, 200), sf::Color(sf::Color::Red),
		sf::Color(160, 160, 160), sf::Color(sf::Color::Black));


	//Down

	this->game_buttons["1_Down"] = new GameLogic(520, 500, -40, true, &this->font, "0", 30,
		sf::Color(sf::Color::Black), sf::Color(200, 200, 200), sf::Color(sf::Color::Red),
		sf::Color(160, 160, 160), sf::Color(sf::Color::Black));

	this->game_buttons["2_Down"] = new GameLogic(580, 500, -40, true, &this->font, "0", 30,
		sf::Color(sf::Color::Black), sf::Color(200, 200, 200), sf::Color(sf::Color::Red),
		sf::Color(160, 160, 160), sf::Color(sf::Color::Black));

	this->game_buttons["3_Down"] = new GameLogic(640, 500, -40, true, &this->font, "0", 30,
		sf::Color(sf::Color::Black), sf::Color(200, 200, 200), sf::Color(sf::Color::Red),
		sf::Color(160, 160, 160), sf::Color(sf::Color::Black));

	this->game_buttons["4_Down"] = new GameLogic(700, 500, -40, true, &this->font, "0", 30,
		sf::Color(sf::Color::Black), sf::Color(200, 200, 200), sf::Color(sf::Color::Red),
		sf::Color(160, 160, 160), sf::Color(sf::Color::Black));

	//Up


	this->game_buttons["1_Up"] = new GameLogic(480, 120, 40, true, &this->font, "0", 30,
		sf::Color(sf::Color::Black), sf::Color(200, 200, 200), sf::Color(sf::Color::Red),
		sf::Color(160, 160, 160), sf::Color(sf::Color::Black));

	this->game_buttons["2_Up"] = new GameLogic(540, 120, 40, true, &this->font, "0", 30,
		sf::Color(sf::Color::Black), sf::Color(200, 200, 200), sf::Color(sf::Color::Red),
		sf::Color(160, 160, 160), sf::Color(sf::Color::Black));

	this->game_buttons["3_Up"] = new GameLogic(600, 120, 40, true, &this->font, "0", 30,
		sf::Color(sf::Color::Black), sf::Color(200, 200, 200), sf::Color(sf::Color::Red),
		sf::Color(160, 160, 160), sf::Color(sf::Color::Black));

	this->game_buttons["4_Up"] = new GameLogic(660, 120, 40, true, &this->font, "0", 30,
		sf::Color(sf::Color::Black), sf::Color(200, 200, 200), sf::Color(sf::Color::Red),
		sf::Color(160, 160, 160), sf::Color(sf::Color::Black));

}
