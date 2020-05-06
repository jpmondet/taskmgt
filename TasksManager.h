#include <map>
#include <vector>
#include "Task.h"

using std::map;
using std::vector;
using std::string;

class TasksManager
{
private:
    map<string, vector<Task>> allTasksBySubject;
    map<string, vector<Task>> GetAllTasks() const { return allTasksBySubject; };

public:
    TasksManager();
    ~TasksManager(void);
    void ShowAllTasks() const;
    void ShowAllTasksOfSubject(string subject) const;
    void StartTask(string subject);
    void StopTask(string subject);
    void DeleteAllTasksOfSubject(string subject);
    void Save();
    void LoadTask(string infos);
    void Load();
};