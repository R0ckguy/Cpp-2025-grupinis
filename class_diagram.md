classDiagram
    class Task {
        +int id
        +string title
        +string description
        +system_clock::time_point dueDate
        +bool completed
    }

    class TaskManager {
        -string filename
        -vector<Task> tasks
        +TaskManager(string filename)
        +void save()
        +Task addTask(string title, string description, system_clock::time_point dueDate)
        +bool deleteById(int id)
        +bool markCompleted(int id)
        +vector<Task> listAll()
        +vector<Task> searchByTitle(string term)
        +void sortByDueDate()
    }

    TaskManager "1" -- "0..*" Task : manages
