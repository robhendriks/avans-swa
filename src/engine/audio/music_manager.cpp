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

        bool music_manager::load_if(std::string file, std::string id) {
            if (!is_loaded(id)) {
                return load(file, id);
            }

            return true;
        }

        bool music_manager::is_loaded(std::string id) {
            return m_songs.find(id) != m_songs.end();
        }

        void music_manager::unload(std::string id) {
            if (is_loaded(id)) {
                if (m_current_song.compare(id) == 0) {
                    stop();
                }

                Mix_FreeMusic(m_songs[id]);
                m_songs.erase(id);
            }
        }

        void music_manager::music_finished() {
            if (when_finished != NULL) {
                when_finished();
                when_finished = NULL;
            }
        }

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

        void music_manager::set_volume(int volume) {
            if (m_current_state != music::NOT_PLAYING) {
                m_volume_stack.push(volume);
                Mix_VolumeMusic(volume);
            }
        }

        int music_manager::get_volume() {
            if (m_volume_stack.size() > 0) {
                return m_volume_stack.top();
            }

            return -1;
        }

        void music_manager::pop_volume() {
            // Remove the top/current volume
            m_volume_stack.pop();
            // Set the volume to the previous volume
            set_volume(m_volume_stack.top());
            // Pop again because set_volume will push again
            m_volume_stack.pop();
        }

        std::stack<int> &music_manager::get_volume_stack() {
            return m_volume_stack;
        }

        void music_manager::stop() {
            if (m_current_state != music::NOT_PLAYING) {
                Mix_HaltMusic();
                m_current_state = music::NOT_PLAYING;
                m_current_song = "";
                // Just a new stack, instead of clearing in a while loop (while != empty { pop; })
                m_volume_stack = std::stack<int>();
            }
        }

        void music_manager::pause() {
            if (m_current_state == music::PLAYING) {
                Mix_PauseMusic();
                m_current_state = music::PAUSED;
            }
        }

        void music_manager::resume() {
            if (m_current_state == music::PAUSED) {
                Mix_ResumeMusic();
                m_current_state = music::PLAYING;
            }
        }

        std::string music_manager::get_current_playing_id() {
            if (m_current_state != music::NOT_PLAYING) {
                return m_current_song;
            }

            return "";
        }

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
