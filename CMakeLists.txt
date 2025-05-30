cmake_minimum_required(VERSION 3.10)
project(TaskManager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include headers
include_directories(${PROJECT_SOURCE_DIR}/src/BACKEND)

# Gather source files
file(GLOB SRCS "${PROJECT_SOURCE_DIR}/src/BACKEND/*cpp")
list(REMOVE_ITEM SRCS "${PROJECT_SOURCE_DIR}/src/BACKEND/main.cpp")

# External library (JSON)
find_package(nlohmann_json 3.2.0 REQUIRED)

# ----------------------------------------------------------------------
# Build the main taskmanager static library
# ----------------------------------------------------------------------
add_library(taskmanager STATIC ${SRCS})
target_link_libraries(taskmanager PRIVATE nlohmann_json::nlohmann_json)

# ----------------------------------------------------------------------
# Build the main CLI application
# ----------------------------------------------------------------------
add_executable(task_app src/BACKEND/main.cpp)
target_link_libraries(task_app PRIVATE taskmanager nlohmann_json::nlohmann_json)

# ----------------------------------------------------------------------
#                        TESTS INCLUDED
# ----------------------------------------------------------------------

enable_testing()

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(TaskManagerTests
    tests/test_TaskManager.cpp
)

target_link_libraries(TaskManagerTests
    PRIVATE
        taskmanager
        gtest_main
        pthread
        nlohmann_json::nlohmann_json
)

target_include_directories(TaskManagerTests PRIVATE include)

include(GoogleTest)
gtest_discover_tests(TaskManagerTests)