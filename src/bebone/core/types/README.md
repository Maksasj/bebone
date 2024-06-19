# omni::types

omni::types - C++ basic algebraic/utils type library.

## Features
- Algebraic vectors
    - 2D vector
    - 3D vector
    - 4D vector
- UUID type
- Color types
    - Color formats
- Algebraic matrix
    - Euler rotation matrices
    - Trait-Bryan rotation matrices
- Interpolation functions

## Build
```bash
cmake -B build -G Ninja

cmake --build build
```

## Testing
```bash
cmake --build build

build\tests\unit\ctest
```

## License
omni_types is free, open source library. All code in this repository is licensed under
- MIT License ([LICENSE.md](https://github.com/Maksasj/omni_types/blob/master/LICENSE.md) or https://opensource.org/license/mit/)