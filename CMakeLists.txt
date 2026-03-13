cmake_minimum_required(VERSION 3.20)

project(LogLib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(
  -Wall
  -Wextra
  -Wpedantic
)
include(FetchContent)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)

FetchContent_MakeAvailable(nlohmann_json)

FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG asio-1-30-2
)

FetchContent_MakeAvailable(asio)

add_library(logger
    logger/src/logger.cpp
    logger/src/filesink.cpp
    logger/src/networksink.cpp
)

target_include_directories(logger
  PUBLIC
    logger/include
            ${asio_SOURCE_DIR}/asio/include
)

target_compile_definitions(logger
    PUBLIC
        ASIO_STANDALONE
)

target_link_libraries(logger
  PUBLIC
    nlohmann_json::nlohmann_json
)

add_executable(test_app
  app/main.cpp
)

target_link_libraries(test_app
  PRIVATE
    logger
)
