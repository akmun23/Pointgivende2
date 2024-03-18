#include "robot.h"
#include "qdebug.h"
#include "qsqldatabase.h"
#include "qsqlquery.h"
#include "qsqlrecord.h"
#include <iostream>

Robot::Robot() {}

void Robot::doTask(){
    //Removes task that has been done from the database
    std::string taskDone;
    std::cout << "Enter task done: ";
    std::cin >> taskDone;
    std::cout << std::endl;
    int id;
    query.exec("SELECT * FROM task");
    int size = query.size();


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

    //Decreases the task_id for all tasks with higher number than the removed task
    if(id < size){
        query.prepare("SELECT task_id FROM task WHERE task_id > :id");
        query.bindValue(":id", id);
        query.exec();
        int size = query.size();
        for (int i = 0; i < size; ++i) {
            qDebug() << id;
            query.prepare("UPDATE task SET task_id = :id WHERE task_id = :task_id");
            query.bindValue(":id", id);
            query.bindValue(":task_id", id+1);
            query.exec();
            id += 1;

        }
    }
}
