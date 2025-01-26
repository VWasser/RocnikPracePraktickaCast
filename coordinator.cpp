#include "coordinator.hpp"
#include "BackendlessQt/StandardNetworkManager.hpp"
#include "httpclient.hpp"


Coordinator::Coordinator(QObject *parent) : QObject(parent) {

}

Coordinator::~Coordinator() {}

void Coordinator::showSignInScreen() {
    /*if (!signInScreen) {
        signInScreen = new SignInScreen();
        QObject::connect(signInScreen, &SignInScreen::goToMenu, this, []() {
            auto coordinator = static_cast<Coordinator*>(QObject::sender()->parent());
            coordinator->showMenuWindow();
            coordinator->signInScreen->hide();
        });
    }*/
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
    /*if (!absenceWindow) {
        absenceWindow = new ::absenceWindow();
        QObject::connect(absenceWindow, &AbsenceWindow::goBackToMenu, this, [this]() {
            auto coordinator = static_cast<Coordinator*>(QObject::sender()->parent());
            coordinator->showMenuWindow();
            coordinator->absenceWindow->hide();
        });
    }*/
    abscWin->show();
}

void Coordinator::showGradesWindow() {
    /*if (!gradesWindow) {
        gradesWindow = new GradesWindow();
        QObject::connect(gradesWindow, &GradesWindow::goBackToMenu, this, []() {
            auto coordinator = static_cast<Coordinator*>(QObject::sender()->parent());
            coordinator->showMenuWindow();
            coordinator->gradesWindow->hide();
        });
    }*/
    gradeWin->show();
}

void Coordinator::showInputAbsence() {
    /*if (!inputAbsence) {
        inputAbsence = new InputAbsence();
        QObject::connect(inputAbsence, &InputAbsence::goBackToAbsence, this, []() {
            auto coordinator = static_cast<Coordinator*>(QObject::sender()->parent());
            coordinator->showAbsenceWindow();
            coordinator->inputAbsence->hide();
        });
    }*/
    absencePopUp->show();
}

void Coordinator::showRegisterScreen() {
    /*if (!registerScreen) {
        registerScreen = new RegisterScreen();
        QObject::connect(registerScreen, &RegisterScreen::goBackToSignIn, this, []() {
            auto coordinator = static_cast<Coordinator*>(QObject::sender()->parent());
            coordinator->showSignInScreen();
            coordinator->registerScreen->hide();
        });
    }*/
    myWindow2->show();
}

void Coordinator::showSettingsWindow() {
    /*if (!settingsWindow) {
        settingsWindow = new SettingsWindow();
        QObject::connect(settingsWindow, &SettingsWindow::goBackToMenu, this, []() {
            auto coordinator = static_cast<Coordinator*>(QObject::sender()->parent());
            coordinator->showMenuWindow();
            coordinator->settingsWindow->hide();
        });
    }*/
    popUpWindow->show();
}

void Coordinator::showSchedule() {
    /*if (!schedule) {
        schedule = new Schedule();
        QObject::connect(schedule, &Schedule::goBackToMenu, this, []() {
            auto coordinator = static_cast<Coordinator*>(QObject::sender()->parent());
            coordinator->showMenuWindow();
            coordinator->schedule->hide();
        });
    }*/
    myWindow3->show();
}
