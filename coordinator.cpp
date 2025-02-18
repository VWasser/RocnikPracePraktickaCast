#include "coordinator.hpp"
#include "absencewindow.hpp"
#include <QObject>

Coordinator::Coordinator(QObject *parent) : QObject(parent) {
    signInWindow = new SignInScreen();
    registerWindow = new registerscreen();
    popUpWindow = new settingsWindow();
    gradeWin = new gradesWindow();
    abscWin = new absenceWindow();
    //abscWin = QSharedPointer<absenceWindow>(new absenceWindow, &QObject::deleteLater);
    absencePopUp = new inputAbsence();

    windows[Screen::SignIn] = signInWindow;
    windows[Screen::Register] = registerWindow;
    windows[Screen::Settings] = popUpWindow;
    windows[Screen::Absence] = abscWin;
    windows[Screen::Grades] = gradeWin;
    windows[Screen::InputAbsence] = absencePopUp;

    QObject::connect(abscWin.get(), &absenceWindow::scheduleAbsenceOpened, this, &Coordinator::sendScheduleAbsence);
}

Coordinator::~Coordinator() {}

void Coordinator::showSignInScreen() {
    signInWindow->show();
}


void Coordinator::showMenuWindow() {
    if (!menuWin) {
        menuWin = new menuWindow();
        windows[Screen::Menu] = menuWin;
    }
    hideAllScreens(Screen::Menu);
}

void Coordinator::showAbsenceWindow() {
    hideAllScreens(Screen::Absence);
}

void Coordinator::showGradesWindow() {
    hideAllScreens(Screen::Grades);
}

void Coordinator::showInputAbsence() {
    hideAllScreens(Screen::InputAbsence);
}

void Coordinator::showRegisterScreen() {
    registerWindow->show();
}

void Coordinator::showSettingsWindow() {
    menuWin->hide();
    popUpWindow->show();
}

void Coordinator::showSchedule() {
    abscWin->hide();
    absencePopUp->hide();
    //menuWin->hide();
    //menuWin->deleteLater();
    //menuWin = nullptr;
    if (!scheduleWindow) {
        scheduleWindow = new Schedule();
        windows[Screen::Schedule] = scheduleWindow;
    }
    hideAllScreens(Screen::Schedule);
}
void Coordinator::hideAllScreens(Screen exeption){
    for(auto i = windows.begin(); i != windows.end(); ++i ){
        if(i.key() == exeption){
            i.value()->show();
            qDebug() << "SHOWING" << &i.key();
        }else if(i.key() != exeption){
            i.value()->hide();
            qDebug()<<  "HIDING" << &i.key();
        }
    }
}
