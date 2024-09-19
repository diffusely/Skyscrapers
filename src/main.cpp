#include "Game.h"

bool GameLogic::pressed = false;
bool GameLogic::pressed3 = false;

//int main()
//{
//
//    Game game;
//    game.run();
//
//}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Game game;
    game.run(); 
}