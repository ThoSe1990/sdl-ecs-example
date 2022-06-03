

#include "game.hpp"
#include "cwt_pch/cwt_pch.hpp"

namespace cwt {

bool game::is_running()
{
    return m_sdl_window.is_running();
}

void game::on_update()
{
    std::cout << "game::on_update()" << std::endl;
    m_sdl_window.on_update();
}
void game::on_event()
{
    std::cout << "game::on_event()" << std::endl;
}


} // namespace cwt