#include "game.hpp"
#include "bird.hpp"


int main(int argc, char* argv[]) 
{
    cwt::game game(800, 600);

    cwt::entity bird_1 = cwt::create_entity();
    game.get_registry().sprites[bird_1] = cwt::sprite_component {
        SDL_Rect{0, 0, 300, 230}, 
        SDL_Rect{10, 10, 100, 73}, 
        IMG_LoadTexture(game.get_renderer(), bird_path)
    };
    game.get_registry().transforms[bird_1] = cwt::transform_component { 10, 10, 0, 0};
    game.get_registry().keys[bird_1] = cwt::keyinputs_component { };
    

    cwt::entity bird_2 = cwt::create_entity();
    game.get_registry().sprites[bird_2] = cwt::sprite_component {
        SDL_Rect{0, 0, 300, 230}, 
        SDL_Rect{0, 0, 100, 73}, 
        IMG_LoadTexture(game.get_renderer(), bird_path)
    };
    game.get_registry().transforms[bird_2] = cwt::transform_component { 10, 500, 0.01f, -0.01f};

    cwt::entity bird_3 = cwt::create_entity();
    game.get_registry().sprites[bird_3] = cwt::sprite_component {
        SDL_Rect{0, 0, 300, 230}, 
        SDL_Rect{200, 300, 100, 73}, 
        IMG_LoadTexture(game.get_renderer(), bird_path)
    };

    while(game.is_running()) 
    {
        game.read_input();
        game.update();
        game.render();
    }
    
    return 0;
}