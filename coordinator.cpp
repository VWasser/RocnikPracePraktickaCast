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

    QObject::connect(abscWin, &absenceWindow::scheduleAbsenceOpened, this, [&](){
        emit sendScheduleAbsence();
    });
}

Coordinator::~Coordinator() {}

void Coordinator::showSignInScreen() {
    myWindow->show();
}


void Coordinator::showMenuWindow() {
    if (!menuWin) {
        menuWin = new ::menuWindow();
        QObject::connect(menuWin, &menuWindow::absencePressed, this, [this]() {
            auto coordinator = static_cast<Coordinator*>(QObject::sender()->parent());
            coordinator->showAbsenceWindow();
            coordinator->menuWin->hide();
        });
        QObject::connect(menuWin, &menuWindow::gradesPressed, this, [this]() {
            auto coordinator = static_cast<Coordinator*>(QObject::sender()->parent());
            coordinator->showGradesWindow();
            coordinator->menuWin->hide();
        });
        QObject::connect(menuWin, &menuWindow::settingsPressed, this, [this]() {
            auto coordinator = static_cast<Coordinator*>(QObject::sender()->parent());
            coordinator->showSettingsWindow();
            coordinator->menuWin->hide();
        });
    }
    menuWin->show();
}

void Coordinator::showAbsenceWindow() {
    abscWin->show();
}

void Coordinator::showGradesWindow() {
    gradeWin->show();
}

void Coordinator::showInputAbsence() {
    absencePopUp->show();
}

void Coordinator::showRegisterScreen() {
    myWindow2->show();
}

void Coordinator::showSettingsWindow() {
    popUpWindow->show();
}

void Coordinator::showSchedule() {
    myWindow3->show();
}
