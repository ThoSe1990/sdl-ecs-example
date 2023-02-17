#include "cwt_game_engine/engine.hpp"
#include "cwt_pch/cwt_pch.hpp"


int main(int argc, char* argv[]) 
{
    cwt::engine<cwt::sdl_window> engine;

    while(engine.is_running()) 
    {
        engine.on_update();
    }
    
    return 0;
}