#include <iostream>
#include "EventManager.h"
void Game()
{
    GameManager::Get()->launchGame();
}

int main()
{
    EventManager::Create();
    GameManager::Create();
    Game();


    return 0;
}
