#include "coordinator.hpp"
#include "absencewindow.hpp"
#include <QObject>

Coordinator::Coordinator(QObject *parent) : QObject(parent) {
    myWindow = new SignInScreen();
    myWindow2 = new registerscreen();
    popUpWindow = new settingsWindow();
    gradeWin = new gradesWindow();
    abscWin = new absenceWindow();
    absencePopUp = new inputAbsence();

    QObject::connect(abscWin, &absenceWindow::scheduleAbsenceOpened, this, &Coordinator::sendScheduleAbsence);
}

Coordinator::~Coordinator() {}

void Coordinator::showSignInScreen() {
    myWindow->show();
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
    myWindow2->show();
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
    if (!myWindow3) {
        myWindow3 = new Schedule();
    }
    myWindow3->show();
}
