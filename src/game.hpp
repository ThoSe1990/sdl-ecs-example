#pragma once

#include <any>
#include <vector>
#include <memory>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


namespace cwt {

class game
{
    public: 
        game(std::size_t width, std::size_t height) : m_width(width), m_height(height)
        {
            m_window = SDL_CreateWindow(
                "sdl window",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                m_width,
                m_height,
                NULL
            );

            if (m_window == NULL) {
                std::cout << "Could not create window: " << SDL_GetError() << '\n';
                m_is_running = false;
            }
            m_renderer = SDL_CreateRenderer(m_window, -1, 0);
            if (!m_renderer) {
                std::cout << "Error creating SDL renderer.\n";
                m_is_running = false;
            }

            m_is_running = true;
        }
        ~game()
        {       
            SDL_DestroyWindow(m_window);
            SDL_Quit();
        }

        bool is_running()
        {
            return m_is_running;
        }
        void read_input()
        {
            SDL_Event sdl_event;
            SDL_PollEvent(&sdl_event);            
            const Uint8* keystates = SDL_GetKeyboardState(NULL);

            if (keystates[SDL_SCANCODE_ESCAPE]) {
                m_is_running = false;
            }
        }
        void update()
        {

        }
        void render()
        {
            SDL_RenderClear(m_renderer);

            SDL_RenderPresent(m_renderer);
        }

    private:
        std::size_t m_width;
        std::size_t m_height;
        SDL_Window* m_window; 
        SDL_Renderer* m_renderer;
        bool m_is_running;
};


} // namespace cwt

