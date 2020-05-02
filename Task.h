#include <iostream>
#include <chrono>

using std::string;

class Task
{
private:
    string subject;
    std::chrono::system_clock::time_point start;
    std::chrono::system_clock::time_point end;
    std::chrono::duration<double> duration;
    bool isStopped;
    string ShowSubject() const;
    string ShowStart() const;
    string ShowEnd() const;
    string ShowIsStopped() const;
    string ShowDuration();

public:
    Task(string subject);
    Task(string subjectStr, string startStr, string endStr, string durationStr, string isStoppedstr);
    ~Task(void);
    void StopTask();
    std::chrono::duration<double> GetDuration();
    string DumpInfos();
};