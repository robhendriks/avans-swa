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
    engine::window_config *w_config;
    engine::engine_config *e_config;

    engine::audio::sound_manager *manager;

    sound_manager_fixture() : Test() {
        // Start the engine, so the SDL functions are initialized
        w_config = new engine::window_config("test", engine::graphics::color4_t(0xFF6495ED));
        e_config = new engine::engine_config(*w_config);

        engine1 = new engine::engine(*e_config);
        engine1->warmup();

        manager = engine1->get_sound_manager();
    }

    virtual ~sound_manager_fixture() {
        engine1->cooldown();
        delete engine1;
        delete w_config;
        delete e_config;
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

/**
 * Test play_if when playing
 */
TEST_F(sound_manager_fixture, play_if_when_playing) {
    EXPECT_TRUE(manager->load(MUSIC_FILE, "pop"));
    manager->play("pop");
    EXPECT_EQ(1, (int)manager->get_playing_sounds()->size());
    manager->play_if("pop");
    EXPECT_EQ(1, (int)manager->get_playing_sounds()->size());
}

/**
 * Test play_if when not playing
 */
TEST_F(sound_manager_fixture, play_if_when_not_playing) {
    EXPECT_TRUE(manager->load(MUSIC_FILE, "pop"));
    EXPECT_TRUE(manager->load(MUSIC_FILE, "pop2"));
    manager->play("pop");
    EXPECT_EQ(1, (int)manager->get_playing_sounds()->size());
    manager->play_if("pop2");
    EXPECT_EQ(2, (int)manager->get_playing_sounds()->size());
}

/**
 * Test play, pause, resume and stop
 */
TEST_F(sound_manager_fixture, play_pause_resume_stop) {
    EXPECT_TRUE(manager->load(MUSIC_FILE, "pop"));
    int channel = manager->play("pop");
    EXPECT_EQ(1, (int)manager->get_playing_sounds()->size());
    manager->pause(channel);
    EXPECT_EQ(1, (int)manager->get_channels("pop", true).size());
    EXPECT_EQ(0, (int)manager->get_channels("pop", false).size());
    manager->resume(channel);
    EXPECT_EQ(1, (int)manager->get_channels("pop", true).size());
    EXPECT_EQ(1, (int)manager->get_channels("pop", false).size());
    manager->stop(channel);
    EXPECT_EQ(0, (int)manager->get_playing_sounds()->size());
    EXPECT_EQ(0, (int)manager->get_channels("pop", true).size());
    EXPECT_EQ(0, (int)manager->get_channels("pop", false).size());
}

/**
 * Test pause, resume and stop all
 */
TEST_F(sound_manager_fixture, pause_resume_and_stop_all) {
    EXPECT_TRUE(manager->load(MUSIC_FILE, "pop"));
    EXPECT_TRUE(manager->load(MUSIC_FILE, "pop2"));
    int channel1 = manager->play("pop");
    manager->play("pop");
    manager->play("pop2");
    EXPECT_EQ(3, (int)manager->get_playing_sounds()->size());
    manager->pause(channel1);
    EXPECT_EQ(1, (int)manager->get_channels("pop", false).size());
    EXPECT_EQ(1, (int)manager->get_channels("pop2", false).size());
    manager->pause_all();
    EXPECT_EQ(0, (int)manager->get_channels("pop", false).size());
    EXPECT_EQ(0, (int)manager->get_channels("pop2", false).size());
    manager->resume_all();
    EXPECT_EQ(2, (int)manager->get_channels("pop", false).size());
    EXPECT_EQ(1, (int)manager->get_channels("pop2", false).size());
    manager->pause_all("pop");
    EXPECT_EQ(0, (int)manager->get_channels("pop", false).size());
    EXPECT_EQ(1, (int)manager->get_channels("pop2", false).size());
    manager->pause_all();
    EXPECT_EQ(0, (int)manager->get_channels("pop", false).size());
    EXPECT_EQ(0, (int)manager->get_channels("pop2", false).size());
    manager->resume_all("pop2");
    EXPECT_EQ(0, (int)manager->get_channels("pop", false).size());
    EXPECT_EQ(1, (int)manager->get_channels("pop2", false).size());
    manager->stop_all("pop2");
    EXPECT_EQ(0, (int)manager->get_channels("pop", false).size());
    EXPECT_EQ(0, (int)manager->get_channels("pop2", false).size());
    EXPECT_EQ(2, (int)manager->get_channels("pop", true).size());
    manager->stop_all();
    EXPECT_EQ(0, (int)manager->get_channels("pop2", false).size());
    EXPECT_EQ(0, (int)manager->get_channels("pop", true).size());
}

/**
 * Test callback
 */
TEST_F(sound_manager_fixture, finished_callback) {
    EXPECT_TRUE(manager->load(MUSIC_FILE, "pop"));
    bool callback_called = false;
    int channel = manager->play("pop", [&callback_called]() {
        callback_called = true;
    });
    EXPECT_FALSE(callback_called);
    manager->stop(channel);
    EXPECT_TRUE(callback_called);
}

/**
 * Test get and set volume
 */
TEST_F(sound_manager_fixture, get_and_set_volume) {
    EXPECT_TRUE(manager->load(MUSIC_FILE, "pop"));
    int channel = manager->play("pop", NULL, 128);
    EXPECT_EQ(128, manager->get_volume(channel));
    manager->set_volume(channel, 68);
    EXPECT_EQ(68, manager->get_volume(channel));
}

/**
 * Test set volume all
 */
TEST_F(sound_manager_fixture, set_all_volume) {
    EXPECT_TRUE(manager->load(MUSIC_FILE, "pop"));
    int channel1 = manager->play("pop", NULL, 28);
    int channel2 = manager->play("pop", NULL, 128);
    EXPECT_EQ(28, manager->get_volume(channel1));
    EXPECT_EQ(128, manager->get_volume(channel2));
    manager->set_volume_all(20);
    EXPECT_EQ(20, manager->get_volume(channel1));
    EXPECT_EQ(20, manager->get_volume(channel2));
}

/**
 * Test volume stack
 */
TEST_F(sound_manager_fixture, volume_stack) {
    EXPECT_TRUE(manager->load(MUSIC_FILE, "pop"));
    int channel = manager->play("pop", NULL, 28);
    EXPECT_EQ(1, (int)manager->get_volume_stack(channel)->size());
    EXPECT_EQ(28, manager->get_volume(channel));
    manager->pop_volume(channel);
    EXPECT_EQ(1, (int)manager->get_volume_stack(channel)->size());
    EXPECT_EQ(28, manager->get_volume(channel));
    manager->set_volume(channel, 68);
    EXPECT_EQ(2, (int)manager->get_volume_stack(channel)->size());
    EXPECT_EQ(68, manager->get_volume(channel));
    manager->pop_volume(channel);
    EXPECT_EQ(1, (int)manager->get_volume_stack(channel)->size());
    EXPECT_EQ(28, manager->get_volume(channel));
    manager->set_volume(channel, 65);
    EXPECT_EQ(2, (int)manager->get_volume_stack(channel)->size());
    EXPECT_EQ(65, manager->get_volume(channel));
    manager->set_volume(channel, 40);
    EXPECT_EQ(3, (int)manager->get_volume_stack(channel)->size());
    EXPECT_EQ(40, manager->get_volume(channel));
    manager->pop_volume(channel);
    EXPECT_EQ(2, (int)manager->get_volume_stack(channel)->size());
    EXPECT_EQ(65, manager->get_volume(channel));
    manager->pop_volume(channel);
    EXPECT_EQ(1, (int)manager->get_volume_stack(channel)->size());
    EXPECT_EQ(28, manager->get_volume(channel));
}
