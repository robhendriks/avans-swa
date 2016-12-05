//
// Created by Rob Hendriks on 19/10/2016.
//

#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "engine.h"
#include "input/input_handler.h"
#include "eventbus/eventbus.h"
#include "events/window_cleared.h"
#include "events/display_changed.h"
#include "events/game_tick.h"

namespace engine {
    engine::engine(engine_config &config) : m_window(nullptr), m_sound_manager(nullptr), m_music_manager(nullptr),
                                            m_texture_manager(nullptr), m_color_manager(nullptr), m_config(config),
                                            m_state(CREATED), m_ticks_when_paused(0), m_paused_ticks(0),
                                            m_game_ticks(0) {
    }

    /**
     * Warmup the engine, here SDL will be initialized and the window will be created. Also the different managers
     * like sound- and musicmanager will be created.
     */
    void engine::warmup() {
        try {
            init_sdl();
            create_window();
            m_state = WARMEDUP;
        } catch (std::runtime_error &e) {
            fprintf(stderr, "%s\n", e.what());
            return;
        }
    }

    /**
     * Start with running the engine, this will only have effect when the current state is WARMEDUP
     */
    void engine::run() {
        if (m_state == WARMEDUP) {
            m_state = RUNNING;
            loop();
        }
    }

    /**
     * Set the pause state, this will only have effect when the current state is RUNNING
     *
     * Note that pausing the engine has no effect on the gameloop, the gameloop will just continue running. The paused
     * state has really only effect on the time elapsed and paused ticks functions.
     */
    void engine::pause() {
        if (m_state == RUNNING) {
            m_state = PAUSED;
            m_ticks_when_paused = m_game_ticks;
        }
    }

    /**
     * Resume after a pause, will only have effect when the current state is PAUSED
     *
     * Like the pause() method this will not effect the gameloop.
     */
    void engine::resume() {
        if (m_state == PAUSED) {
            m_state = RUNNING;
            m_paused_ticks += (m_game_ticks - m_ticks_when_paused);
        }
    }

    /**
     * The game loop
     */
    void engine::loop() {
        printf("[DEBUG] Starting gameloop...\n");

        auto next_game_tick = SDL_GetTicks();
        int loops;
        float interpolation;
        while (m_state == RUNNING || m_state == PAUSED) {
            loops = 0;
            while (SDL_GetTicks() > next_game_tick && loops < m_config.max_frameskip) {
                update();

                next_game_tick += m_config.get_skip_ticks();
                loops++;
                m_game_ticks++;
            }

            m_window->clear();

            interpolation =
                float(SDL_GetTicks() + m_config.get_skip_ticks() - next_game_tick) / float(m_config.get_skip_ticks());

            // Fire event clear event
            auto *clear_event = new events::window_cleared(get_time_elapsed(interpolation), m_game_ticks, interpolation);
            eventbus::eventbus::get_instance().fire(*clear_event);
            delete clear_event;

            m_window->present();
        }
    }

    /**
     * Update the game states (handle the input)
     */
    void engine::update() {
        auto &eventbus = eventbus::eventbus::get_instance();

        // Fire the game tick event
        auto *game_tick_event = new events::game_tick(m_game_ticks, get_time_elapsed());
        eventbus.fire(game_tick_event);
        delete game_tick_event;

        // Handle the SDL events
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            // Check for the QUIT event
            if (event.type == SDL_QUIT) {
                stop();
            } else if (event.type == SDL_WINDOWEVENT) {
                m_window->trigger_display_change();
            }

            // Update the input handler
            input::input_handler::get_instance()->update(event);
        }
    }

    /**
     * Stop the gameloop
     */
    void engine::stop() {
        m_state = STOPPED;
    }

    /**
     * Cooldown the engine, this will delete/destroy the window, SDL funcions and the different created managers
     */
    void engine::cooldown() {
        // Destroy the window if it was created
        if (m_window) {
            m_window->destroy();
            delete m_window;
            m_window = nullptr;
            delete m_color_manager;
            m_color_manager = nullptr;
            delete m_texture_manager;
            m_texture_manager = nullptr;
        }

        // Delete audio manager when created
        if (m_music_manager) {
            delete m_music_manager;
            m_music_manager = nullptr;
        }

        if (m_sound_manager) {
            delete m_sound_manager;
            m_sound_manager = nullptr;
        }

        Mix_Quit();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();

        m_state = COOLEDDOWN;
    }

    /**
     * Init SDL with IMG, AUDIO and TTF
     */
    void engine::init_sdl() {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
            std::string error = SDL_GetError();
            throw std::runtime_error("Failed to initialize SDL: " + error);
        } else {
            // Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags)) {
                std::string error = IMG_GetError();
                throw std::runtime_error("Failed to initialize SDL image: " + error);
            }

            // Initialize ttf
            if(TTF_Init() == -1) {
                std::string error = TTF_GetError();
                throw std::runtime_error("Failed to initialize SDL ttf: " + error);
            }

            //Initialize SDL_mixer
            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
                std::string error = Mix_GetError();
                throw std::runtime_error("Failed to initialize SDL mixer: " + error);
            }

            m_sound_manager = new audio::sound_manager();
            m_music_manager = new audio::music_manager();
        }
    }

    /**
     * Get the texture_manager where images can be drawn
     *
     * @return graphics::texture_manager*
     */
    graphics::texture_manager *engine::get_texture_manager() const {
        return m_texture_manager;
    }

    /**
     * Get the color_manager where colors can be drawn
     *
     * @return graphics::color_manager
     */
    graphics::color_manager *engine::get_color_manager() const {
        return m_color_manager;
    }

    /**
     * Create the window when it's not already created
     */
    void engine::create_window() {
        // Create the window of it wasn't already created
        if (m_window == nullptr) {
            m_window = new window(m_config.win_config);
            m_window->create();

            // Set the color and texture manager
            m_color_manager = new graphics::color_manager(*m_window->get_renderer());

            m_texture_manager = new graphics::texture_manager(*m_window->get_renderer(), *m_window->get_surface());
        }
    }

    /**
     * Get the window
     *
     * @return window*
     */
    window *engine::get_window() const {
        return m_window;
    }

    /**
     * Get the sound_manager where sounds can be played
     *
     * @return audio::sound_manager*
     */
    audio::sound_manager *engine::get_sound_manager() const {
        return m_sound_manager;
    }

    /**
     * Get the music_manager where music can be played
     *
     * @return audio::music_manager*
     */
    audio::music_manager *engine::get_music_manager() const {
        return m_music_manager;
    }

    /**
     * Get the time elapsed since start/running the engine
     *
     * Note that the time_elapsed is independent of the number of times the window is refreshed and it is also independent
     * of SDL_GetTicks(). Because of this, time_elapsed will be the same on fast hardware as on slow hardware.
     *
     * @param interpolation - calculate the time with the given interpolation, default = 1 (no extra time)
     *
     * @return unsigned int - time in milliseconds
     */
    unsigned int engine::get_time_elapsed(float interpolation) const {
        if (m_state == RUNNING || m_state == PAUSED) {
            float game_ticks = m_game_ticks - get_paused_ticks() + interpolation - 1;
            return game_ticks * m_config.get_skip_ticks();
        }

        return 0;
    }

    /**
     * Get the current state of the engine
     *
     * @return state
     */
    state engine::get_state() const {
          return m_state;
    }

    /**
     * Get the number of game_ticks since starting/running the engine
     *
     * Note 1: when the gameloop is not started this will just return 0
     * Note 2: also game_ticks in the paused state are counted
     *
     * @return unsigned int
     */
    unsigned int engine::get_game_ticks() const {
        return m_game_ticks;
    }

    /**
     * Get the number of game_ticks that were in the paused state
     *
     * Note: when the current state is the paused state, also the game_ticks in the current pause are counted
     *
     * @return unsigned int
     */
    unsigned int engine::get_paused_ticks() const {
        if (m_state == PAUSED) {
            return m_paused_ticks + (m_game_ticks - m_ticks_when_paused);
        }

        return m_paused_ticks;
    }
}
