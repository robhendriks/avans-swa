//
// Created by robbie on 6-11-2016.
//

#include "music_manager.h"

namespace engine {
    namespace audio {

        std::function<void()> music_manager::when_finished = NULL;

        music_manager::music_manager() {
            m_current_state = NOT_LOADED;
            m_current_song = "";
            m_volume = -1;
            m_init_volume = -1;

            Mix_HookMusicFinished(music_finished);
        }

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

        void music_manager::unload(std::string id) {
            if (m_songs.find(id) != m_songs.end()) {
                if (m_current_song.compare(id) == 0) {
                    stop();
                }

                Mix_FreeMusic(m_songs[id]);
                m_songs.erase(id);
            }
        }

        void music_manager::music_finished() {
            if (music_manager::when_finished != NULL) {
                music_manager::when_finished();
                music_manager::when_finished = NULL;
            }
        }

        void music_manager::play(std::string id, std::function<void()> when_finished, int volume, int loops) {
            if (m_current_state != NOT_LOADED) {
                // Stop the music
                stop();
            }

            // Play the song
            if (m_songs.find(id) != m_songs.end()) {
                // Set finished callback
                music_manager::when_finished = when_finished;
                m_init_volume = volume;
                set_volume(volume);
                Mix_PlayMusic(m_songs[id], loops);
                m_current_song = id;
                m_current_state = PLAYING;
            }
        }

        void music_manager::set_volume(int volume) {
            if (m_current_state != NOT_LOADED) {
                m_volume = volume;
                Mix_VolumeMusic(volume);
            }
        }

        int music_manager::get_current_volume() const {
            return m_volume;
        }

        int music_manager::get_init_volume() const {
            return m_init_volume;
        }

        void music_manager::stop() {
            if (m_current_state != NOT_LOADED) {
                Mix_HaltMusic();
                m_current_state = NOT_LOADED;
                m_current_song = "";
                m_volume = -1;
                m_init_volume = -1;
            }
        }

        void music_manager::pause() {
            if (m_current_state == PLAYING) {
                Mix_PauseMusic();
                m_current_state = PAUSED;
            }
        }

        void music_manager::resume() {
            if (m_current_state == PAUSED) {
                Mix_ResumeMusic();
                m_current_state = PLAYING;
            }
        }

        std::string music_manager::get_current_song() const {
            if (m_current_state != NOT_LOADED) {
                return m_current_song;
            }

            return "";
        }

        music_state music_manager::get_state(std::string id) const {
            if (id == "" || m_current_song.compare(id) == 0) {
                return m_current_state;
            }

            if (m_songs.find(id) != m_songs.end()) {
                return LOADED;
            }

            return NOT_LOADED;
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
