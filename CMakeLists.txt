cmake_minimum_required(VERSION 3.16)
project(rv64 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(rv64
        main.cpp
        config.cpp
        config.hpp
        enum_helpers.hpp
        memory/base_memory.hpp
        memory/flat_memory.cpp
        memory/flat_memory.cpp
        memory/flat_memory.hpp
        cpu/cpu.cpp
        cpu/cpu.hpp
        cpu/state.hpp
        cpu/decoder.hpp
        cpu/extensions/I.cpp
        memory/flat_test_memory.cpp
        memory/flat_test_memory.hpp
)

include(FetchContent)

FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
)

FetchContent_MakeAvailable(nlohmann_json)

# Link it
target_link_libraries(rv64 PRIVATE nlohmann_json::nlohmann_json)
