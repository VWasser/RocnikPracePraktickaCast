#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include "absencewindow.hpp"
#include "gradeswindow.hpp"
#include "qpushbutton.h"
#include "schedule.hpp"
#include "signinscreen.hpp"
#include "settingsWindow.hpp"
#include <QWidget>
#include <QGridLayout>
#include <QMenuBar>

extern Schedule* myWindow3;
extern gradesWindow* gradeWin;
extern absenceWindow* abscWin;
extern SignInScreen* myWindow;
extern settingsWindow* popUpWindow;

class menuWindow : public QWidget
{
    Q_OBJECT
public:
    menuWindow(QWidget *parent = nullptr);
    ~menuWindow();


private:
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *row1 = new QHBoxLayout;
    QHBoxLayout *row2 = new QHBoxLayout;

    QPushButton *scheduleButton = new QPushButton(menuWindow::tr("Schedule"));
    QPushButton *absenceButton = new QPushButton(menuWindow::tr("Grades"));
    QPushButton *gradesButton = new QPushButton(menuWindow::tr("Absence"));
    QPushButton *settingsButton = new QPushButton;
    QPushButton *LanguageButton = new QPushButton;

};

#endif // MENUWINDOW_H
