//
// Created by robbie on 6-11-2016.
//

#include "music_manager.h"

namespace engine {
    namespace audio {

        music_manager::music_manager() {
            m_current_state = NOT_LOADED;
            m_current_song = nullptr;
        }

        bool music_manager::load(std::string file, std::string id) {
            Mix_Music *music = Mix_LoadMUS(file.c_str());
            if(music == nullptr) {
                return false;
            }

            m_songs[id] = music;

            return true;
        }

        void music_manager::unload(std::string id) {
            if (m_songs.find(id) != m_songs.end()) {
                if (m_current_song != nullptr && m_current_song->compare(id) == 0) {
                    stop();
                }

                Mix_FreeMusic(m_songs[id]);
                m_songs.erase(id);
            }
        }

        void music_manager::play(std::string id) {
            if (m_current_state != NOT_LOADED) {
                // Stop the music
                stop();
            }

            // Play the song
            if (m_songs.find(id) != m_songs.end()) {
                Mix_PlayMusic(m_songs[id], -1);
                m_current_song = new std::string(id);
                m_current_state = PLAYING;
            }
        }

        void music_manager::stop() {
            if (m_current_state != NOT_LOADED) {
                Mix_HaltMusic();
                m_current_state = NOT_LOADED;
                delete m_current_song;
                m_current_song = nullptr;
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

        music_state music_manager::get_state(std::string id) {
            if (m_current_song != nullptr && m_current_song->compare(id) == 0) {
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
