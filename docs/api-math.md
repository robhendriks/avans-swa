# Math

## vec2_t

Represents a vector in two-dimensional space.

```cpp
struct vec2_t {
    float x, y;
};
```

### Using vec2_t

```cpp
#include "math/vec2.hpp"
using namespace math; // OPTIONAL
```

```
math::vec2_t vec(10, 10);
// OR
math::vec2_t vec = {10, 10};
// OR
math::vec2_t vec(vec_to_copy); // Copy constructor
```

## box2_t

Represents a rectangular shape in two-dimensional space.

```cpp
struct box2_t {
    vec2_t min, max;
};
```

### Using box2_t

```cpp
#include "math/box2.hpp"
using namespace math; // OPTIONAL
```

```cpp
math::box2_t box(
    math::vec2_t(0, 0),
    math::vec2_t(10, 10));
// OR
math::box2_t box = {
    math::vec2_t(0, 0), 
    math::vec2_t(10, 10)};
// OR
math::box2_t box = {{0, 0}, {10, 10}};
```
