//
// Created by Rob Hendriks on 19/10/2016.
//

#ifndef CITY_DEFENCE_ENGINE_H
#define CITY_DEFENCE_ENGINE_H

#include <string>
#include <exception>
#include "window.h"
#include "engine_config.h"
#include "audio/sound_manager.h"
#include "audio/music_manager.h"
#include "graphics/texture_manager.h"
#include "graphics/color_manager.h"

namespace engine {

    enum state {
        CREATED, WARMEDUP, RUNNING, PAUSED, STOPPED, COOLEDDOWN
    };

    class engine {
    public:
        engine(engine_config &config);

        void warmup();

        void run();

        void pause();

        void resume();

        void stop();

        void cooldown();

        unsigned int get_game_ticks() const;

        unsigned int get_paused_ticks() const;

        unsigned int get_time_elapsed(float interpolation = 1) const;

        state get_state() const;

        graphics::texture_manager *get_texture_manager() const;

        graphics::color_manager *get_color_manager() const;

        audio::sound_manager *get_sound_manager() const;

        audio::music_manager *get_music_manager() const;

        window *get_window() const;
    protected:
        void loop();

        void update();

        void init_sdl();

        void create_window();

    private:
        window* m_window;
        audio::sound_manager *m_sound_manager;
        audio::music_manager *m_music_manager;
        graphics::texture_manager *m_texture_manager;
        graphics::color_manager *m_color_manager;
        engine_config &m_config;
        state m_state;

        unsigned int m_ticks_when_paused;
        unsigned int m_paused_ticks;
        unsigned int m_game_ticks;
    };
}

#endif //CITY_DEFENCE_ENGINE_H
