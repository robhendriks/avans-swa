//
// Created by robbie on 11-11-2016.
//

#include "gtest/gtest.h"
#include "../../../src/engine/engine.h"
#include "../../src/engine/eventbus/eventbus.h"
#include "../../src/engine/events/window_cleared.h"

class engine_fixture : public ::testing::Test {
public:
    engine::engine *engine1;
    engine::window_config *w_config;
    engine::engine_config *e_config;

    engine_fixture() : Test() {
        // Start the engine, so the SDL functions are initialized
        w_config = new engine::window_config("test", engine::graphics::color4_t(0xFF6495ED));
        e_config = new engine::engine_config(*w_config);

        engine1 = new engine::engine(*e_config);
    }

    virtual ~engine_fixture() {
        delete engine1;
        delete w_config;
        delete e_config;
    }
};

/**
 * Test state transitions
 */
TEST_F(engine_fixture, state_transitions) {
    // Check we cannot run, pause or resume in the CREATED state
    EXPECT_EQ(engine::state::CREATED, engine1->get_state());
    engine1->run();
    EXPECT_EQ(engine::state::CREATED, engine1->get_state());
    engine1->pause();
    EXPECT_EQ(engine::state::CREATED, engine1->get_state());
    engine1->resume();
    EXPECT_EQ(engine::state::CREATED, engine1->get_state());

    // Warmup engine
    engine1->warmup();
    EXPECT_EQ(engine::state::WARMEDUP, engine1->get_state());

    // We still cannot pause or resume
    engine1->pause();
    EXPECT_EQ(engine::state::WARMEDUP, engine1->get_state());
    engine1->resume();
    EXPECT_EQ(engine::state::WARMEDUP, engine1->get_state());

    // Subscribe to the window callback so we can do something when the engine is running
    std::function<void(engine::events::window_cleared &event)> callback = [&](engine::events::window_cleared &event) {
        EXPECT_EQ(engine::state::RUNNING, engine1->get_state());

        // Now we should be able to pause
        engine1->pause();
        EXPECT_EQ(engine::state::PAUSED, engine1->get_state());

        // And resume
        engine1->resume();
        EXPECT_EQ(engine::state::RUNNING, engine1->get_state());

        // Stop
        engine1->stop();
        EXPECT_EQ(engine::state::STOPPED, engine1->get_state());
    };

    engine::eventbus::eventbus::get_instance().subscribe("engine_stop", callback);

    // We can run
    engine1->run();
    // Here the callback will be called

    // Back from the callback
    engine::eventbus::eventbus::get_instance().unsubscribe("engine_stop");

    // Cooldown
    engine1->cooldown();
    EXPECT_EQ(engine::state::COOLEDDOWN, engine1->get_state());
}

/**
 * Test time elapsed
 */
TEST_F(engine_fixture, time_elapsed) {
    EXPECT_EQ(0, (int)engine1->get_time_elapsed());
    engine1->warmup();
    // Should still be 0 milliseconds elapsed
    EXPECT_EQ(0, (int)engine1->get_time_elapsed());

    // Subscribe to the window callback so we can do something when the engine is running
    unsigned int elapsed_time_before_pause = 0;
    int prev_game_ticks = -1;
    std::function<void(engine::events::window_cleared &event)> callback = [&](engine::events::window_cleared &event) {
        if (prev_game_ticks != (int)engine1->get_game_ticks()) {
            if (engine1->get_game_ticks() == 0) {
                // On the first window_cleared event the time_elapsed should be still 0
                EXPECT_EQ(0, (int)engine1->get_time_elapsed());
            } else if (engine1->get_game_ticks() == 1) {
                // At one game tick the time elapsed should be get_skip_ticks
                EXPECT_EQ(e_config->get_skip_ticks(), (int)engine1->get_time_elapsed());
            } else if (engine1->get_game_ticks() == 2) {
                // Pause the game
                elapsed_time_before_pause = engine1->get_time_elapsed();
                engine1->pause();
            } else if (engine1->get_game_ticks() == 4) {
                EXPECT_EQ(2, (int)engine1->get_paused_ticks());
                // The elapsed time should still be the same
                EXPECT_EQ(elapsed_time_before_pause, engine1->get_time_elapsed());

                engine1->resume();
            } else if (engine1->get_game_ticks() == 5) {
                // The elapsed time should now be one tick further
                EXPECT_EQ(elapsed_time_before_pause + e_config->get_skip_ticks(), engine1->get_time_elapsed());

                engine1->stop();
            }

            prev_game_ticks = engine1->get_game_ticks();
        }
    };

    engine::eventbus::eventbus::get_instance().subscribe("engine_stop", callback);

    // Run
    engine1->run();
    // Here the callback will be called

    // Back from the callback
    engine::eventbus::eventbus::get_instance().unsubscribe("engine_stop");

    // Cooldown the engine
    engine1->cooldown();
}
