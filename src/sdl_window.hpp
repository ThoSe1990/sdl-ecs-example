#pragma once

namespace cwt
{
    class sdl_window 
    {    
    public:
        sdl_window()
        {
            m_window = SDL_CreateWindow(
                "sdl window",                  // window title
                SDL_WINDOWPOS_UNDEFINED,           // initial x position
                SDL_WINDOWPOS_UNDEFINED,           // initial y position
                640,                               // width, in pixels
                480,                               // height, in pixels
                SDL_WINDOW_OPENGL                  // flags - see below
            );

            if (m_window == NULL) {
                std::cout << "Could not create window: " << SDL_GetError() << '\n';
            }
            m_renderer = SDL_CreateRenderer(m_window, -1, 0);
            if (!m_renderer) {
                std::cout << "Error creating SDL renderer.\n";
                return;
            }
        }
        ~sdl_window()
        {       
            SDL_DestroyWindow(m_window);
            SDL_Quit();
        }

        SDL_Renderer* get_renderer() { return m_renderer; }


        template<typename EventCallback>
        void on_update(EventCallback&& event_callback) 
        {
            SDL_Event sdl_event;
            SDL_PollEvent(&sdl_event);
            SDL_GetKeyboardState(NULL);
            
            const Uint8* keystates = SDL_GetKeyboardState(NULL);
            if (keystates[SDL_SCANCODE_ESCAPE]) {
                close_window_event e;
                event_callback(e);
            }
        }

    private: 

    private:
        std::size_t m_width;
        std::size_t m_height;
        SDL_Window* m_window; 
        SDL_Renderer* m_renderer;
    };


} // namespace cwt
