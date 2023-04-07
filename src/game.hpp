#pragma once

#include <any>
#include <vector>
#include <memory>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <unordered_map>

#include <entt/entt.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


namespace cwt {

struct sprite_component{
    SDL_Rect src;
    SDL_Rect dst;
    SDL_Texture* texture;
};

struct transform_component{
    float pos_x;
    float pos_y;
    float vel_x;
    float vel_y;
};

struct input_component
{ 
    struct {
        int x; 
        int y;
        bool left_button;
    } mouse;
};

struct collider_component 
{
    float radius;
    bool collision;
};
struct key_input_component {};
struct bullet_component {};

enum class player_type{
    left = 0,
    right
};
struct player_component 
{
    std::size_t score;
    player_type type;
};


struct collision_system
{
    void update(entt::registry& reg)
    {
        auto view = reg.view<sprite_component, collider_component>();
        for (auto entity1 : view) {
            auto& sprite1 = view.get<sprite_component>(entity1);
            auto& col1 = view.get<collider_component>(entity1);
            
            for (auto entity2 : view) {
                if (entity1 == entity2) {
                    continue;
                } 
                
                auto& sprite2 = view.get<sprite_component>(entity2);
                auto& col2 = view.get<collider_component>(entity2);
                
                col1.collision = has_colition(sprite1.dst, sprite2.dst);
                col2.collision = col1.collision;
            }
        }
    }
    private: 
        bool has_colition(const SDL_Rect& rect1, const SDL_Rect& rect2)
        {
            return rect1.x + rect1.w >= rect2.x &&
                rect2.x + rect2.w >= rect1.x &&
                rect1.y + rect1.h >= rect2.y &&
                rect2.y + rect2.h >= rect1.y;
        }
};


struct sprite_system 
{
    void update(entt::registry& reg)
    {
        auto view = reg.view<sprite_component, transform_component>();
        view.each([](auto &s, auto &t){
                s.dst.x = t.pos_x;
                s.dst.y = t.pos_y;
        });
    }
    void render(entt::registry& reg, SDL_Renderer* renderer)
    {
        auto view = reg.view<sprite_component>();
        view.each([renderer](auto &s){
             SDL_RenderCopy(
                    renderer, 
                    s.texture, 
                    &s.src, 
                    &s.dst
                );
        });
    }
};

struct transform_system 
{
    float dt = 0.1f;
    
    void update(entt::registry& reg)
    {
        auto view = reg.view<transform_component>();
        view.each([](auto &t){
            t.pos_x += t.vel_x*0.1f;
            t.pos_y += t.vel_y*0.1f;            
        });
    }
};

struct movement_system 
{  
    void update(entt::registry& reg)
    {
        const Uint8* keys = SDL_GetKeyboardState(NULL);
        auto key_movement = reg.view<transform_component, key_input_component>();
        key_movement.each([&keys](auto &t){
            if (keys[SDL_SCANCODE_W]) { t.vel_y = -2.5f; } 
            if (keys[SDL_SCANCODE_S]) { t.vel_y = 2.5f; }
            if (!keys[SDL_SCANCODE_W] && !keys[SDL_SCANCODE_S]) { t.vel_y = 0.0f; }
        });
    }
};

struct bullet_system
{
    void update(entt::registry& reg, SDL_Renderer* renderer)
    {
        int x,y;
        bool mouse_left = SDL_GetMouseState(&x, &y);
        if (mouse_left == false && m_last_mouse_left) 
        {
            auto bullet = reg.create();
            reg.emplace<sprite_component>(bullet, 
                SDL_Rect{0, 0, 50, 50}, 
                SDL_Rect{780, y, 15, 15}, 
                IMG_LoadTexture(renderer, blue_path)
            );
            reg.emplace<transform_component>(bullet, 780.0f, static_cast<float>(y), -2.5f, 0.0f);
            reg.emplace<collider_component>(bullet, 10.0f);
            reg.emplace<bullet_component>(bullet);
        }
        m_last_mouse_left = mouse_left;

        auto bullets_view = reg.view<transform_component, const collider_component, bullet_component>();
        bullets_view.each([&reg](const auto entity, auto& t, const auto& c){
            if (c.collision) {
                t.vel_x = 2.5f;
            }
            if (t.pos_x > 800 || t.pos_x < 0) {
                std::cout << "delete me" << std::endl;
                reg.destroy(entity);
            }
        });
    }

    private:
        bool m_last_mouse_left{false};
};


struct score_system
{
    void update(entt::registry& reg)
    {
        auto bullets_view = reg.view<const transform_component, bullet_component>();
        auto player_view = reg.view<player_component>();

        bullets_view.each([&reg, &player_view](const auto entity, const auto& t)
        {
            player_view.each([&reg, &entity, &t](auto& player){
                
                if (
                    (player.type == player_type::left && t.pos_x < 0) ||
                    (player.type == player_type::right && t.pos_x > 800)
                ) {
                    ++player.score;
                    reg.destroy(entity);
                } 
            });

            // if (t.pos_x > 800 || t.pos_x < 0) {
            //     std::cout << "delete me" << std::endl;
            //     reg.destroy(entity);
            // }
        });
    }
};

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

        entt::registry& get_registry() { return m_registry; }
        SDL_Renderer* get_renderer() { return m_renderer; }

        bool is_running()
        {
            return m_is_running;
        }
        void read_input()
        {
            SDL_Event sdl_event;
            SDL_PollEvent(&sdl_event);            
            const Uint8* keystates = SDL_GetKeyboardState(NULL);

            if (keystates[SDL_SCANCODE_ESCAPE] || sdl_event.type == SDL_QUIT) {
                m_is_running = false;
            }
        }
        void update()
        {
            m_coillision_system.update(m_registry);
            m_bullet_system.update(m_registry, m_renderer);
            m_movement_system.update(m_registry);
            m_transform_system.update(m_registry);
            m_sprite_system.update(m_registry);
            m_score_system.update(m_registry);
        }
        void render()
        {
            SDL_RenderClear(m_renderer);

            m_sprite_system.render(m_registry, m_renderer);

            SDL_RenderPresent(m_renderer);
        }

    private:
        std::size_t m_width;
        std::size_t m_height;
        SDL_Window* m_window; 
        SDL_Renderer* m_renderer;
        bool m_is_running;

        entt::registry m_registry;

        score_system m_score_system;
        movement_system m_movement_system;
        bullet_system m_bullet_system;
        sprite_system m_sprite_system;
        transform_system m_transform_system;
        collision_system m_coillision_system;
};


} // namespace cwt

