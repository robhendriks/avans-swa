# Configuration

## ini_config

```cpp
#include "settings/ini_config.h"
using namespace settings; // OPTIONAL
```

### Loading 

```cpp
settings::ini_config cfg("my_ini_file.ini");

if (!cfg.load()) {
    fprintf(stderr, "Failed to load configuration!\n");
    return;
}
```

### Getting properties

Example INI file.

```ini
; Demo section
[demo]
my_string = Hello World!
my_bool = true
my_double = 10.0
my_long = 10
```

Example code.

```cpp
// Get string
const char *my_string = cfg.get_value("demo", "my_string");
// Get bool
bool my_bool = cfg.get_bool("demo", "my_bool");
// Get double
double my_double = cfg.get_double("demo", "my_double");
// Get long
long my_long = cfg.get_long("demo", "my_long);
```

Example code with fallback (works on all four types).

```cpp
// Get double, return -1 if the property doesn't exist
double my_double = cfg.get_double("demo", "my_double", -1);
```
