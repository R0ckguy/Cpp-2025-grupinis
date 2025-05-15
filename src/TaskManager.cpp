#include "TaskManager.h"

#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std::chrono;

TaskManager::TaskManager(const std::string& storageFile)
  : storageFile_(storageFile)
{
    load();
}

void TaskManager::load() {
    std::ifstream in(storageFile_);
    if (!in.is_open()) return;

    json j;
    in >> j;
    tasks_.clear();

    for (auto& el : j) {
        Task t = el.get<Task>();
        t.dueDate = stringToTime(el.at("dueDate").get<std::string>());
        tasks_.push_back(t);
        nextId_ = std::max(nextId_, t.id + 1);
    }
}

void TaskManager::save() const {
    json j = json::array();
    for (auto& t : tasks_) {
        json el = t;
        el["dueDate"] = timeToString(t.dueDate);
        j.push_back(el);
    }
    std::ofstream out(storageFile_);
    out << j.dump(4);
}

Task TaskManager::addTask(const std::string& title,
                         const std::string& desc,
                         system_clock::time_point due)
{
    Task t{ nextId_++, title, desc, due, false };
    tasks_.push_back(t);
    return t;
}

std::vector<Task> TaskManager::listAll() const {
    return tasks_;
}

std::vector<Task> TaskManager::searchByTitle(const std::string& term) const {
    std::vector<Task> res;
    for (auto& t : tasks_)
        if (t.title.find(term) != std::string::npos)
            res.push_back(t);
    return res;
}

void TaskManager::sortByDueDate() {
    std::sort(tasks_.begin(), tasks_.end(),
              [](auto& a, auto& b){ return a.dueDate < b.dueDate; });
}

bool TaskManager::deleteById(int id) {
    auto oldSize = tasks_.size();
    tasks_.erase(
      std::remove_if(tasks_.begin(), tasks_.end(),
                     [id](auto& t){ return t.id == id; }),
      tasks_.end());
    return tasks_.size() < oldSize;
}

bool TaskManager::markCompleted(int id) {
    for (auto& t : tasks_)
        if (t.id == id) {
            t.completed = true;
            return true;
        }
    return false;
}

std::string TaskManager::timeToString(system_clock::time_point tp) {
    std::time_t time = system_clock::to_time_t(tp);
    std::tm tm = *std::localtime(&time);
    std::ostringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%d %H:%M");
    return ss.str();
}

system_clock::time_point TaskManager::stringToTime(const std::string& s) {
    std::tm tm = {};
    std::istringstream ss(s);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M");
    if (ss.fail()) {
        return system_clock::now();
    }
    return system_clock::from_time_t(std::mktime(&tm));
}
