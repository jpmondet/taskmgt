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
    //TODO: This constructor should take directly the iostream.
    //It would be less messy to do the heavy lifting inside this func
    //instead of outside Task impl. The caller shouldn't need to know the
    //internals.
    Task(string subjectStr, string startStr, string endStr, string durationStr, string isStoppedstr);
    Task(string serializedInfos, bool load);
    ~Task(void);
    void StopTask();
    std::chrono::duration<double> GetDuration();
    string DumpInfos();
    string GetSubject() { return subject; };
};
