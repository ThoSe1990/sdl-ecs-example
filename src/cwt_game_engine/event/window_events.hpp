#pragma once


namespace cwt {

struct close_window_event : public event 
{
    EVENT_CLASS_TYPE(close_window);
    EVENT_CLASS_CATEGORY(event_category::window_events);    
};

} // namespace cwt 