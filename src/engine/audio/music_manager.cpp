//
// Created by robbie on 6-11-2016.
//

#include "music_manager.h"

namespace engine {
    namespace audio {

        std::stack<int> music_manager::m_volume_stack = std::stack<int>();
        std::string music_manager::m_current_song = "";
        music::state music_manager::m_current_state = music::NOT_PLAYING;
        std::function<void()> music_manager::when_finished = NULL;

        /**
         * Load a file in the manager
         *
         * @param file
         * @param id
         * @return bool - whether it's loaded successfully or not
         */
        bool music_manager::load(std::string file, std::string id) {
            if (id == "") {
                // Id cannot be empty
                return false;
            }

            Mix_Music *music = Mix_LoadMUS(file.c_str());
            if(music == nullptr) {
                return false;
            }

            m_songs[id] = music;

            return true;
        }

        /**
         * Load a file in the manager if it's not already loaded
         *
         * @param file
         * @param id
         * @return bool - whether it's loaded successfully or not
         */
        bool music_manager::load_if(std::string file, std::string id) {
            if (!is_loaded(id)) {
                return load(file, id);
            }

            return true;
        }

        /**
         * Check if an id is loaded in the manager
         *
         * @param id
         * @return bool - whether it's loaded or not
         */
        bool music_manager::is_loaded(std::string id) {
            return m_songs.find(id) != m_songs.end();
        }

        /**
         * Unload the id in the manager. It's safe to call, also when the id is not loaded in the manager.
         * When the current playing song is unloaded this function will force a stop.
         *
         * @param id
         */
        void music_manager::unload(std::string id) {
            if (is_loaded(id)) {
                if (m_current_song.compare(id) == 0) {
                    stop();
                }

                Mix_FreeMusic(m_songs[id]);
                m_songs.erase(id);
            }
        }

        /**
         * Called when the music is finished
         */
        void music_manager::music_finished() {
            if (when_finished != NULL) {
                when_finished();
                when_finished = NULL;
            }
        }

        /**
         * Start playing music, if there is already some music playing this will stops automatically
         *
         * @param id - id of the music to play, the id should be loaded.
         * @param when_finished_callback - callback that will be called when the music is finished/stops
         * @param volume - the volume of the music: max = 128
         * @param loops - the number of loops for the music, use -1 for a infinite number of loops
         */
        void music_manager::play(std::string id, std::function<void()> when_finished_callback, int volume, int loops) {
            if (m_current_state != music::NOT_PLAYING) {
                // Stop the music
                stop();
            }

            // Play the song
            if (is_loaded(id)) {
                // Set finished callback
                Mix_HookMusicFinished(music_finished);
                when_finished = when_finished_callback;

                // Set state
                m_current_state = music::PLAYING;

                // Set volume
                set_volume(volume);

                // Play
                Mix_PlayMusic(m_songs[id], loops);
                m_current_song = id;
            }
        }

        /**
         * Set the volume for the current playing song
         *
         * @param volume - max 128
         */
        void music_manager::set_volume(int volume) {
            if (m_current_state != music::NOT_PLAYING) {
                m_volume_stack.push(volume);
                Mix_VolumeMusic(volume);
            }
        }

        /**
         * Get the current volume
         *
         * @return int - the volume (0 - 128) or -1 when there is no music playing at the moment
         */
        int music_manager::get_volume() {
            if (m_volume_stack.size() > 0) {
                return m_volume_stack.top();
            }

            return -1;
        }

        /**
         * Go back to the previous volume on the stack. If the stack size is less than 2, nothing will happen.
         */
        void music_manager::pop_volume() {
            if (m_volume_stack.size() > 1) {
                // Remove the top/current volume
                m_volume_stack.pop();
                // Set the volume to the previous volume
                set_volume(m_volume_stack.top());
                // Pop again because set_volume will push again
                m_volume_stack.pop();
            }
        }

        /**
         * Get the volume stack of the currently playing music
         *
         * @return &std::stack<int> - the volumes that are used for the playing music. If there is no playing music
         * an empty stack will be returned.
         */
        std::stack<int> &music_manager::get_volume_stack() {
            return m_volume_stack;
        }

        /**
         * Stops the currently playing (or paused) music
         */
        void music_manager::stop() {
            if (m_current_state != music::NOT_PLAYING) {
                Mix_HaltMusic();
                m_current_state = music::NOT_PLAYING;
                m_current_song = "";
                // Just a new stack, instead of clearing in a while loop (while != empty { pop; })
                m_volume_stack = std::stack<int>();
            }
        }

        /**
         * Pause the music, will only do something when the current state is PLAYNING
         */
        void music_manager::pause() {
            if (m_current_state == music::PLAYING) {
                Mix_PauseMusic();
                m_current_state = music::PAUSED;
            }
        }

        /**
         * Resume the paused music, will only do something when the current state is PAUSED
         */
        void music_manager::resume() {
            if (m_current_state == music::PAUSED) {
                Mix_ResumeMusic();
                m_current_state = music::PLAYING;
            }
        }

        /**
         * Get the current playing id
         *
         * @return string - the current playing id or an empty string when there is nothing playing at the moment
         */
        std::string music_manager::get_current_playing_id() {
            if (m_current_state != music::NOT_PLAYING) {
                return m_current_song;
            }

            return "";
        }

        /**
         * Get the state for the id
         *
         * @param id
         * @return music::state - PLAYING, PAUSED OR NOT_PLAYING
         */
        music::state music_manager::get_state(std::string id) {
            if (id == "" || m_current_song.compare(id) == 0) {
                return m_current_state;
            }

            return music::NOT_PLAYING;
        }

        music_manager::~music_manager() {
            stop();

            // Unload all songs, iterator loop because the m_songs will be changed inside
            for (auto it = m_songs.begin(); it != m_songs.end();) {
                unload(it->first);
                it = m_songs.begin();
            }
        }
    }
}
