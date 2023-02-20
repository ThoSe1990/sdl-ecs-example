#pragma once

#include "pch.hpp"

#include "event/event.hpp"
#include "event/window_events.hpp"

#include "window.hpp"

namespace cwt {

template<typename Window> 
class engine
{
public: 
    bool is_running()
    {
        return m_is_running;
    }
    void on_update()
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
    Window m_window;
    bool m_is_running = true;
};


} // namespace cwt

