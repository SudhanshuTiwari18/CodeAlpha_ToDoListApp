#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

class Task {
public:
    string description;
    string category;
    bool completed;

    Task(string desc, string cat = "General", bool comp = false) {
        description = desc;
        category = cat;
        completed = comp;
    }

    string toString() const {
        return description + " | " + category + " | " + (completed ? "Done" : "Pending");
    }
};

class ToDoList {
    vector<Task> tasks;
    const string filename = "tasks.txt";

public:
    void addTask() {
        string desc, cat;
        cout << "Enter task description: ";
        cin.ignore();
        getline(cin, desc);
        cout << "Enter category (optional): ";
        getline(cin, cat);
        if (cat.empty()) cat = "General";
        tasks.push_back(Task(desc, cat));
        cout << "Task added!\n";
    }

    void viewTasks(bool showCompleted) {
        cout << (showCompleted ? "\nCompleted Tasks:\n" : "\nPending Tasks:\n");
        int count = 0;
        for (size_t i = 0; i < tasks.size(); ++i) {
            if (tasks[i].completed == showCompleted) {
                cout << i + 1 << ". " << tasks[i].toString() << endl;
                count++;
            }
        }
        if (count == 0) cout << "No tasks found.\n";
    }

    void markTaskCompleted() {
        viewTasks(false);
        int index;
        cout << "\nEnter the task number to mark as completed: ";
        cin >> index;
        if (index > 0 && index <= tasks.size() && !tasks[index - 1].completed) {
            tasks[index - 1].completed = true;
            cout << "Task marked as completed!\n";
        } else {
            cout << "Invalid input or task already completed.\n";
        }
    }

    void saveToFile() {
        ofstream out(filename);
        for (const auto &task : tasks) {
            out << task.description << "|" << task.category << "|" << task.completed << "\n";
        }
        out.close();
        cout << "Tasks saved to file.\n";
    }

    void loadFromFile() {
        tasks.clear();
        ifstream in(filename);
        string line;
        while (getline(in, line)) {
            size_t p1 = line.find('|');
            size_t p2 = line.rfind('|');
            if (p1 == string::npos || p2 == string::npos || p1 == p2) continue;

            string desc = line.substr(0, p1);
            string cat = line.substr(p1 + 1, p2 - p1 - 1);
            bool comp = (line.substr(p2 + 1) == "1");

            tasks.push_back(Task(desc, cat, comp));
        }
        in.close();
        cout << "Tasks loaded from file.\n";
    }

    void menu() {
        loadFromFile();
        int choice;
        do {
            cout << "\n====== TO-DO LIST MENU ======\n";
            cout << "1. Add Task\n";
            cout << "2. Mark Task as Completed\n";
            cout << "3. View Pending Tasks\n";
            cout << "4. View Completed Tasks\n";
            cout << "5. Save and Exit\n";
            cout << "Choose an option: ";
            cin >> choice;

            switch (choice) {
                case 1: addTask(); break;
                case 2: markTaskCompleted(); break;
                case 3: viewTasks(false); break;
                case 4: viewTasks(true); break;
                case 5: saveToFile(); cout << "Exiting...\n"; break;
                default: cout << "Invalid choice. Try again.\n";
            }
        } while (choice != 5);
    }
};

int main() {
    ToDoList app;
    app.menu();
    return 0;
}
