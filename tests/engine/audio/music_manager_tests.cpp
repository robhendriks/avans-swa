//
// Created by robbie on 10-11-2016.
//

#include "gtest/gtest.h"
#include "../../../src/engine/audio/music_manager.h"
#include "../../../src/engine/engine.h"

const std::string MUSIC_FILE = "data/sounds/pop.wav";

class music_manager_fixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    engine::engine *engine1;
    engine::audio::music_manager *manager;

    music_manager_fixture() : Test() {
        // Start the engine, so the SDL functions are initialized
        engine::window_config w_config = {
           "test",
            engine::graphics::color4_t(0xFF6495ED)
        };
        engine::engine_config e_config = { w_config };
        engine1 = new engine::engine(e_config);
        engine1->warmup();

        manager = engine1->get_music_manager();
    }

    virtual ~music_manager_fixture() {
        delete manager;
        delete engine1;
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
    manager->play("pop");
    EXPECT_EQ(engine::audio::music::state::PLAYING, manager->get_state());
    EXPECT_EQ("pop", manager->get_current_playing_id());
    manager->stop();
    EXPECT_EQ(engine::audio::music::state::NOT_PLAYING, manager->get_state());
    EXPECT_EQ("", manager->get_current_playing_id());
}
