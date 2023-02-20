#pragma once

namespace cwt
{


    class sdl_window 
    {
    private:
        std::size_t m_width;
        std::size_t m_height;

        SDL_Window* m_window; 
        SDL_Renderer* m_renderer;
        
    public:
        sdl_window()
        {
            m_window = SDL_CreateWindow(
                "cwt game engine SDL2 window",                  // window title
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


        template<typename EventCallback>
        void on_update(EventCallback&& event_callback) 
        {
            SDL_Event sdl_event;
            SDL_PollEvent(&sdl_event);
            switch (sdl_event.type) {
                case SDL_QUIT: {
                    close_window_event e;
                    event_callback(e);
                    break;
                }
                case SDL_KEYDOWN: {
                    if (sdl_event.key.keysym.sym == SDLK_ESCAPE) {
                        close_window_event e;
                        event_callback(e);
                    }
                }
                default: {
                    break;
                }
            }

            SDL_SetRenderDrawColor(m_renderer, 21, 21, 21, 255);
            SDL_RenderClear(m_renderer);
            SDL_RenderPresent(m_renderer);
        }

    };
} // namespace cwt
