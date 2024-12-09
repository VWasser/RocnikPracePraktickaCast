#ifndef MENUBAR_HPP
#define MENUBAR_HPP

#include "absencewindow.hpp"
#include "gradeswindow.hpp"
#include "qboxlayout.h"
#include "schedule.hpp"
#include "settingsWindow.hpp"
#include "signinscreen.hpp"
#include <QMenuBar>

extern Schedule* myWindow3;
extern gradesWindow* gradeWin;
extern absenceWindow* abscWin;
extern settingsWindow* popUpWindow;
extern SignInScreen* myWindow;

class menuBar : public QMenuBar
{
    Q_OBJECT
public:
    menuBar();
    ~menuBar();

public:
    QMenuBar *quickAcces = new QMenuBar;

    QMenu *functions = new QMenu(menuBar::tr("functions"));
    QMenu *options = new QMenu(menuBar::tr("options"));
    QMenu *languages = new QMenu(menuBar::tr("languages"));

    QAction *scheduleAction = new QAction(menuBar::tr("Schedule"), this);
    QAction *absenceAction = new QAction(menuBar::tr("Absence"), this);
    QAction *gradesAction = new QAction(menuBar::tr("Grades"), this);
    QAction *menuAction = new QAction(menuBar::tr("Menu"), this);
    QAction *settingsAction = new QAction(menuBar::tr("Settings"), this);
    QAction *czLanguageAction = new QAction(menuBar::tr("Czech"), this);
    QAction *engLanguageAction = new QAction(menuBar::tr("English"), this);
    QAction *logOutAction = new QAction(menuBar::tr("LogOut"), this);

public:
    void menuBarStup(QBoxLayout *layout);

};

#endif // MENUBAR_HPP
