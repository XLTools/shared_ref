shared_ref
==========

shared_ref is a non-nullable, reference-counted reference wrapper.

**Table of Contents**

- [Use](#use)
- [Contributor Guidelines](#contributor-guidelines)
- [License](#license)

## Use

shared_ref can used similarly to shared_ptr, however, it cannot inherit existing pointers.

```cpp
#include <shared_ref.hpp>
#include <iostream>

int main(void)
{
    auto value = ref::make_shared<int>(1);
    auto copy(value);
    std::cout << "Value is: " << value.get() << std::endl;
}
```

## Contributor Guidelines

All useful pull requests will be merged, provided that they do not add external dependencies and follow these guidelines.

1. Preprocessor macros should be used sparingly.
2. Code syntax should not depend on the preprocessor.
3. Your code must be readable.

## License

MIT, see [license](LICENSE.md).
