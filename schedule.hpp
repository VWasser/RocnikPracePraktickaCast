#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QWidget>
#include <QFormLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>

class Schedule : public QWidget
{
public:
    Schedule(QWidget *parent = nullptr);
    ~Schedule();

private:



    QHBoxLayout *table = new QHBoxLayout;
    QVector<QPushButton*> dayButtons;

};

#endif // SCHEDULE_H
