#ifndef ROBOT_H
#define ROBOT_H
#include "qsqlquery.h"

class Robot{
    QSqlQuery query;
public:
    Robot();
    void doTask();
};

#endif // ROBOT_H
