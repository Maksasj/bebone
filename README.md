<div>
  <img align="left" src="https://github.com/Maksasj/bebone/blob/master/docs/images/tmpLogo.png" width="288px">
  
  # Bebone
  Bebone - Is a framework/engine aimed for flexible and comfortable game development, written in C++. 
  In other words Bebone is a set of useful game development libraries, written and integrated 
  in Bebone framework ecosystem.
  
  > Bebone is not a new javascript framework btw, this time it is and game development one !
  
  Cool looking widgets 
  <img src="https://img.shields.io/github/stars/Maksasj/bebone" alt="stars">
  <img src="https://img.shields.io/github/actions/workflow/status/Maksasj/bebone/clang_build_win.yml" alt="build">
  <img src="https://img.shields.io/github/license/Maksasj/bebone" alt="build">
  
  <br>
</div>

## Roadmap

### 0.1v Release (This year)
1. **Graphics abstraction layer**. General OpenGL. Window, Monitor apis.
2. **Event system**. Generic event system
3. **Input system**. Event based input system

### 0.1.1v
1. **Asset system**. Basic abstractions for creating/editing image data.

### 0.1.2v
1. **Profiler** General bebone profiler

### 0.2v ...
1. *Scripting*.
2. *Sound system*.
3. *Physics engine*.

## Features
*Todo*

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
Bebone is free, open source game development framework. All code in this repository FOR NOW is licensed under
- MIT License ([LICENSE.md](https://github.com/Maksasj/bebone/blob/master/LICENSE.md) or https://opensource.org/license/mit/)