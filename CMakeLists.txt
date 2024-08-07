cmake_minimum_required(VERSION 3.21)
project(Bebone)

# Bebone versions
set(BEBONE_VERSION_MAJOR 0 CACHE STRING "Bebone major version")
set(BEBONE_VERSION_MINOR 2 CACHE STRING "Bebone minor version")
set(BEBONE_VERSION_PATCH 0 CACHE STRING "Bebone patch version")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Bebone build type" FORCE)
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG)
endif()

if(CMAKE_BUILD_TYPE MATCHES Release)
    add_definitions(-DNDEBUG)
endif()

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

# Bebone build options
option(BEBONE_EXAMPLES          "Bebone build all examples"     ON)
option(BEBONE_TESTS             "Bebone build all tests"        ON)

option(BEBONE_BUILD_CORE        "Bebone build core module"      ON)
option(BEBONE_BUILD_ASSETS      "Bebone build assets module"    ON)
option(BEBONE_BUILD_GFX         "Bebone build gfx module"       ON)
option(BEBONE_BUILD_SOUND       "Bebone build sound module"     ON)

add_subdirectory(3dparty)
add_subdirectory(src)

if(BEBONE_EXAMPLES)
    add_subdirectory(examples)
endif()

if(BEBONE_TESTS)
    add_subdirectory(tests)
endif()