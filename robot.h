#ifndef ROBOT_H
#define ROBOT_H
#include "qsqlquery.h"

class Robot{
    QSqlQuery query;
    std::string _name;
    int _taskID;
public:
    Robot(std::string name, int taskID);
    ~Robot();
    void doTask();
};

#endif // ROBOT_HS
