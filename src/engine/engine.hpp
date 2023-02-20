#pragma once

#include "pch.hpp"

#include "event/event.hpp"
#include "event/window_events.hpp"

#include "window.hpp"

namespace cwt {

template<typename WindowType, typename SceneType> 
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
        // all systems: .update(m_active_scene.get_registry())
        m_window.on_render(m_active_scene);
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
    WindowType m_window;
    SceneType m_active_scene;
    bool m_is_running = true;
};


} // namespace cwt

