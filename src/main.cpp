#include "game.hpp"
#include "bird.hpp"


int main(int argc, char* argv[]) 
{
    cwt::game game(800, 600);

    auto bird_1 = game.get_registry().create();
    game.get_registry().emplace<cwt::sprite_component>(bird_1, 
        SDL_Rect{0, 0, 300, 230}, 
        SDL_Rect{10, 10, 100, 73}, 
        IMG_LoadTexture(game.get_renderer(), bird_path)
    );
    game.get_registry().emplace<cwt::transform_component>(bird_1, 10.0f, 10.0f, 0.0f, 0.0f);
    game.get_registry().emplace<cwt::keyinputs_component>(bird_1);
    

    auto bird_2 = game.get_registry().create();
    game.get_registry().emplace<cwt::sprite_component>(bird_2, 
        SDL_Rect{0, 0, 300, 230}, 
        SDL_Rect{0, 0, 100, 73}, 
        IMG_LoadTexture(game.get_renderer(), bird_path)
    );
    game.get_registry().emplace<cwt::transform_component>(bird_2, 10.0f, 500.0f, 0.01f, -0.01f);

    auto bird_3 = game.get_registry().create();
    game.get_registry().emplace<cwt::sprite_component>(bird_3, 
        SDL_Rect{0, 0, 300, 230}, 
        SDL_Rect{200, 300, 100, 73}, 
        IMG_LoadTexture(game.get_renderer(), bird_path)
    );

    while(game.is_running()) 
    {
        game.read_input();
        game.update();
        game.render();
    }
    
    return 0;
}