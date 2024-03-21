#include "robot.h"
#include "qdebug.h"
#include "qsqldatabase.h"
#include "qsqlquery.h"
#include "qsqlrecord.h"
#include <iostream>

Robot::Robot(std::string name, int taskID):_name(name), _taskID(taskID) {
    //Adds robot to the database
    query.exec("SELECT * from robots");
    int id = query.size()+1;
    query.prepare("INSERT INTO robots (robot_id, name, current_task)"
                  "VALUES (:id, :name, :taskName)");
    query.bindValue(":id", id);
    query.bindValue(":name", QString::fromStdString(_name));
    query.bindValue(":taskName", _taskID);
    query.exec();
}

Robot::~Robot() {
    //Removes robot from the database
    query.prepare("DELETE FROM robots WHERE current_task = :taskID");
    query.bindValue(":taskID", (_taskID));
    query.exec();
}

void Robot::doTask(){
    //Removes task that has been done from the database
    std::string taskDone;
    std::cout << "Enter task done: ";
    std::cin >> taskDone;
    std::cout << std::endl;
    int id;

    // Show the task_id that matches description
    query.prepare("SELECT task_id FROM task WHERE description = :description");
    query.bindValue(":description", QString::fromStdString(taskDone));
    query.exec();

    while (query.next()) {
        id = query.value(0).toInt();
    }

    query.prepare("DELETE FROM task WHERE task_id = :task_id");
    query.bindValue(":task_id", id);
    query.exec();

    query.exec("SELECT * FROM task");
    int size = query.size();
    //Decreases the task_id for all tasks with higher number than the removed task
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
