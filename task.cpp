#include "task.h"
#include "qdebug.h"
#include "qsqldatabase.h"
#include "qsqlquery.h"
#include "qsqlrecord.h"
#include <iostream>

Task::Task() {
}

void Task::getTask() {
    //Prints tasks
    qDebug() << "Tasks: ";
    query.exec("SELECT description FROM task");
    while (query.next()) {
        qDebug() << query.value(0).toString();
    }
    std::cout << std::endl;
}

void Task::addTask() {
    //Adds a task
    std::string task;
    int time;

    query.exec("SELECT * FROM task");
    int task_id = query.size();

    std::cout << "Enter task: ";
    std::cin >> task;
    std::cout << "Enter time: ";
    std::cin >> time;

    query.prepare("INSERT INTO task (task_id, description, time)"
                  "VALUES (:task_id, :description, :time)");
    query.bindValue(":task_id", task_id+1);
    query.bindValue(":description", QString::fromStdString(task));
    query.bindValue(":time", time);
    query.exec();

    std::cout << "Task added" << std::endl;
    std::cout << std::endl;
}
