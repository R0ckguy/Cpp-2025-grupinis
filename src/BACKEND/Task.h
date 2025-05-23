#pragma once
#include <string>
#include <chrono>
#include <nlohmann/json.hpp>

struct Task {
    int         id;
    std::string title;
    std::string description;
    std::chrono::system_clock::time_point dueDate;
    bool        completed = false;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(
        Task,
        id, title, description,
        completed
    )
};
