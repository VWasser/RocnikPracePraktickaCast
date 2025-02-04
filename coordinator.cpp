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
        this->myWindow3->onSomething();
    });
}

Coordinator::~Coordinator() {}

void Coordinator::showSignInScreen() {
    myWindow->show();
}


void Coordinator::showMenuWindow() {
    if (!menuWin) {
        menuWin = new ::menuWindow();
        // Next lines are not calling (and it's great, because otherwise we will show the same screens twice)
        QObject::connect(menuWin, &menuWindow::absencePressed, this, [this]() {
            auto coordinator = qobject_cast<Coordinator*>(QObject::sender()->parent());
            coordinator->showAbsenceWindow();
            coordinator->menuWin->hide();
        });
        QObject::connect(menuWin, &menuWindow::gradesPressed, this, [this]() {
            auto coordinator = qobject_cast<Coordinator*>(QObject::sender()->parent());
            coordinator->showGradesWindow();
            coordinator->menuWin->hide();
        });
        QObject::connect(menuWin, &menuWindow::settingsPressed, this, [this]() {
            auto coordinator = qobject_cast<Coordinator*>(QObject::sender()->parent());
            coordinator->showSettingsWindow();
            coordinator->menuWin->hide();
        });
    }
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
