#pragma once

#include "Task.h"
#include <string>
#include <vector>
#include <chrono>

class TaskManager {
public:
    explicit TaskManager(const std::string& storageFile);

    Task addTask(const std::string& title,
                 const std::string& desc,
                 std::chrono::system_clock::time_point due);
    std::vector<Task> listAll() const;
    std::vector<Task> searchByTitle(const std::string& term) const;
    void sortByDueDate();
    bool deleteById(int id);
    bool markCompleted(int id);

    void load();
    void save() const;

private:
    std::string storageFile_;
    std::vector<Task> tasks_;
    int nextId_ = 1;

    static std::string timeToString(std::chrono::system_clock::time_point tp);
    static std::chrono::system_clock::time_point stringToTime(const std::string& s);
};
