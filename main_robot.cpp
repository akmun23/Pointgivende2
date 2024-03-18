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

    Task task;

    task.getTask();
    task.addTask();
    task.getTask();

    return 1;
}
