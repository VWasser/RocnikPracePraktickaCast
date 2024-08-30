#include "schedule.hpp"

schedule::schedule(QWidget*parent): QWidget(parent)  {

    //schedule::setFixedSize(720,180);
    //IDEA -> date could be set in the database and compere it self with time output from program
    //so table could switch automaticaly
    // and the user doesnt have to switch it manualy every week

    for(int i = 0; i < 10; i++){
        table->addWidget(&dayButtons[i]);
    }

    setLayout(table);

}


schedule::~schedule(){}
