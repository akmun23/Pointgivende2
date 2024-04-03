#include "robot.h"
#include "task.h"
#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>

#include<unistd.h> // for sleep on unix


int main(int argc, char *argv[])
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("robot_worker"); // Ret til det schema navn du har valgt
    db.setUserName("aksel");  // Ret brugernavn
    db.setPassword("password");  // Ret password
    db.open();

    QSqlQuery query;
    Robot robots[100];
    int number = 0;
    Task task;

    std::string input;

    std::cout << "Welcome to the robot worker" << std::endl;
    std::cout << "Commands: add, get, do, exit, new, set" << std::endl;
    std::cout << "Type help for commands" << "\n" << std::endl;

    int i = 0;

    // Main loop
    while(1){
        if(i > 0){
            std::cout << "Enter next command or type help for commands" << "\n" << std::endl;
        }
        std::cin >> input;
        input[0] = tolower(input[0]);
        if(input == "exit"){
            break;
        } else if(input == "add"){
            task.addTask();
        } else if(input == "get"){
            task.getTask();
        } else if(input == "do"){
            robots[0].doTask();
        } else if(input == "new"){
            int id;
            std::cout << "Enter name of robot:";
            std::string name;
            std::cin.ignore();
            std::cout << std::endl;
            std::getline(std::cin, name);
            std::cout << "Enter the task to do:" << std::endl;
            std::string desc;
            std::getline(std::cin, desc);
            query.prepare("SELECT * FROM task where description = :desc");
            query.bindValue(":desc", QString::fromStdString(desc));
            query.exec();
            while(query.next()){
                id = query.value(0).toInt();
            }
            if(id == 0){
                std::cout << "Task does not exist" << std::endl;
                std::cout << "Robot hasnt been assigned a task" << std::endl;
            }
            robots[number].init(name, id);
            number++;

        } else if(input == "set"){
            int id;
            bool exists = true;
            std::cout << "Enter name of robot:";
            std::string name;
            std::cin.ignore();
            std::cout << std::endl;
            std::getline(std::cin, name);

            query.prepare("SELECT count(*) FROM robots where name = :name");
            query.bindValue(":name", QString::fromStdString(name));
            if(query.exec()){
                while(query.next()){
                    if(query.value(0).toInt() == 0){
                        std::cout << "Robot does not exist" << std::endl;
                        exists = false;
                    }
                }
            }

            if(!exists){
                continue;
            }

            std::cout << "Enter the task to do:" << std::endl;
            std::string desc;
            std::getline(std::cin, desc);
            query.prepare("SELECT * FROM task where description = :desc");
            query.bindValue(":desc", QString::fromStdString(desc));
            query.exec();
            while(query.next()){
                id = query.value(0).toInt();
            }
            query.prepare("UPDATE robots SET current_task = :id WHERE name = :name");
            query.bindValue(":id", id);
            query.bindValue(":name", QString::fromStdString(name));
            query.exec();
        } else if(input == "help"){
            std::cout << "Commands: add, get, do, exit" << std::endl;
            std::cout << "Add: Add a task to the database" << std::endl;
            std::cout << "Get: Get list of all tasks from the database" << std::endl;
            std::cout << "Do: Do the task if a robot is assisgned to it" << std::endl;
            std::cout << "New: Create a new robot and assign a task to it" << std::endl;
            std::cout << "Exit: Exit the program" << std::endl;
            std::cout << "Set: Set the task for a robot" << std::endl;
        } else {
            std::cout << "Command not found" << std::endl;
        }
        i++;
    }

    return 1;
}
