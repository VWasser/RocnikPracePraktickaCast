#include "schedule.hpp"

Schedule::Schedule(QWidget*parent): QWidget(parent)  {
    calendar->setVisible(true);

    table ->addWidget(calendar);
    setLayout(table);

    calendar->setVerticalHeaderItem(0, monday);
    calendar->setVerticalHeaderItem(1, tuesday);
    calendar->setVerticalHeaderItem(2, wednesday);
    calendar->setVerticalHeaderItem(3, thursday);
    calendar->setVerticalHeaderItem(4, friday);

    calendar->setRowHeight(0, 75);
    calendar->setRowHeight(1, 75);
    calendar->setRowHeight(2, 75);
    calendar->setRowHeight(3, 75);
    calendar->setRowHeight(4, 75);

    calendar->setFixedSize(1090,410);

    calendar->setDisabled(true);


}

Schedule::~Schedule(){}
