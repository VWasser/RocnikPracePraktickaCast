#include "coordinator.hpp"
#include "absencewindow.hpp"
#include <QObject>

Coordinator::Coordinator(QObject *parent) : QObject(parent) {
    signInWindow = new SignInScreen();
    registerWindow = new registerscreen();
    popUpWindow = new settingsWindow();
    gradeWin = new gradesWindow();
    abscWin = new absenceWindow();
    absencePopUp = new inputAbsence();

    QObject::connect(abscWin, &absenceWindow::scheduleAbsenceOpened, this, &Coordinator::sendScheduleAbsence);
}

Coordinator::~Coordinator() {}

void Coordinator::showSignInScreen() {
    signInWindow->show();
}


void Coordinator::showMenuWindow() {
    if (!menuWin) {
        menuWin = new menuWindow();
    }
    menuWin->show();
}

void Coordinator::showAbsenceWindow() {
    menuWin->hide();
    //menuWin->deleteLater();
    //menuWin = nullptr;
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
    registerWindow->show();
}

void Coordinator::showSettingsWindow() {
    menuWin->hide();
    popUpWindow->show();
}

void Coordinator::showSchedule() {
    abscWin->hide();
    absencePopUp->hide();
    hideAllScreenExcept();
    //menuWin->hide();
    //menuWin->deleteLater();
    //menuWin = nullptr;
    if (!scheduleWindow) {
        scheduleWindow = new Schedule();
    }
    scheduleWindow->show();
}
