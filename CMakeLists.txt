cmake_minimum_required(VERSION 3.10)
project(TaskManager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRCS "${PROJECT_SOURCE_DIR}/src/*.cpp")

find_package(nlohmann_json 3.2.0 REQUIRED)

add_library(taskmanager STATIC
    ${SRCS}
)

target_link_libraries(taskmanager
    PRIVATE nlohmann_json::nlohmann_json
)

add_executable(task_app
    ${PROJECT_SOURCE_DIR}/src/main.cpp
)
target_link_libraries(task_app PRIVATE taskmanager)
