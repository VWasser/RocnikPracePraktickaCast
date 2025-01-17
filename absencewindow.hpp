#ifndef ABSENCEWINDOW_HPP
#define ABSENCEWINDOW_HPP

#include "addabsencewindow.hpp"
#include "qlabel.h"
#include "qpushbutton.h"
#include "qtablewidget.h"
#include <QWidget>
#include <QBoxLayout>

extern addAbsenceWindow *addAbscPopUpWin;


class absenceWindow : public QWidget
{
    Q_OBJECT
public:
    absenceWindow(QWidget *parent = nullptr);
    ~absenceWindow();

private:
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QTableWidget *absenceLayout = new QTableWidget;

    QTableWidgetItem *date = new QTableWidgetItem(absenceWindow::tr("date"));
    QTableWidgetItem *ok = new QTableWidgetItem(absenceWindow::tr("Ok"));
    QTableWidgetItem *unsolved = new QTableWidgetItem(absenceWindow::tr("Unsolved"));
    QTableWidgetItem *missed = new QTableWidgetItem(absenceWindow::tr("Missed"));
    QTableWidgetItem *late = new QTableWidgetItem(absenceWindow::tr("Late"));
    QTableWidgetItem *school = new QTableWidgetItem(absenceWindow::tr("School"));

    //when functional the vaiable will be = 0 but for now ill sett it
    //to random number
    int ammountOfDays = 6;

    //will later be added as a verticalHeaderItem to the
    //absence adding function
    QString dateOfAbsence = "DD:MM";

    QPushButton *addAbsence = new QPushButton;
};


#endif // ABSENCEBUTTON_HPP
