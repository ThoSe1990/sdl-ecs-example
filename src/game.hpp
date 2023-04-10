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

#include "imgui.h"
#include "bindings/imgui_impl_sdl.h"
#include "bindings/imgui_impl_sdlrenderer.h"

namespace cwt {


constexpr static const std::size_t width = 800;
constexpr static const std::size_t height = 600;
constexpr static const std::size_t fps = 60;

constexpr static const float bullet_speed = 50.0f;
constexpr static const std::size_t bullet_size = 20;
constexpr static const float bullet_freq = 0.3f;

constexpr static const float bar_speed = 300.0f;
constexpr static const std::size_t bar_width = 30;
constexpr static const std::size_t bar_height = 30;



float random_float(float lower_limit, float upper_limit) {
    float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    return lower_limit + random * (upper_limit - lower_limit);
}

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

struct ai_component
{
    neural_net net;
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
            // if (t.pos_y > height-50 || t.pos_y <= -50) {
            //     return;
            // }
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
            if (keys[SDL_SCANCODE_W]) { t.vel_y = -bar_speed; } 
            if (keys[SDL_SCANCODE_S]) { t.vel_y = bar_speed; }
            if (!keys[SDL_SCANCODE_W] && !keys[SDL_SCANCODE_S]) { t.vel_y = 0.0f; }
        });
    }
};

struct bullet_system
{
    void update(entt::registry& reg, SDL_Renderer* renderer, const float dt)
    {
        m_time_count += dt;
        if (m_time_count > bullet_freq)
        {
            m_time_count = 0;
            std::size_t y = random_float(0.0f, static_cast<float>(height));
            auto bullet = reg.create();
            reg.emplace<sprite_component>(bullet, 
                SDL_Rect{0, 0, 50, 50}, 
                SDL_Rect{780, static_cast<int>(y), bullet_size, bullet_size}, 
                IMG_LoadTexture(renderer, blue_path)
            );
            reg.emplace<transform_component>(bullet, 780.0f, static_cast<float>(y), -bullet_speed, 0.0f);
            reg.emplace<collider_component>(bullet);
            reg.emplace<bullet_component>(bullet);
        }

        auto bullets_view = reg.view<transform_component, const collider_component, bullet_component>();
        bullets_view.each([&reg](const auto entity, auto& t, const auto& c){
            if (c.collision) {
                t.vel_x = bullet_speed;
            }
        });
    }

    private:
        float m_time_count;
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
                    (player.type == player_type::right && t.pos_x > width)
                ) {
                    ++player.score;
                    reg.destroy(entity);
                } 
            });
        });
    }
};


struct ai_system 
{
    void update(entt::registry& reg, SDL_Renderer* renderer)
    {
        transform_component bullet;
        bullet.pos_x = width;
        bool no_bullet = true;
        reg.view<const transform_component, const bullet_component>().each([&bullet, &no_bullet](const auto& t)
        {
            if (t.pos_x <= bullet.pos_x && t.vel_x < 0.0f) {
                no_bullet = false;
                bullet = t;
            }
        });

        reg.view<ai_component, transform_component>().each([this, &bullet, &no_bullet](auto& ai, auto& t)
        {
            const float bar_center_x = t.pos_x + bar_width/2;
            const float bar_center_y = t.pos_y + bar_height/2;

            const std::size_t bullet_center_x = bullet.pos_x + bullet_size/2;
            const std::size_t bullet_center_y = bullet.pos_y + bullet_size/2;
            

            ai.net.feed_forward({bar_center_y, bullet.pos_y});
            auto result = ai.net.get_result(); // [0.0 .. 1.0] 
            t.vel_y = map_to_speed(static_cast<float>(result[0]));

            const float delta_pos = bullet_center_y - bar_center_y;
            float expected_velocity = 0.5f;
   
            if (no_bullet) {
                expected_velocity = 0.5f;
            } else if ( std::abs(delta_pos) - static_cast<float>(bar_height*2) < 0.0f) {
                expected_velocity = (delta_pos + static_cast<float>(width)) / static_cast<float>(width*2);
            } else if (delta_pos > static_cast<float>(bar_height/2) ) {
                expected_velocity = 1.0f;
            } else if (delta_pos < -1.0f * static_cast<float>(bar_height/2)) {
                expected_velocity = 0.0f;
            }

            std::vector<double> target_values;
            target_values.push_back(expected_velocity);
            ai.net.back_prop(target_values);

            if (!no_bullet)
            std::cout << bar_center_y << ' ' << bullet_center_y << std::endl;

        });
    }



    private: 
        std::size_t x1,y1,x2,y2;

        float map_to_speed(const float value)
        {
            // map from 0..1 to -1..1 and apply speed
            return ((value * 2.0f) - 1.0f) * bar_speed;
        }
        
};

class game
{
    public: 
        game(const std::size_t width, const std::size_t height, const std::size_t fps) : m_width(width), m_height(height), m_time_per_frame(1000/fps)
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

            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
            io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   
            ImGui::StyleColorsDark();
            ImGui_ImplSDL2_InitForSDLRenderer(m_window, m_renderer);
            ImGui_ImplSDLRenderer_Init(m_renderer);

            m_is_running = true;
        }
        ~game()
        {       
            ImGui_ImplSDLRenderer_Shutdown();
            ImGui_ImplSDL2_Shutdown();
            ImGui::DestroyContext();

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
            ImGui_ImplSDL2_ProcessEvent(&sdl_event);
            const Uint8* keystates = SDL_GetKeyboardState(NULL);

            if (keystates[SDL_SCANCODE_ESCAPE] || sdl_event.type == SDL_QUIT) {
                m_is_running = false;
            }
        }
        void update()
        {
            delta_time();
            
            m_coillision_system.update(m_registry);
            m_bullet_system.update(m_registry, m_renderer, m_dt);
            // m_movement_system.update(m_registry);
            m_ai_system.update(m_registry, m_renderer);
            m_transform_system.update(m_registry);
            m_sprite_system.update(m_registry);
            m_score_system.update(m_registry);
            
        }
        void render()
        {
            SDL_RenderClear(m_renderer);
            // render_imgui();
            m_sprite_system.render(m_registry, m_renderer);
            SDL_RenderPresent(m_renderer);
        }

    private:
        void delta_time()
        {
            int time_to_wait = m_time_per_frame - (SDL_GetTicks() - m_ticks_last_frame);
            if (time_to_wait > 0 && time_to_wait <= m_time_per_frame) {
                SDL_Delay(time_to_wait);
            }
            m_dt = (SDL_GetTicks() - m_ticks_last_frame) / 1000.0f;
            m_ticks_last_frame = SDL_GetTicks();
        }
        void render_imgui()
        {
            ImGui_ImplSDLRenderer_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();
            ImGui::Begin("Hello, world!");  
            ImGui::End();
            ImGui::Render();
            
            ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
        }


    private:
        const std::size_t m_width;
        const std::size_t m_height;
        const std::size_t m_time_per_frame;
        std::size_t m_ticks_last_frame;
        float m_dt;

        SDL_Window* m_window; 
        SDL_Renderer* m_renderer;
        bool m_is_running;

        entt::registry m_registry;

        score_system m_score_system;
        // movement_system m_movement_system;
        bullet_system m_bullet_system;
        sprite_system m_sprite_system;
        transform_system m_transform_system;
        collision_system m_coillision_system;
        ai_system m_ai_system;
};


} // namespace cwt

