//
// Created by robbie on 10-11-2016.
//

#include "gtest/gtest.h"
#include "../../../src/engine/audio/sound_manager.h"
#include "../../../src/engine/engine.h"

const std::string MUSIC_FILE = "data/sounds/pop.wav";

class sound_manager_fixture : public ::testing::Test {
public:
    engine::engine *engine1;
    engine::audio::sound_manager *manager;

    sound_manager_fixture() : Test() {
        // Start the engine, so the SDL functions are initialized
        engine::window_config w_config = {
            "test",
            engine::graphics::color4_t(0xFF6495ED)
        };
        engine::engine_config e_config = { w_config };
        engine1 = new engine::engine(e_config);
        engine1->warmup();

        manager = engine1->get_sound_manager();
    }

    virtual ~sound_manager_fixture() {
        engine1->cooldown();
        delete engine1;
    }
};

/**
 * Test loading file
 */
TEST_F(sound_manager_fixture, load) {
    EXPECT_FALSE(manager->is_loaded("pop"));
    EXPECT_TRUE(manager->load(MUSIC_FILE, "pop"));
    EXPECT_TRUE(manager->is_loaded("pop"));
}

/**
 * Test loading not existing file
 */
TEST_F(sound_manager_fixture, load_not_existing_file) {
    EXPECT_FALSE(manager->is_loaded("pop"));
    EXPECT_FALSE(manager->load("sounds/doesntexists.wav", "pop"));
    EXPECT_FALSE(manager->is_loaded("pop"));
}

/**
 * Test load_if
 */
TEST_F(sound_manager_fixture, load_if) {
    EXPECT_FALSE(manager->is_loaded("pop"));
    EXPECT_TRUE(manager->load_if(MUSIC_FILE, "pop"));
    EXPECT_TRUE(manager->is_loaded("pop"));
}

/**
 * Test unload
 */
TEST_F(sound_manager_fixture, unload) {
    EXPECT_TRUE(manager->load(MUSIC_FILE, "pop"));
    EXPECT_TRUE(manager->is_loaded("pop"));
    manager->unload("pop");
    EXPECT_FALSE(manager->is_loaded("pop"));
}

/**
 * Test unload while playing
 */
TEST_F(sound_manager_fixture, unload_while_playing) {
    EXPECT_TRUE(manager->load(MUSIC_FILE, "pop"));
    EXPECT_TRUE(manager->is_loaded("pop"));
    manager->play("pop");
    EXPECT_EQ(1, (int)manager->get_playing_sounds()->size());
    manager->unload("pop");
    EXPECT_EQ(0, (int)manager->get_playing_sounds()->size());
    EXPECT_FALSE(manager->is_loaded("pop"));
}
