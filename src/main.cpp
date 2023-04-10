

#include "assets.hpp"
#include "neural_net.hpp"
#include "game.hpp"



int main(int argc, char* argv[]) 
{
    srand(time(nullptr));

    cwt::game game(cwt::width, cwt::height, cwt::fps);

    auto bar = game.get_registry().create();
    game.get_registry().emplace<cwt::sprite_component>(bar, 
        SDL_Rect{0, 0, 50, 50}, 
        SDL_Rect{10, 10, cwt::bar_width, cwt::bar_height}, 
        IMG_LoadTexture(game.get_renderer(), orange_path)
    );
    auto& bar_t = game.get_registry().emplace<cwt::transform_component>(bar, 10.0f, 10.0f, 0.0f, 0.0f);
    game.get_registry().emplace<cwt::collider_component>(bar);
    game.get_registry().emplace<cwt::player_component>(bar, std::size_t{0}, cwt::player_type::right);
    game.get_registry().emplace<cwt::ai_component>(bar, std::vector<unsigned int>({2, 4, 1}));


    auto player = game.get_registry().create();
    game.get_registry().emplace<cwt::player_component>(player, std::size_t{0}, cwt::player_type::left);

    while(game.is_running()) 
    {

        game.read_input();
        game.update();
        game.render();
    }
    
    return 0;
}