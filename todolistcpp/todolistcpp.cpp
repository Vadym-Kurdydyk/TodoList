
#include <iostream>
#include<string>
#include<vector>
#include <list>
#include <ctime>
#include <fstream>
enum Choices {
    QUIT, ADD, COMPLETE
};

class Task {
public:
    int id;
    std::string description;
    bool done;
public:
    Task() : id(0), description(""), done(false) {}
    ~Task() = default;

    Task(std::string new_description) {
        id = rand() % 100 + 1;
        description = new_description;
        done = false;
    }

    int getid() { return id; }
    std::string getdescription() { return description; }
    bool iscompleted(){ return done; }
    
    void markcompleted(bool var) { done = var; }

};
int main()
{
    srand(static_cast<unsigned>(time(nullptr)));
    std::list<Task> Tasks;
    std::list<Task>::iterator it;
    Tasks.clear();
    int choice = ADD, input_id;
    std::string input_task;
    Task temp;
    std::fstream myfile;
    myfile.open("tasks.txt", std::ios::out | std::ios::in);
    char ch;


    if (myfile.is_open()) {

        while (!(myfile.eof())) {
            Task task;
            int id;
            myfile >> task.id;
            char separator;
            myfile >> separator;
            std::getline(myfile, task.description, '|');
            myfile >> std::boolalpha >> task.done;
            Tasks.push_back(task);
            if (!(myfile >> task.id)) {
                break;

            }
            myfile.close();
        }
        while (choice != QUIT) {
            system("cls");
            std::cout << std::endl;
            std::cout << std::endl;


            for (it = Tasks.begin(); it != Tasks.end(); it++) {

                std::string iscompletedstr = it->iscompleted() ? "done" : "undone";

                std::cout << it->getid() << " | " << it->getdescription() << " | " << iscompletedstr
                    << std::endl;
            }
            if (Tasks.empty()) {
                std::cout << "Add your first task!\n";
            }
            std::cout << "Press 1 to add task\n"
                      << "Press 2 to comlete taks\n"
                      << "Press 0 to quit\n";
            std::cin >> choice;
            switch (choice) {
            case QUIT:
                std::cout << "Have a great day\n";
                break;
            case ADD:
                std::cout << "Enter a description of a task:\n";
                std::cin.ignore();
                getline(std::cin, input_task);
                Tasks.push_back(Task(input_task));
                continue;

            case COMPLETE:
                std::cout << "Enter id of a task you want to complete:\n";
                std::cin >> input_id;
                for (it = Tasks.begin(); it != Tasks.end(); it++) {

                    if (input_id == it->getid()) {
                        it->markcompleted(true);
                        break;
                    }
                }
                continue;
            default:
                std::cout << "Error, wrong input";
                continue;
            }

        }

        for (it = Tasks.begin(); it != Tasks.end(); it++) {

            myfile << it->getid() << " | " << it->getdescription() << " | " << it->iscompleted() << std::endl;

        }
        myfile.close();
    }
}


