#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QWidget>
#include <QFormLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QCalendarWidget>


class Schedule : public QWidget
{
public:
    Schedule(QWidget *parent = nullptr);
    ~Schedule();

private:


    QTableWidget* calendar = new QTableWidget(5,10);

    QHBoxLayout *table = new QHBoxLayout;
    QVector<QPushButton*> dayButtons;

    QTableWidgetItem *monday = new QTableWidgetItem(tr("MONDAY"));
    QTableWidgetItem *tuesday = new QTableWidgetItem(tr("TUESDAY"));
    QTableWidgetItem *wednesday = new QTableWidgetItem(tr("WEDNESDAY"));
    QTableWidgetItem *thursday = new QTableWidgetItem(tr("THURDAY"));
    QTableWidgetItem *friday = new QTableWidgetItem(tr("FRIDAY"));


};

#endif // SCHEDULE_H

