# Eventbus

```cpp
/**
 * Get the instance of the eventbus
 *
 * @return eventbus
 */
static eventbus &get_instance();
```

## (Un)Subscribe

```cpp
/**
 * Add a (class)subscriber
 *
 * @param subscriber1
 */
template<class T>
void subscribe(subscriber<T> *subscriber1);
```

```cpp
/**
 * Unsubscribe a (class)subscriber
 *
 * @param subscriber1
 */
template<class T>
void unsubscribe(subscriber<T> *subscriber1);
```

```cpp
/**
 * Add a callback as subscriber
 *
 * NOTE: When calling this with a lambda function you must specify the type for conversion e.g.
 * This will work:
 *      std::function<void(TestEvent &)> callback = [&](TestEvent &event) {};
 *
 *      subscribe("name", callback);
 *
 *  But this will not:
 *      auto callback = [&](TestEvent &event) {};
 *
 *      subscribe("name", callback);
 *
 *  And this will also fail:
 *
 *      subscribe("name", [&](TestEvent &event) {});
 *
 * @param name
 * @param callback
 */
template<class T>
void subscribe(std::string name, std::function<void(T)> callback);
```

```cpp
/**
 * Unsubscribe a callback subscriber
 *
 * @param name
 */
void unsubscribe(std::string name);
```

## Fire
```cpp
/**
 * Fire an event (pointer)
 *
 * @param event
 */
template<class T>
void fire(T *event);
```

```cpp
/**
 * Fire an event (reference)
 *
 * @param event
 */
template<class T>
void fire(T &event);
```
