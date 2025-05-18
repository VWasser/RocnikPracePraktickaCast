#ifndef ABSENCEWINDOW_HPP
#define ABSENCEWINDOW_HPP

#include "schedule.hpp"
#include <QTableWidget>
#include <QPushButton>
#include <QWidget>
#include <QBoxLayout>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "screenwidget.hpp"

enum absenceTypes {
    OK = 0,
    UNSOLVED,
    MISSED,
    LATE,
    SCHOOL,
    COUNT
};

struct AbsenceItem {
    QString userId;
    int absenceMonth;
    int absenceDay;
    int absenceHour;
    absenceTypes kind;

    AbsenceItem(QJsonObject object) {
        userId = object["UserID"].toString();
        absenceMonth = object["AbsenceMonth"].toInteger();
        absenceDay = object["AbsenceDay"].toInteger();
        absenceHour = object["AbsenceHour"].toInteger();
        kind = static_cast<absenceTypes>(object["Kind"].toInteger());
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
    int ammountOfDays;

    //will later be added as a verticalHeaderItem to the
    //absence adding function
    QString dateOfAbsence = "DD:MM";

    QPushButton *addAbsence = new QPushButton;

private:
    QList<AbsenceItem> cachedItems;
};


#endif // ABSENCEBUTTON_HPP
