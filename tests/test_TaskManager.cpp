#include <gtest/gtest.h>
#include "../include/TaskManager.h"

class TaskManagerTest : public ::testing::Test {
protected:
    std::string testFile = "test_tasks.json";
    TaskManager mgr = TaskManager(testFile);

    void SetUp() override {
        mgr = TaskManager(testFile);
        // Clear out tasks before each test
        mgr.load();
        auto tasks = mgr.listAll();
        for (const auto& task : tasks) {
            mgr.deleteById(task.id);
        }
        mgr.save();
    }

    std::chrono::system_clock::time_point now() {
        return std::chrono::system_clock::now();
    }
};

TEST_F(TaskManagerTest, AddTaskIncreasesListSize) {
    auto initialSize = mgr.listAll().size();
    mgr.addTask("Test Title", "Test Desc", now());
    ASSERT_EQ(mgr.listAll().size(), initialSize + 1);
}

TEST_F(TaskManagerTest, SearchFindsCorrectTask) {
    mgr.addTask("UniqueSearchKey", "Test", now());
    auto results = mgr.searchByTitle("UniqueSearchKey");
    ASSERT_FALSE(results.empty());
    EXPECT_EQ(results[0].title, "UniqueSearchKey");
}

TEST_F(TaskManagerTest, CanMarkTaskAsCompleted) {
    auto task = mgr.addTask("Complete Me", "To be done", now());
    bool success = mgr.markCompleted(task.id);
    EXPECT_TRUE(success);

    auto tasks = mgr.listAll();
    auto it = std::find_if(tasks.begin(), tasks.end(), [&](const Task& t) {
        return t.id == task.id;
    });

    ASSERT_TRUE(it != tasks.end());
    EXPECT_TRUE(it->completed);
}

TEST_F(TaskManagerTest, CanDeleteTaskById) {
    auto task = mgr.addTask("Delete Me", "To be deleted", now());
    bool deleted = mgr.deleteById(task.id);
    EXPECT_TRUE(deleted);

    auto allTasks = mgr.listAll();
    auto found = std::any_of(allTasks.begin(), allTasks.end(), [&](const Task& t) {
        return t.id == task.id;
    });
    EXPECT_FALSE(found);
}

TEST_F(TaskManagerTest, SortsByDueDate) {
    using namespace std::chrono;
    mgr.addTask("Later", "Due later", now() + hours(24));
    mgr.addTask("Sooner", "Due sooner", now());

    mgr.sortByDueDate();
    auto tasks = mgr.listAll();

    ASSERT_EQ(tasks.size(), 2);
    EXPECT_LT(tasks[0].dueDate, tasks[1].dueDate);
}
