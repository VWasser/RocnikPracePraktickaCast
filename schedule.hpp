#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QWidget>
#include <QFormLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>

class schedule : public QWidget
{
public:
    schedule(QWidget *parent = nullptr);
    ~schedule();

private:



    QHBoxLayout *table = new QHBoxLayout;
    QVector<QPushButton>dayButtons;

};

#endif // SCHEDULE_H
