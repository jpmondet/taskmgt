#include <vector>
#include "Task.h"

using std::string;
using std::vector;

Task::Task(string subject) : subject(subject)
{
    start = std::chrono::system_clock::now();
    isStopped = false;
}

Task::Task(string subject, string startStr, string endStr, string durationStr, string isStoppedstr) : subject(subject) {
    int startInt = std::stoi(startStr);
    std::chrono::duration<int> durationTmp (startInt);
    std::cout << std::to_string(durationTmp.count()) << std::endl;
    std::chrono::system_clock::time_point starttp{durationTmp};
    start = starttp;
    isStopped = (std::stoi(isStoppedstr) ? true : false);
    // For now, we load only at launch so "isStopped" is always true"
    isStopped = true;
    if (isStopped) {
        int endInt = std::stoi(endStr);
        std::chrono::duration<int> durationTmp (endInt);
        std::chrono::system_clock::time_point endtp{durationTmp};
        end = endtp;
        double durationD = std::stod(durationStr);
        //duration = end - start;
        //std::cout << durationD << " or " << std::to_string(duration.count()) << std::endl;
        //duration = std::chrono::system_clock::duration()
        duration = std::chrono::duration<double>(durationD);
    }
}

Task::Task(string serializedInfos, bool load) {
  // This constructor does nothing it isn't called as a 'load' action
  // This bool flag is needed because we already have a 'string' constructor...
  if (load){

    //Deserialization of the compact string into a vector
    std::string delimiter = "|";
    vector<string> splitInfos;
    size_t pos = 0;
    std::string token;
    while ((pos = serializedInfos.find(delimiter)) != std::string::npos)
    {
        token = serializedInfos.substr(0, pos);
        splitInfos.push_back(token);
        serializedInfos.erase(0, pos + delimiter.length());
    }
    splitInfos.push_back(serializedInfos);

    // Variables only used to improved readability on the rest of the func
    subject = splitInfos[0];
    string startStr = splitInfos[1];
    string endStr = splitInfos[2];
    string durationStr = splitInfos[3];
    string isStoppedstr = splitInfos[4];

    //Converting 2nd string part into 'start' time_point 
    int startInt = std::stoi(startStr);
    std::chrono::duration<int> durationTmp (startInt);
    std::chrono::system_clock::time_point starttp{durationTmp};
    start = starttp;

    //Converting last string part into bool
    isStopped = (std::stoi(isStoppedstr) ? true : false);
    // For now, we load only at launch so "isStopped" is always true"
    isStopped = true;

    if (isStopped) {
        //Converting 3rd string part into 'end' time_point
        int endInt = std::stoi(endStr);
        std::chrono::duration<int> durationTmp (endInt);
        std::chrono::system_clock::time_point endtp{durationTmp};
        end = endtp;

        //Converting 4th string part into a 'duration'
        double durationD = std::stod(durationStr);
        duration = std::chrono::duration<double>(durationD);
    }
  } else {
      throw "Not a loading action, this constructor shouldn't be used";
  }

}

Task::~Task()
{
    StopTask();
}

void Task::StopTask()
{
    if (!isStopped)
    {
        end = std::chrono::system_clock::now();
        duration = end - start;
        isStopped = true;
        //std::cout << "Task " << GetSubject() << " took : " << duration.count() << " sec to complete" << std::endl;
    }
}

string Task::ShowSubject() const
{
    return subject;
}

string Task::ShowStart() const
{
    std::time_t startt = std::chrono::system_clock::to_time_t(start);
    return std::to_string(startt);
}
string Task::ShowEnd() const
{
    std::time_t endt = std::chrono::system_clock::to_time_t(end);
    return std::to_string(endt);
}
string Task::ShowIsStopped() const
{
    return std::to_string(isStopped);
}

string Task::ShowDuration()
{
    return std::to_string(GetDuration().count());
}

std::chrono::duration<double> Task::GetDuration()
{
    if (isStopped)
        return duration;

    end = std::chrono::system_clock::now();
    duration = end - start;

    return duration;
}

string Task::DumpInfos()
{
    return ShowSubject() + "|" + ShowStart() + "|"  + ShowEnd() + "|"  + ShowDuration() + "|"  + ShowIsStopped();
}
