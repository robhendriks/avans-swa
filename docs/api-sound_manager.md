# Sound manager

## Load

```cpp
/**
 * Load a file in the sound manager
 *
 * @param file
 * @param id
 * @return bool - whether it's loaded successfully or not
 */
bool load(std::string file, std::string id);
```

```cpp
/**
 * Load a file in the sound manager if it's not already loaded
 *
 * @param file
 * @param id
 * @return bool - whether it's loaded successfully or not
 */
bool load_if(std::string file, std::string id);
```

```cpp
/**
 * Check if an id is loaded in the manager
 *
 * @param id
 * @return bool - whether it's loaded or not
 */
bool is_loaded(std::string id);
```

```cpp
/**
 * Unload the id in the manager. It's safe to call, also when the id is not loaded in the manager.
 * All the playing sounds with the given id are forced to stop
 *
 * @param id
 */
void unload(std::string id);
```

## Playing

```cpp
/**
 * Start playing a sound
 *
 * @param id - id of the sound to play, the id should be loaded.
 * @param when_finished - callback that will be called when the sound is finished/stops
 * @param volume - the volume of the sound: max = 128
 * @param fade_in - fade in time in milliseconds, use -1 for no fade in
 * @param loops - the number of loops for the sound, use -1 for a infinite number of loops
 * @return int - the channel where the sound is being played
 */
int play(std::string id, std::function<void()> when_finished = NULL, int volume = 128, int fade_in = -1, int loops = 0);
```

```cpp
/**
 * Start playing a sound if the sound is not already being played
 *
 * @param id - id of the sound to play, the id should be loaded.
 * @param count_paused - whether paused sounds are counting
 * @param when_finished - callback that will be called when the sound is finished/stops
 * @param volume - the volume of the sound: max = 128
 * @param fade_in - fade in time in milliseconds, use -1 for no fade in
 * @param loops - the number of loops for the sound, use -1 for a infinite number of loops
 * @return int - the channel where the sound is being played, if there are multiple channels where the sound
 * is being played the first channel will be returned
 */
int play_if(std::string id, bool count_paused = true, std::function<void()> when_finished = NULL, int volume = 128, int fade_in = -1, int loops = 0);
```

```cpp
/**
 * Pause the sound on the given channel, will only do something when there is a sound playing on the channel
 *
 * @param channel
 */
void pause(int channel);
```

```cpp
/**
 * Pause all channels/playing sounds with the given sound id
 *
 * @param id
 */
void pause_all(std::string id);
```

```cpp
/**
 * Pause all channels/playing sounds
 */
void pause_all();
```

```cpp
/**
 * Resume the sound ont the given channel, will only do something when there is a paused sound on the channel
 * @param channel
 */
void resume(int channel);
```

```cpp
/**
 * Resume all channels/playing sounds with the given sound id
 *
 * @param id
 */
void resume_all(std::string id);
```

```cpp
/**
 * Resume all the paused channels/playing sounds
 */
void resume_all();
```

```cpp
/**
 * Stop the sound on a channel
 *
 * @param channel
 * @param fade_out - fade out time in milliseconds, use -1 for no fade out
 */
void stop(int channel, int fade_out = -1);
```

```cpp
/**
 * Stop all channels/playing sounds with the given sound id
 *
 * @param id
 * @param fade_out - fade out time in milliseconds, use -1 for no fade out
 */
void stop_all(std::string id, int fade_out = -1);
```

```cpp
/**
 * Stop all channels/playing sounds
 *
 * @param fade_out - fade out time in milliseconds, use -1 for no fade out
 */
void stop_all(int fade_out = -1);
```

## Volume

```cpp
/**
 * Set the volume for a channel
 *
 * @param channel
 * @param volume - max 128
 */
void set_volume(int channel, int volume);
```

```cpp
/**
 * Set the volume for all the channels/playing sounds
 *
 * @param volume - max 128
 */
void set_volume_all(int volume);
```

```cpp
/**
 * Get the volume for a channel
 *
 * @param channel
 * @return int - the volume (0 - 128) or -1 when there is nothing played on the channel
 */
int get_volume(int channel) const;
```

```cpp
/**
 * Go back to the previous volume for the channel on the stack. If the stack size is less than 2,
 * nothing will happen.
 *
 * @param channel
 */
void pop_volume(int channel);
```

```cpp
/**
 * Get the volume stack for the channel
 *
 * @param channel
 * @return *std::stack<int> - the volumes that are used for the channel. If there is nothing played on the
 * channel a nullptr will be returned.
 */
std::stack<int> *get_volume_stack(int channel) const;
```

## Other

```cpp
/**
 * Get the playing channels for the id
 *
 * @param id
 * @param count_paused - whether paused sounds also should be returned
 * @return std::vector<int>
 */
std::vector<int> get_channels(std::string id, bool count_paused = true) const;
```

```cpp
/**
 * Get the currently playing sounds
 *
 * @return *std::map<int, std::tuple<std::string, sound::state, std::stack<int>>>
 *  int = channel
 *  std::string = sound id
 *  sound::state = PLAYING OR PAUSED
 *  std::stack<int> = volume stack
 */
std::map<int, std::tuple<std::string, sound::state, std::stack<int>>> *get_playing_sounds() const;
```
