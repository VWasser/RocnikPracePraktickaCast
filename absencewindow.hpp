#ifndef ABSENCEWINDOW_HPP
#define ABSENCEWINDOW_HPP

#include "qlabel.h"
#include "qpushbutton.h"
#include "qtablewidget.h"
#include "schedule.hpp"
#include <QWidget>
#include <QBoxLayout>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "screenwidget.hpp"

struct AbsenceItem {
    QString userId;
    int absenceMonth;
    int absenceDay;
    int absenceHour;

    AbsenceItem(QJsonObject lessonObject) {
        userId = lessonObject["UserID"].toString();
        absenceMonth = lessonObject["AbsenceMonth"].toInteger();
        absenceDay = lessonObject["AbsenceDay"].toInteger();
        absenceHour = lessonObject["AbsenceHour"].toInteger();
    }
};

class absenceWindow : public ScreenWidget
{
    Q_OBJECT
public:
    absenceWindow(QWidget *parent = nullptr);
    ~absenceWindow();
    void configure(QSharedPointer<ShowBasicData>) override;

signals:
    void scheduleAbsenceOpened();

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

private:
    QList<AbsenceItem> cachedItems;
};


#endif // ABSENCEBUTTON_HPP
