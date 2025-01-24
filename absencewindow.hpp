#ifndef ABSENCEWINDOW_HPP
#define ABSENCEWINDOW_HPP

#include "addabsencewindow.hpp"
#include "qlabel.h"
#include "qpushbutton.h"
#include <QWidget>
#include <QBoxLayout>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

extern addAbsenceWindow *addAbscPopUpWin;

struct AbsenceItem {
    QString userId;
    unsigned long absenceDate;

    AbsenceItem(QJsonObject lessonObject) {
        userId = lessonObject["UserID"].toString();
        absenceDate = lessonObject["AbsenceDate"].toInteger();
    }
};

class absenceWindow : public QWidget
{
    Q_OBJECT
public:
    absenceWindow(QWidget *parent = nullptr);
    ~absenceWindow();

private:
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QVBoxLayout *absenceDaily = new QVBoxLayout;

    QHBoxLayout *popisky = new QHBoxLayout;

    QLabel *date = new QLabel(absenceWindow::tr("date"));
    QLabel *ok = new QLabel(absenceWindow::tr("Ok"));
    QLabel *unsolved = new QLabel(absenceWindow::tr("Unsolved"));
    QLabel *missed = new QLabel(absenceWindow::tr("Missed"));
    QLabel *late = new QLabel(absenceWindow::tr("Late"));
    QLabel *school = new QLabel(absenceWindow::tr("School"));

    QPushButton *addAbsence = new QPushButton;

private:
    QList<AbsenceItem> cachedItems;
};


#endif // ABSENCEBUTTON_HPP
