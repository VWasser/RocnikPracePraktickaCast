#include "schedule.hpp"

schedule::schedule(QWidget(*parent)): QWidget(parent), scheduleTable(this) {

    schedule::setFixedSize(1200, 700);
    MONDAY.setText("MONDAY");
    TUESDAY.setText("TUESDAY");
    WEDNESDAY.setText("WEDNESDAY");
    THURSDAY.setText("THURSDAY");
    FRIDAY.setText("FRIDAY");

    //IDEA -> date could be set in the database and compere it self with time output from program
    //so table could switch automaticaly
    // and the user doesnt have to switch it manualy every week

    mondayRow.addWidget(&MONDAY);

    tuesdayRow.addWidget(&TUESDAY);

    wednesdayRow.addWidget(&WEDNESDAY);

    thursdayRow.addWidget(&THURSDAY);

    fridayRow.addWidget(&FRIDAY);

    scheduleTable.addLayout(&mondayRow);
    scheduleTable.addLayout(&tuesdayRow);
    scheduleTable.addLayout(&wednesdayRow);
    scheduleTable.addLayout(&thursdayRow);
    scheduleTable.addLayout(&fridayRow);

    setLayout(&scheduleTable);

}


schedule::~schedule(){}
