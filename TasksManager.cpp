#include <fstream>
#include "TasksManager.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

TasksManager::TasksManager()
{
    Load();
}

TasksManager::~TasksManager()
{
    Save();
}

void TasksManager::ShowAllTasks() const
{
    for (auto const &[subject, tasks] : allTasksBySubject)
    {
        ShowAllTasksOfSubject(subject);
    }
}

void TasksManager::ShowAllTasksOfSubject(string subject) const
{
    try
    {
        vector<Task> tasks = allTasksBySubject.at(subject);
        std::chrono::duration<double> duration = duration.zero();
        cout << subject + ": \n      ";
        for (Task task : tasks)
        {
            duration += task.GetDuration();
            cout << task.GetDuration().count() << " sec, ";
        }
        cout << "\n      Total : " << std::to_string(duration.count()) << " sec" << endl;
    }
    catch (const std::out_of_range &oor)
    {
        cout << "This subject doesn't exist" << endl;
    }
}

void TasksManager::StartTask(string subject)
{
    StopTask(subject);
    Task task = Task(subject);
    allTasksBySubject[subject].push_back(task);
}

void TasksManager::StopTask(string subject)
{
    try
    {
        vector<Task> tasks = allTasksBySubject.at(subject);
        allTasksBySubject[subject]
            .back()
            .StopTask();
    }
    catch (const std::out_of_range &oor)
    {
    }
}

void TasksManager::DeleteAllTasksOfSubject(string subject)
{
    allTasksBySubject.erase(subject);
}

void TasksManager::Save()
{
    std::ofstream out_stream("save.tasks", std::ofstream::out);

    for (auto const &[subject, tasks] : allTasksBySubject)
    {
        for (Task task : tasks)
        {
            out_stream << task.DumpInfos() << endl;
        }
    }
}

void TasksManager::LoadTask(string infos)
{
    std::string delimiter = "|";

    vector<string> splitInfos;

    size_t pos = 0;
    std::string token;
    while ((pos = infos.find(delimiter)) != std::string::npos)
    {
        token = infos.substr(0, pos);
        splitInfos.push_back(token);
        infos.erase(0, pos + delimiter.length());
    }
    splitInfos.push_back(infos);

    Task task = Task(splitInfos[0], splitInfos[1], splitInfos[2], splitInfos[3], splitInfos[4]);
    allTasksBySubject[splitInfos[0]].push_back(task);
}

void TasksManager::Load()
{
    std::string line;
    std::ifstream in_stream("save.tasks", std::ifstream::in);
    while (std::getline(in_stream, line))
    {
        //LoadTask(line);
        Task task = Task(line, true);
        allTasksBySubject[task.GetSubject()].push_back(task);
    }
}
