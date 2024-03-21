#include "robot.h"
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
    Robot robot("R2D2", 2);
    Robot robot2("C3P0", 2);

    std::string input;

    std::cout << "Welcome to the robot worker" << std::endl;
    std::cout << "Commands: add, get, do, exit" << std::endl;
    std::cout << "Type help for commands" << "\n" << std::endl;


    while(1){
        std::cin >> input;
        input[0] = tolower(input[0]);
        if(input == "exit"){
            break;
        } else if(input == "add"){
            task.addTask();
            continue;
        } else if(input == "get"){
            task.getTask();
            continue;
        } else if(input == "do"){
            robot.doTask();
            continue;
        } else if(input == "help"){
            std::cout << "Commands: add, get, do, exit" << std::endl;
            continue;
        }
    }

    return 1;
}
