#include "engine/engine.hpp"


int main(int argc, char* argv[]) 
{
    cwt::engine<cwt::sdl_window, cwt::sdl_scene> engine;

    while(engine.is_running()) 
    {
        engine.on_update();
    }
    
    return 0;
}