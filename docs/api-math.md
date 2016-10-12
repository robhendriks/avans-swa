# Math

Available classes and/or structures:

* vec2_t
* box2_t

## vec2_t

Represents a vector in two-dimensional space.

```cpp
struct vec2_t {
    float x, y;
};
```

```cpp
#include "math/vec2.hpp"
using namespace math; // OPTIONAL
```

## box2_t

Represents a rectangular shape in two-dimensional space.

```cpp
struct box2_t {
    vec2_t min, max;
};
```

```cpp
#include "math/box2.hpp"
using namespace math; // OPTIONAL
```
