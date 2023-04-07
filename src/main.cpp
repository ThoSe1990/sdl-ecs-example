#include "assets.hpp"
#include "game.hpp"


int main(int argc, char* argv[]) 
{
    cwt::game game(800, 600);

    auto bar = game.get_registry().create();
    game.get_registry().emplace<cwt::sprite_component>(bar, 
        SDL_Rect{0, 0, 50, 50}, 
        SDL_Rect{10, 10, 30, 110}, 
        IMG_LoadTexture(game.get_renderer(), orange_path)
    );
    game.get_registry().emplace<cwt::transform_component>(bar, 10.0f, 10.0f, 0.0f, 0.0f);
    game.get_registry().emplace<cwt::collider_component>(bar, 10.0f);
    game.get_registry().emplace<cwt::key_input_component>(bar);

    auto player = game.get_registry().create();
    game.get_registry().emplace<cwt::player_component>(player, std::size_t{0}, cwt::player_type::left);

    auto opponent = game.get_registry().create();
    game.get_registry().emplace<cwt::player_component>(opponent, std::size_t{0}, cwt::player_type::right);


    while(game.is_running()) 
    {
        game.read_input();
        game.update();
        game.render();
    }
    
    return 0;
}