#include "coordinator.hpp"
#include "absencewindow.hpp"
#include "menubar.hpp"
#include <QObject>

Coordinator::Coordinator(QObject *parent) : QObject(parent) {
    signInWindow = new SignInScreen();
    registerWindow = new registerscreen();
    popUpWindow = new settingsWindow();
    gradeWin = new gradesWindow();
    abscWin = new absenceWindow();
    absencePopUp = new inputAbsence();

    windows[Screen::SignIn] = signInWindow;
    windows[Screen::Register] = registerWindow;
    windows[Screen::Settings] = popUpWindow;
    windows[Screen::Absence] = abscWin;
    windows[Screen::Grades] = gradeWin;
    windows[Screen::InputAbsence] = absencePopUp;

    QObject::connect(abscWin.get(), &absenceWindow::scheduleAbsenceOpened, this, &Coordinator::sendScheduleAbsence);
    QObject::connect(scheduleWindow.get(), &Schedule::sendImputAbsenceData, this, &Coordinator::sendImputAbsence);

}

Coordinator::~Coordinator() {}

void Coordinator::showSignInScreen() {
    hideAllScreens(Screen::SignIn);
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

void Coordinator::showInputAbsence(QSharedPointer<InputAbsenceData> data) {
    hideAllScreens(Screen::InputAbsence, data);
}

void Coordinator::showRegisterScreen() {
    hideAllScreens(Screen::Register);
}

void Coordinator::showSettingsWindow() {
    hideAllScreens(Screen::Settings);
}

void Coordinator::showSchedule() {
    if (!scheduleWindow) {
        scheduleWindow = new Schedule();
        windows[Screen::Schedule] = scheduleWindow;
    }
    hideAllScreens(Screen::Schedule);
}

void Coordinator::hideAllScreens(Screen exeption, QSharedPointer<ShowBasicData> data){
    for(auto i = windows.begin(); i != windows.end(); ++i ){
        if(i.key() == exeption){
            i.value()->show();
            i.value()->configure(data);
            qDebug() << "SHOWING" << &i.key();
        }else if(i.key() != exeption){
            i.value()->hide();
            qDebug()<<  "HIDING" << &i.key();
        }
    }
}
void Coordinator::implementMenuBar(QBoxLayout *layout){
    auto bar = new menuBar();
    bar->menuBarStup(layout);
}
absenceTypes Coordinator::getAbsenceType(int abscType) const{
    //will eventualy add some functions just dont have the idea of exactly what
    switch(abscType){
    case (0):
        return absenceTypes::OK;
        break;
    case (1):
        return absenceTypes::UNSOLVED;
        break;
    case (2):
        return absenceTypes::MISSED;
        break;
    case (3):
        return absenceTypes::LATE;
        break;
    case (4):
        return absenceTypes::SCHOOL;
        break;
    }
}
