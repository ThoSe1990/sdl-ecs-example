#include "game.hpp"


int main(int argc, char* argv[]) 
{
    cwt::game game;

    while(game.is_running()) 
    {
        game.update();
    }
    
    return 0;
}