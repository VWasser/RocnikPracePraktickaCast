#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QWidget>
#include <QFormLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QCalendarWidget>
#include "BackendlessQt/BackendlessAPI.hpp"
#include "editmodescreen.hpp"
#include "qlabel.h"
#include "qlineedit.h"
#include <ctime>

extern BackendlessAPI* api;
extern editModeScreen* popUpWindow;

class Schedule : public QWidget
{
    Q_OBJECT

public:
    Schedule(QWidget *parent = nullptr);
    ~Schedule();    

private:


    QTableWidget* calendar = new QTableWidget(5,10);

    QPushButton* editMode = new QPushButton;
    QVBoxLayout *table = new QVBoxLayout;
    QHBoxLayout *dateLay = new QHBoxLayout;
    QVector<QPushButton*> dayButtons;

    QLabel* date = new QLabel;
    time_t timestamp;

    QTableWidgetItem *monday = new QTableWidgetItem(tr("Monday"));
    QTableWidgetItem *tuesday = new QTableWidgetItem(tr("Tuesday"));
    QTableWidgetItem *wednesday = new QTableWidgetItem(tr("Wednesday"));
    QTableWidgetItem *thursday = new QTableWidgetItem(tr("Thursday"));
    QTableWidgetItem *friday = new QTableWidgetItem(tr("Friday"));


    QTableWidgetItem *zero = new QTableWidgetItem(tr("7:55 - 8:40"));
    QTableWidgetItem *one = new QTableWidgetItem(tr("8:45 - 9:30"));
    QTableWidgetItem *two = new QTableWidgetItem(tr("9:40 - 10:25"));
    QTableWidgetItem *three = new QTableWidgetItem(tr("10:50 - 11:35"));
    QTableWidgetItem *four = new QTableWidgetItem(tr("11:45 - 12:30"));
    QTableWidgetItem *five = new QTableWidgetItem(tr("12:40 - 13:25"));
    QTableWidgetItem *six = new QTableWidgetItem(tr("13:30 - 14:15"));
    QTableWidgetItem *seven = new QTableWidgetItem(tr("14:20 - 15:05"));
    QTableWidgetItem *eight = new QTableWidgetItem(tr("15:10 - 15:55"));
    QTableWidgetItem *nine = new QTableWidgetItem(tr("16:00 - 16:45"));


};

#endif // SCHEDULE_H

