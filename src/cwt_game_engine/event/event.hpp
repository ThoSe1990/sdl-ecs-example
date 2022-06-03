#pragma once

#define CWT_BIND_MEMBERFUNCTION(member_function) [this](auto&&... args) { return this->member_function(std::forward<decltype(args)>(args)...); }

#define BIT(x) (1 << x)

namespace cwt {

enum class event_type 
{
    none = 0,
    close_window
};

enum event_category
{
    none = 0,
    window_events = BIT(0)
};

struct event 
{
    virtual ~event() = default;

    virtual event_type get_type() const = 0;
    virtual const char* get_name() const = 0;
    virtual std::size_t get_category_flags() const = 0;
        
    bool is_in_category(event_category category)
    {
        return get_category_flags() & category;
    }
};

#define EVENT_CLASS_TYPE(type) static event_type get_concrete_type() { return event_type::type; }\
                                event_type get_type() const override { return get_concrete_type(); }\
                                const char* get_name() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual std::size_t get_category_flags() const override { return category; }


class event_dispatcher 
{
private:
    event& m_event;
public: 
    event_dispatcher(event& e) : m_event(e) {}

    template<typename T, typename F> 
    void dispatch(const F& function) 
    {
        if (m_event.get_type() == T::get_concrete_type())
        {
            function(static_cast<T&>(m_event));
        }
    }
};


} // namespace cwt


