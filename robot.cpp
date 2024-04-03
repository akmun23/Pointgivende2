#include "robot.h"
#include "qdebug.h"
#include "qsqldatabase.h"
#include "qsqlquery.h"
#include "qsqlrecord.h"
#include <iostream>

Robot::Robot(){}

Robot::Robot(std::string name, int taskID):_name(name), _taskID(taskID) {
    //Checks if task is already being done
    while(1){
        int task_check;
        bool check = false;
        bool real = false;
        query.exec("SELECT * from robots");

        // Checks if the task is already being done
        while (query.next()) {
            task_check = query.value(2).toInt();
            if(task_check == _taskID){
                std::cout << name << "'s task is already being done" << std::endl;
                task.getTask();
                std::cout << "Please enter a task that is not being done: " << std::endl;
                std::string taskName;
                std::getline(std::cin, taskName);
                bool real = false;

                while(!real){
                    // Checks if the task is in the database
                    query.prepare("SELECT description FROM task WHERE description = :description");
                    query.bindValue(":description", QString::fromStdString(taskName));
                    query.exec();
                    if(query.size() == 0){
                        std::cout << "Task not found" << std::endl;
                        real = false;
                        std::cout << "Please enter a task that is not being done: " << std::endl;
                        std::getline(std::cin, taskName);
                    } else {
                        real = true;
                    }
                }

                // Gets the task_id for the task
                query.prepare("SELECT task_id FROM task WHERE description = :description");
                query.bindValue(":description", QString::fromStdString(taskName));
                query.exec();
                while (query.next()) {
                    _taskID = query.value(0).toInt();
                    check = true;
                }
            }
        }
        if(check == false){
            break;
        }
    }

    //Adds robot to the database
    query.exec("SELECT * FROM robots");
    int id = query.size()+1;
    query.prepare("INSERT INTO robots (robot_id, name, current_task)"
                  "VALUES (:id, :name, :taskName)");
    query.bindValue(":id", id);
    query.bindValue(":name", QString::fromStdString(_name));
    query.bindValue(":taskName", _taskID);
    query.exec();
}

void Robot::init(std::string name, int taskID){
    //Checks if task is already being done
    _name = name;
    _taskID = taskID;
    while(1){
        int task_check;
        bool check = false;
        bool real = false;
        query.exec("SELECT * from robots");

        // Checks if the task is already being done
        while (query.next()) {
            task_check = query.value(2).toInt();
            if(task_check == _taskID){
                std::cout << name << "'s task is already being done" << std::endl;
                task.getTask();
                std::cout << "Please enter a task that is not being done: " << std::endl;
                std::string taskName;
                std::getline(std::cin, taskName);
                bool real = false;

                while(!real){
                    // Checks if the task is in the database
                    query.prepare("SELECT description FROM task WHERE description = :description");
                    query.bindValue(":description", QString::fromStdString(taskName));
                    query.exec();
                    if(query.size() == 0){
                        std::cout << "Task not found" << std::endl;
                        real = false;
                        std::cout << "Please enter a task that is not being done: " << std::endl;
                        std::getline(std::cin, taskName);
                    } else {
                        real = true;
                    }
                }

                // Gets the task_id for the task
                query.prepare("SELECT task_id FROM task WHERE description = :description");
                query.bindValue(":description", QString::fromStdString(taskName));
                query.exec();
                while (query.next()) {
                    _taskID = query.value(0).toInt();
                    check = true;
                }
            }
        }
        if(check == false){
            break;
        }
    }

    //Adds robot to the database
    query.exec("SELECT * FROM robots");
    int id = query.size()+1;
    query.prepare("INSERT INTO robots (robot_id, name, current_task)"
                  "VALUES (:id, :name, :taskName)");
    query.bindValue(":id", id);
    query.bindValue(":name", QString::fromStdString(_name));
    query.bindValue(":taskName", _taskID);
    query.exec();
}

//Removes robot from the database
Robot::~Robot() {
    query.prepare("DELETE FROM robots WHERE current_task = :taskID");
    query.bindValue(":taskID", _taskID);
    query.exec();
}

void Robot::doTask(){
    int id;
    // Loops until a task that is being done is entered
    while(1){
        bool check = false;
        std::string taskDone;
        std::cout << "Enter task done: " << std::endl;
        std::getline(std::cin, taskDone);
        std::cout << std::endl;

        // Selects the task_id for the task done
        query.prepare("SELECT task_id FROM task WHERE description = :description");
        query.bindValue(":description", QString::fromStdString(taskDone));
        query.exec();

        while (query.next()) {
            id = query.value(0).toInt();
        }

        // Check if the task is being done
        query.prepare("SELECT current_task FROM robots WHERE current_task = :task_id");
        query.bindValue(":task_id", id);
        query.exec();
        if(query.size() == 0){
            std::cout << "Task not being done" << std::endl;
            check = true;
        }
        if(check == false){
            break;
        }
    }

    // Remove the task from the robot doing the task
    query.prepare("UPDATE robots SET current_task = :new_id WHERE current_task = :task_id");
    query.bindValue(":task_id", id);
    query.bindValue(":new_id", 0);
    query.exec();

    // Remove the task from the database
    query.prepare("DELETE FROM task WHERE task_id = :task_id");
    query.bindValue(":task_id", id);
    query.exec();

    // Decreases the task_id for all tasks with higher number than the removed task
    query.exec("SELECT * FROM task");
    int size = query.size();
    if(id < size){
        query.prepare("SELECT task_id FROM task WHERE task_id > :id");
        query.bindValue(":id", id);
        query.exec();
        int size = query.size();
        for (int i = 0; i < size; ++i) {
            query.prepare("UPDATE task SET task_id = :id WHERE task_id = :task_id");
            query.bindValue(":id", id);
            query.bindValue(":task_id", id+1);
            query.exec();
            id += 1;
        }
    }
}
