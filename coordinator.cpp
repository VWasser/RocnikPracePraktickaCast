#include "coordinator.hpp"
#include "absencewindow.hpp"
#include <QObject>

Coordinator::Coordinator(QObject *parent) : QObject(parent) {
    myWindow = new SignInScreen();
    myWindow2 = new registerscreen();
    myWindow3 = new Schedule();
    popUpWindow = new settingsWindow();
    menuWin = new menuWindow();
    gradeWin = new gradesWindow();
    abscWin = new absenceWindow();
    absencePopUp = new inputAbsence();

    QObject::connect(abscWin, &absenceWindow::scheduleAbsenceOpened, this, &Coordinator::sendScheduleAbsence);

    QObject::connect(this, &Coordinator::sendScheduleAbsence, myWindow3, [&](){
        myWindow3->onSomething();
    });
}

Coordinator::~Coordinator() {}

void Coordinator::showSignInScreen() {
    myWindow->show();
}


void Coordinator::showMenuWindow() {
    menuWin->show();
}

void Coordinator::showAbsenceWindow() {
    menuWin->hide();
    abscWin->show();
}

void Coordinator::showGradesWindow() {
    menuWin->hide();
    gradeWin->show();
}

void Coordinator::showInputAbsence() {
    absencePopUp->show();
}

void Coordinator::showRegisterScreen() {
    myWindow2->show();
}

void Coordinator::showSettingsWindow() {
    menuWin->hide();
    popUpWindow->show();
}

void Coordinator::showSchedule() {
    absencePopUp->hide();
    menuWin->hide();
    myWindow3->show();
}
