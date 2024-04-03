#ifndef ROBOT_H
#define ROBOT_H
#include "qsqlquery.h"
#include "task.h"

class Robot{
    QSqlQuery query;
    std::string _name;
    int _taskID;
    Task task;
public:
    Robot();
    Robot(std::string name, int taskID);
    void init(std::string name, int taskID);
    ~Robot();
    void doTask();
};

#endif // ROBOT_HS
