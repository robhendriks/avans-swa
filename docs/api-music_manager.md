# Music manager

## Load

Load a music file

```cpp
/**
 * Load a file in the manager
 *
 * @param file
 * @param id
 * @return bool - whether it's loaded successfully or not
*/
bool load(std::string file, std::string id);
```

Load only when the id is not already loaded

```cpp
/**
 * Load a file in the manager if it's not already loaded
 *
 * @param file
 * @param id
 * @return bool - whether it's loaded successfully or not
 */
bool load_if(std::string file, std::string id);
```

Check if the id is already loaded

```cpp
/**
 * Check if an id is loaded in the manager
 * 
 * @param id 
 * @return bool - whether it's loaded or not
 */
bool is_loaded(std::string id);
```

## Unload
The unload function will force a stop when the id is currently playing. 
```cpp
/**
 * Unload the id in the manager. It's safe to call, also when the id is not loaded in the manager.
 * When the current playing song is unloaded this function will force a stop.
 *
 * @param id
 */
void unload(std::string id);
```

## Playing

```cpp
/**
 * Start playing music, if there is already some music playing this will stops automatically
 *
 * @param id - id of the music to play, the id should be loaded.
 * @param when_finished_callback - callback that will be called when the music is finished/stops
 * @param volume - the volume of the music: max = 128
 * @param fade_in - fade in time in milliseconds, use -1 for no fade in
 * @param loops - the number of loops for the music, use -1 for a infinite number of loops
 */
void play(std::string id, std::function<void()> when_finished = NULL, int volume = 128, int fade_in = -1, int loops = -1);
```

```cpp
/**
 * Stops the currently playing (or paused) music
 *
 * @param fade_out - fade out time in milliseconds, use -1 for no fade out
 */
void stop(int fade_out = -1);
```
```cpp
/**
 * Pause the music, will only do something when the current state is PLAYNING
 */
void pause();
```

```cpp
/**
 * Resume the paused music, will only do something when the current state is PAUSED
 */
void resume();
```

## Volume

```cpp
/**
 * Set the volume for the current playing song
 *
 * @param volume - max 128
 */
void set_volume(int volume);
```

```cpp
/**
 * Get the current volume
 *
 * @return int - the volume (0 - 128) or -1 when there is no music playing at the moment
 */
int get_volume();
```

```cpp
/**
 * Go back to the previous volume on the stack. If the stack size is less than 2, nothing will happen.
 */
void pop_volume();
```

```cpp
/**
 * Get the volume stack of the currently playing music
 *
 * @return &std::stack<int> - the volumes that are used for the playing music. If there is no playing music
 * an empty stack will be returned.
 */
std::stack<int> &get_volume_stack();
```

## State
```cpp
/**
 * Get the current playing id
 *
 * @return string - the current playing id or an empty string when there is nothing playing at the moment
 */
std::string get_current_playing_id();
```

```cpp
/**
 * Get the state for the id
 *
 * @param id
 * @return music::state - PLAYING, PAUSED OR NOT_PLAYING
 */
music::state get_state(std::string id);
```
