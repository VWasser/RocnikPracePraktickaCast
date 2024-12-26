#ifndef ABSENCEWINDOW_HPP
#define ABSENCEWINDOW_HPP

#include "addabsencewindow.hpp"
#include "qlabel.h"
#include "qpushbutton.h"
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
    QVBoxLayout *absenceDaily = new QVBoxLayout;

    QHBoxLayout *popisky = new QHBoxLayout;

    QLabel *date = new QLabel(absenceWindow::tr("date"));
    QLabel *ok = new QLabel(absenceWindow::tr("Ok"));
    QLabel *unsolved = new QLabel(absenceWindow::tr("Unsolved"));
    QLabel *missed = new QLabel(absenceWindow::tr("Missed"));
    QLabel *late = new QLabel(absenceWindow::tr("Late"));
    QLabel *school = new QLabel(absenceWindow::tr("School"));

    QPushButton *addAbsence = new QPushButton;
};


#endif // ABSENCEBUTTON_HPP
