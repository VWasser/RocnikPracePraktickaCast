#include "schedule.hpp"

Schedule::Schedule(QWidget*parent): QWidget(parent)  {

    //schedule::setFixedSize(720,180);
    //IDEA -> date could be set in the database and compere it self with time output from program
    //so table could switch automaticaly
    // and the user doesnt have to switch it manualy every week

    for(int i = 0; i < 10; i++){
        table->addWidget(new QPushButton(this));
    }

    setLayout(table);

}

Schedule::~Schedule(){}
