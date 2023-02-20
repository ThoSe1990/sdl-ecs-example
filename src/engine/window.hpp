#pragma once

namespace cwt
{

    class sdl_scene 
    {
    public:
        void on_update()
        {

        }

        void on_render(SDL_Renderer* renderer)
        {
            SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
            SDL_RenderClear(renderer);

            auto src = SDL_Rect{0, 0, 300, 230};
            auto dst = SDL_Rect{10, 10, 80, 60}; 
            auto texture = IMG_LoadTexture(renderer, "D:\\git\\cwt_game_engine\\src\\playground\\bird_up.png");
            SDL_RenderCopy(renderer, texture, &src, &dst);

            SDL_RenderPresent(renderer);
        }
    private:
    private:
        // registry 
    };

    class sdl_window 
    {    
    public:
        sdl_window()
        {
            m_window = SDL_CreateWindow(
                "cwt game engine - SDL2 window",                  // window title
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
        }

        void on_render(sdl_scene& active_scene)
        {
            active_scene.on_render(m_renderer);
        }
    private: 

    private:
        std::size_t m_width;
        std::size_t m_height;
        SDL_Window* m_window; 
        SDL_Renderer* m_renderer;
    };


} // namespace cwt
