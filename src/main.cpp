#include "game.hpp"


int main(int argc, char* argv[]) 
{
    cwt::game game(800, 600);

    while(game.is_running()) 
    {
        game.read_input();
        game.update();
        game.render();
    }
    
    return 0;
}