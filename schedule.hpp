#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "qlabel.h"
#include <QWidget>
#include <QFormLayout>
#include <QPushButton>

class schedule : public QWidget
{
public:
    schedule(QWidget *parent = nullptr);
    ~schedule();

private:
    QVBoxLayout scheduleTable;

    QHBoxLayout mondayRow;
    QHBoxLayout tuesdayRow;
    QHBoxLayout wednesdayRow;
    QHBoxLayout thursdayRow;
    QHBoxLayout fridayRow;


    QLabel MONDAY;
    QLabel TUESDAY;
    QLabel WEDNESDAY;
    QLabel THURSDAY;
    QLabel FRIDAY;

    QMap<int, QPushButton>tableButtons;
};

#endif // SCHEDULE_H
