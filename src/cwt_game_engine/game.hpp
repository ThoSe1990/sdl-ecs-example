#pragma once

#include "window.hpp"

namespace cwt {

class game
{
private:

    window m_sdl_window;

public: 
    bool is_running();
    void on_update();
    void on_event();
};


} // namespace cwt