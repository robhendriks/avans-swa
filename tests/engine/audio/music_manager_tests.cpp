//
// Created by robbie on 10-11-2016.
//

#include "gtest/gtest.h"
#include "../../../src/engine/audio/music_manager.h"
#include "../../../src/engine/engine.h"

const std::string MUSIC_FILE = "data/sounds/pop.wav";

class music_manager_fixture : public ::testing::Test {
public:
    engine::engine *engine1;
    engine::window_config *w_config;
    engine::engine_config *e_config;

    engine::audio::music_manager *manager;

    music_manager_fixture() : Test() {
        // Start the engine, so the SDL functions are initialized
        w_config = new engine::window_config("test", engine::graphics::color4_t(0xFF6495ED));
        e_config = new engine::engine_config(*w_config);

        engine1 = new engine::engine(*e_config);
        engine1->warmup();

        manager = engine1->get_music_manager();
    }

    virtual ~music_manager_fixture() {
        engine1->cooldown();
        delete engine1;
        delete w_config;
        delete e_config;
    }
};

/**
 * Test loading file
 */
TEST_F(music_manager_fixture, load) {
    EXPECT_FALSE(manager->is_loaded("pop"));
    EXPECT_TRUE(manager->load(MUSIC_FILE, "pop"));
    EXPECT_TRUE(manager->is_loaded("pop"));
}

/**
 * Test loading not existing file
 */
TEST_F(music_manager_fixture, load_not_existing_file) {
    EXPECT_FALSE(manager->is_loaded("pop"));
    EXPECT_FALSE(manager->load("sounds/doesntexists.wav", "pop"));
    EXPECT_FALSE(manager->is_loaded("pop"));
}

/**
 * Test load_if
 */
TEST_F(music_manager_fixture, load_if) {
    EXPECT_FALSE(manager->is_loaded("pop"));
    EXPECT_TRUE(manager->load_if(MUSIC_FILE, "pop"));
    EXPECT_TRUE(manager->is_loaded("pop"));
}

/**
 * Test unload
 */
TEST_F(music_manager_fixture, unload) {
    EXPECT_TRUE(manager->load(MUSIC_FILE, "pop"));
    EXPECT_TRUE(manager->is_loaded("pop"));
    manager->unload("pop");
    EXPECT_FALSE(manager->is_loaded("pop"));
}

/**
 * Test unload while playing
 */
TEST_F(music_manager_fixture, unload_while_playing) {
    EXPECT_TRUE(manager->load(MUSIC_FILE, "pop"));
    EXPECT_TRUE(manager->is_loaded("pop"));
    manager->play("pop");
    EXPECT_EQ(engine::audio::music::state::PLAYING, manager->get_state());
    manager->unload("pop");
    EXPECT_EQ(engine::audio::music::state::NOT_PLAYING, manager->get_state());
    EXPECT_FALSE(manager->is_loaded("pop"));
}

/**
 * Test stop
 */
TEST_F(music_manager_fixture, stop) {
    EXPECT_TRUE(manager->load(MUSIC_FILE, "pop"));
    EXPECT_TRUE(manager->is_loaded("pop"));
    EXPECT_EQ(engine::audio::music::state::NOT_PLAYING, manager->get_state());
    manager->play("pop");
    EXPECT_EQ(engine::audio::music::state::PLAYING, manager->get_state());
    EXPECT_EQ("pop", manager->get_current_playing_id());
    manager->stop();
    EXPECT_EQ(engine::audio::music::state::NOT_PLAYING, manager->get_state());
    EXPECT_EQ("", manager->get_current_playing_id());
}

/**
 * Test pause and resume
 */
TEST_F(music_manager_fixture, pause_and_resume) {
    EXPECT_TRUE(manager->load(MUSIC_FILE, "pop"));
    manager->play("pop");
    EXPECT_EQ(engine::audio::music::state::PLAYING, manager->get_state());
    manager->pause();
    EXPECT_EQ(engine::audio::music::state::PAUSED, manager->get_state());
    manager->resume();
    EXPECT_EQ(engine::audio::music::state::PLAYING, manager->get_state());
}

/**
 * Test pause when not playing
 */
TEST_F(music_manager_fixture, pause_when_not_playing) {
    EXPECT_TRUE(manager->load(MUSIC_FILE, "pop"));
    EXPECT_EQ(engine::audio::music::state::NOT_PLAYING, manager->get_state());
    manager->pause();
    EXPECT_EQ(engine::audio::music::state::NOT_PLAYING, manager->get_state());
}

/**
 * Test resume when not paused
 */
TEST_F(music_manager_fixture, resume_when_not_paused) {
    EXPECT_TRUE(manager->load(MUSIC_FILE, "pop"));
    manager->play("pop");
    EXPECT_EQ(engine::audio::music::state::PLAYING, manager->get_state());
    manager->resume();
    EXPECT_EQ(engine::audio::music::state::PLAYING, manager->get_state());
}

/**
 * Test get and set volume
 */
TEST_F(music_manager_fixture, get_and_set_volume) {
    EXPECT_TRUE(manager->load(MUSIC_FILE, "pop"));
    manager->play("pop", NULL, 128);
    EXPECT_EQ(128, manager->get_volume());
    manager->set_volume(68);
    EXPECT_EQ(68, manager->get_volume());
}

/**
 * Get and set volume when nothing is being played
 */
TEST_F(music_manager_fixture, get_and_set_volume_when_nothing_is_playing) {
    EXPECT_EQ(-1, manager->get_volume());
    manager->set_volume(68);
    EXPECT_EQ(-1, manager->get_volume());
}

/**
 * Test volume stack
 */
TEST_F(music_manager_fixture, volume_stack) {
    EXPECT_EQ(0, (int)manager->get_volume_stack().size());
    manager->set_volume(68);
    EXPECT_EQ(0, (int)manager->get_volume_stack().size());
    EXPECT_TRUE(manager->load(MUSIC_FILE, "pop"));
    manager->play("pop", NULL, 128);
    EXPECT_EQ(1, (int)manager->get_volume_stack().size());
    EXPECT_EQ(128, manager->get_volume());
    manager->pop_volume();
    EXPECT_EQ(1, (int)manager->get_volume_stack().size());
    manager->set_volume(65);
    EXPECT_EQ(2, (int)manager->get_volume_stack().size());
    EXPECT_EQ(65, manager->get_volume());
    manager->set_volume(40);
    EXPECT_EQ(3, (int)manager->get_volume_stack().size());
    EXPECT_EQ(40, manager->get_volume());
    manager->pop_volume();
    EXPECT_EQ(2, (int)manager->get_volume_stack().size());
    EXPECT_EQ(65, manager->get_volume());
    manager->pop_volume();
    EXPECT_EQ(1, (int)manager->get_volume_stack().size());
    EXPECT_EQ(128, manager->get_volume());
}

/**
 * Test callback
 */
TEST_F(music_manager_fixture, finished_callback) {
    EXPECT_TRUE(manager->load(MUSIC_FILE, "pop"));
    bool callback_called = false;
    manager->play("pop", [&callback_called]() {
       callback_called = true;
    });
    EXPECT_FALSE(callback_called);
    manager->stop();
    EXPECT_TRUE(callback_called);
}
