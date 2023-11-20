#include <iostream>
#include<string>
#include<vector>
#include <list>
#include <ctime>
#include <fstream>
enum Choices { // Rename int values for choices so no magical numbers appear
    QUIT, ADD, COMPLETE 
};

class Task { // main class of the programm, task contains id, description and status of completion
private:
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
    bool iscompleted() { return done; }
    // Functions for accesing private variables and changing them 

    void markcompleted(bool var) { done = var; } 
    void setId(int n) { id = n; }
    void setDescription(std::string str) { description = str; } 
    // Functions for accesing private variables and changing them 

};
void ReadTask(std::string filename, std::list<Task>& Tasks); 
void WriteTask(std::string filenamem, std::list<Task>& Tasks);
//Prototype for functions described below
int main()
{

    srand(static_cast<unsigned>(time(nullptr))); // Setting seed of rand%

    std::list<Task>::iterator it;

    int choice = ADD, input_id;
    std::string input_task;
    std::list<Task> Tasks;
    Tasks.clear();
    Task temp;
    std::string FILE_NAME = "tasks.txt";
    ReadTask(FILE_NAME, Tasks);
    // Describing basic variables ued later




    while (choice != QUIT) {
        system("cls");
        std::cout << std::endl;
        std::cout << std::endl;


        for (it = Tasks.begin(); it != Tasks.end(); it++) {

            std::string iscompletedstr = it->iscompleted() ? "done" : "undone";

            std::cout << it->getid() << " | " << it->getdescription() << " | " << iscompletedstr
                << std::endl;
        } // Outputing listof tasks
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
            break; // Quit the programm
        case ADD:
            std::cout << "Enter a description of a task:\n";
            std::cin.ignore();
            getline(std::cin, input_task);
            Tasks.push_back(Task(input_task));
            continue; // Add the task by inputing description

        case COMPLETE:
            std::cout << "Enter id of a task you want to complete:\n";
            std::cin >> input_id;
            for (it = Tasks.begin(); it != Tasks.end(); it++) {

                if (input_id == it->getid()) {
                    it->markcompleted(true);
                    break;
                }
            } // Marking task as complete
            continue;
        default:
            std::cout << "Error, wrong input";
            continue; // If anything of the above
        } // PRoccesing the choices

    }
    WriteTask(FILE_NAME, Tasks); // Calling func to write user-inputed information into file


}

void ReadTask(std::string filename, std::list<Task>& Tasks) { // Function to read data from file  
    std::fstream myfile(filename, std::ios::in);

    if (myfile.is_open()) {
        while (!myfile.eof()) {
            Task task;
            int id;
            std::string description;
            bool iscomplete;
            char separator;

            if (!(myfile >> id)) { break; }

            myfile >> separator;
            std::getline(myfile, description, '|');
            myfile >> iscomplete;

            task.setId(id);
            task.setDescription(description);
            task.markcompleted(iscomplete);

            Tasks.push_back(task);
        }

        myfile.close();
    }
}


void WriteTask(std::string filename, std::list<Task>& Tasks) { // Function that writes data into the file 
    std::fstream myfile;
    myfile.open(filename, std::ios::app);
    std::list<Task>::iterator it;

    for (it = Tasks.begin(); it != Tasks.end(); it++) {

        myfile << it->getid() << " | " << it->getdescription() << " | " << it->iscompleted() << std::endl;

    }
    myfile.close();
}
