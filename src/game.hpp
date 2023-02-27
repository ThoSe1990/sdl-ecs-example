#pragma once

#include "pch.hpp"

#include "event/event.hpp"
#include "event/window_events.hpp"

#include "sdl_window.hpp"

namespace cwt {

class game
{
public: 
    bool is_running()
    {
        return m_is_running;
    }
    void update()
    {
        m_window.on_update(CWT_BIND_MEMBERFUNCTION(on_event));
    }

    void on_event(event& e)
    {
        if (e.is_in_category(event_category::window_events)) {
            event_dispatcher dispatcher(e);
            dispatcher.dispatch<close_window_event>(CWT_BIND_MEMBERFUNCTION(on_window_close_event));
        }
    }

private:
    void on_window_close_event(const close_window_event&)
    {
        this->m_is_running = false;
    }

private:
    sdl_window m_window;
    bool m_is_running = true;
};


} // namespace cwt

