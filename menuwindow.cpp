#include "menuwindow.hpp"
#include <QGridLayout>
#include <QMenuBar>
#include <QAction>
#include "menubar.hpp"
#include "coordinator.hpp"

extern Coordinator* coordinator;

menuWindow::menuWindow(QWidget*parent): ScreenWidget(parent)  {

    QObject::connect(gradesButton, &QPushButton::clicked, this, [&](){
        emit gradesPressed();
        coordinator->showGradesWindow();
    });
    QObject::connect(absenceButton, &QPushButton::clicked, this, [&](){
        emit absencePressed();
        coordinator->showAbsenceWindow();
    });
    QObject::connect(scheduleButton, &QPushButton::clicked, this, [&](){
        emit schedulePressed();
        coordinator->showSchedule();
    });
    QObject::connect(settingsButton, &QPushButton::clicked, this, [&](){
        emit settingsPressed();
        coordinator->showSettingsWindow();
    });

    row1->addWidget(scheduleButton);
    row1->addWidget(gradesButton);
    row2->addWidget(absenceButton);
    coordinator->implementMenuBar(mainLayout);
    //auto bar = new menuBar();
    //bar->menuBarStup(mainLayout);
    mainLayout->addLayout(row1);
    mainLayout->addLayout(row2);
    setLayout(mainLayout);
}

menuWindow::~menuWindow(){};

void menuWindow::configure(QSharedPointer<ShowBasicData>) {

}
