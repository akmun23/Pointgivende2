#ifndef TASK_H
#define TASK_H
#include "qsqlquery.h"

class Task{

    QSqlQuery query;

public:
    Task();
    void getTask();
    void addTask();
};

#endif // TASK_H
