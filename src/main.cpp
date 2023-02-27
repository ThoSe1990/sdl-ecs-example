#include "game.hpp"
#include "bird.hpp"

int main(int argc, char* argv[]) 
{
    cwt::game game(800, 600);

    cwt::entity bird = cwt::create_entity();
    
    game.get_registry().sprites[bird] = cwt::sprite_component {
        SDL_Rect{0, 0, 300, 230}, 
        SDL_Rect{10, 10, 100, 73}, 
        IMG_LoadTexture(game.get_renderer(), bird_path)
    };
    game.get_registry().transforms[bird] = cwt::transform_component { 10, 10, 0, 0};
    game.get_registry().keys[bird] = cwt::keyinputs_component { };
    
    while(game.is_running()) 
    {
        game.read_input();
        game.update();
        game.render();
    }
    
    return 0;
}