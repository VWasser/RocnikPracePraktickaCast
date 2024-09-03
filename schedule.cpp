#include "schedule.hpp"

Schedule::Schedule(QWidget*parent): QWidget(parent)  {
    calendar->setVisible(true);

    table ->addWidget(calendar);
    setLayout(table);

}

Schedule::~Schedule(){}
