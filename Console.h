#include "TasksManager.h"

using std::string;


class Console {
    private:
        int lastAnswer;
        TasksManager tasksManager;

        int Menu();
        void ShowMainMenu() const;
        void ClearScreen() const;
        void SayGoodbye() const;
        void SayAnyKey() const;
        int GetAnswer() const;
        string GetStrAnswer() const;
        string ActivityQuestion() const;
    public:
        Console();
        ~Console();
};