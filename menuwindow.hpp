#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include "absencebutton.hpp"
#include "gradeswindow.hpp"
#include "qpushbutton.h"
#include "schedule.hpp"
#include <QWidget>
#include <QGridLayout>
#include <QMenuBar>

extern Schedule* myWindow3;
extern gradesWindow* gradeWin;
extern absenceWindow* abscWin;

class menuWindow : public QWidget
{
    Q_OBJECT
public:
    menuWindow(QWidget *parent = nullptr);
    ~menuWindow();


private:
    QGridLayout *mainLayout = new QGridLayout;
    QPushButton *scheduleButton = new QPushButton;
    QPushButton *absenceButton = new QPushButton;
    QPushButton *gradesButton = new QPushButton;
    QPushButton *settingsButton = new QPushButton;
    QPushButton *LanguageButton = new QPushButton;


private:
    void onClickScheduleButton();
    void onClickGradesButton();
    void onClickAbsenceButton();
    void onClickSettingsButton();
    void onClickLanguageButton();
public:
    QMenuBar *quickAcces = new QMenuBar;

};

#endif // MENUWINDOW_H
