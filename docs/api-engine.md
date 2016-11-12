# Engine

## Running

Before you use the engine you *must* always warmup the engine:

```cpp
/**
 * Warmup the engine, here SDL will be initialized and the window will be created. Also the different managers
 * like sound- and musicmanager will be created.
 */
void engine::warmup();
```

```cpp
/**
 * Start with running the engine, this will only have effect when the current state is WARMEDUP
 */
void engine::run();
```

```cpp
/**
 * Set the pause state, this will only have effect when the current state is RUNNING
 *
 * Note that pausing the engine has no effect on the gameloop, the gameloop will just continue running. The paused
 * state has really only effect on the time elapsed and paused ticks functions.
 */
void engine::pause();
```

```cpp
/**
 * Resume after a pause, will only have effect when the current state is PAUSED
 *
 * Like the pause() method this will not effect the gameloop.
 */
void engine::resume();
```

```cpp
/**
 * Stop the gameloop
 */
void engine::stop();
```

If the engine is warmed up and you stop using the engine, you *must* cool it down:

```cpp
/**
 * Cooldown the engine, this will delete/destroy the window, SDL funcions and the different created managers
 */
void engine::cooldown();
```

## Time
```cpp
/**
 * Get the number of game_ticks since starting/running the engine
 *
 * Note 1: when the gameloop is not started this will just return 0
 * Note 2: also game_ticks in the paused state are counted
 *
 * @return unsigned int
 */
unsigned int engine::get_game_ticks() const;
```

```cpp
/**
 * Get the number of game_ticks that were in the paused state
 *
 * Note: when the current state is the paused state, also the game_ticks in the current pause are counted
 *
 * @return unsigned int
 */
unsigned int engine::get_paused_ticks() const;
```

```cpp
/**
 * Get the time elapsed since start/running the engine
 *
 * Note that the time_elapsed is independent of the number of times the window is refreshed and it is also independent
 * of SDL_GetTicks(). Because of this, time_elapsed will be the same on fast hardware as on slow hardware.
 *
 * @return unsigned int - time in milliseconds
 */
unsigned int engine::get_time_elapsed() const;
```

## Other getters
```cpp
/**
 * Get the current state of the engine
 *
 * @return state
 */
state engine::get_state() const;
```

```cpp
/**
 * Get the texture_manager where images can be drawn
 *
 * @return graphics::texture_manager*
 */
graphics::texture_manager *engine::get_texture_manager() const;
```

```cpp
/**
 * Get the color_manager where colors can be drawn
 *
 * @return graphics::color_manager
 */
graphics::color_manager *engine::get_color_manager() const;
```

```cpp
/**
 * Get the sound_manager where sounds can be played
 *
 * @return audio::sound_manager*
 */
audio::sound_manager *engine::get_sound_manager() const;
```

```cpp
/**
 * Get the music_manager where music can be played
 *
 * @return audio::music_manager*
 */
audio::music_manager *engine::get_music_manager() const;
```

```cpp
/**
 * Get the window
 *
 * @return window*
 */
window *engine::get_window() const;
```
