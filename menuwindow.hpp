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




public:
    QMenuBar *quickAcces = new QMenuBar;

    QMenu *functions = new QMenu(menuWindow::tr("functions"));
    QMenu *options = new QMenu(menuWindow::tr("options"));
    QMenu *languages = new QMenu(menuWindow::tr("languages"));

    QAction *scheduleAction = new QAction(menuWindow::tr("Schedule"), this);
    QAction *absenceAction = new QAction(menuWindow::tr("Absence"), this);
    QAction *gradesAction = new QAction(menuWindow::tr("Grades"), this);
    QAction *menuAction = new QAction(menuWindow::tr("Menu"), this);
    QAction *settingsAction = new QAction(menuWindow::tr("Settings"), this);
    QAction *czLanguageAction = new QAction(menuWindow::tr("Czech"), this);
    QAction *engLanguageAction = new QAction(menuWindow::tr("English"), this);
    QAction *logOutAction = new QAction(menuWindow::tr("LogOut"), this);

public:
    void menuBarStup();
};

#endif // MENUWINDOW_H
