#ifndef ROBOT_H
#define ROBOT_H
#include "qsqlquery.h"

class Robot{
    QSqlQuery query;
    std::string _name;
    std::string _taskName;
public:
    Robot(std::string name, std::string taskName);
    ~Robot();
    void doTask();
};

#endif // ROBOT_HS
