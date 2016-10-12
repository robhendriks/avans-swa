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

```cpp
math::vec2_t vec(10, 10);
// OR
math::vec2_t vec = {10, 10};
// OR
math::vec2_t vec(vec_to_copy); // Copy constructor
```

#### Operations

**min**

Set both axes to the smallest of both values.

```cpp
auto vec = {10, 10};
vec.min({5, 15}); // Returns {5, 10}
```

**max**

Set both axes to the largest of both values.

```cpp
auto vec = {10, 10};
vec.max({5, 15}); // Returns {10, 15}
```

**clamp**

Clamp both axes between a minimum and maximum value.

```cpp
auto vec = {-1, 1000};
vec.clamp(0, 999); // Returns {0, 999}
```

#### Operators

##### Add

```cpp
// Add scalar (copy)
vec + 10
// Add vectors (copy)
vec + vec

// Add scalar
vec += 10
// Add vectors
vec += vec
```

##### Subtract

```cpp
// Sub scalar (copy)
vec - 10
// Sub vectors (copy)
vec - vec

// Sub scalar
vec -= 10
// Sub vectors
vec -= vec
```

##### Multiply

```cpp
// Multiply scalar (copy)
vec * 10
// Multiply vectors (copy)
vec * vec

// Multiply scalar
vec *= 10
// Multiply vectors
vec *= vec
```

##### Divide

```cpp
// Divide scalar (copy)
vec / 10
// Divide vectors (copy)
vec / vec

// Divide scalar
vec /= 10
// Divide vectors
vec /= vec
```

##### Increment/decrement

```cpp
// Increment
++vec
// Decrement
--vec
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
math::box2_t box(math::vec2_t(0, 0), math::vec2_t(10, 10));
// OR
math::box2_t box = {{0, 0}, {10, 10}};
// OR
math::box2_t box(box_to_copy); // Copy constructor
```
