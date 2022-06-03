#pragma once

#include "cwt_pch/cwt_pch.hpp"

namespace cwt
{
    class window
    {
    private:
        std::size_t m_width;
        std::size_t m_height;

        bool m_is_running = false;

        SDL_Window* m_window; 
        SDL_Event m_sdl_event;
    public:
        window()
        {
            m_window = SDL_CreateWindow(
                "An SDL2 window",                  // window title
                SDL_WINDOWPOS_UNDEFINED,           // initial x position
                SDL_WINDOWPOS_UNDEFINED,           // initial y position
                640,                               // width, in pixels
                480,                               // height, in pixels
                SDL_WINDOW_OPENGL                  // flags - see below
            );

            // Check that the window was successfully created
            if (m_window == NULL) {
                // In the case that the window could not be made...
                printf("Could not create window: %s\n", SDL_GetError());
            }
            m_is_running = true;
        }

        ~window()
        {       
            SDL_DestroyWindow(m_window);
            SDL_Quit();
        }

        bool is_running() { return m_is_running; }

        void on_update()
        {
            SDL_PollEvent(&m_sdl_event);
            switch (m_sdl_event.type) {
                case SDL_QUIT: {
                    m_is_running = false;
                    break;
                }
                case SDL_KEYDOWN: {
                    if (m_sdl_event.key.keysym.sym == SDLK_ESCAPE) {
                        m_is_running = false;
                    }
                }
                default: {
                    break;
                }
            }
        }

    };
} // namespace cwt
