#include "menuwindow.hpp"
#include "schedule.hpp"
#include "signinscreen.hpp"
#include <QGridLayout>
#include <QMenuBar>
#include <QAction>
#include "menubar.hpp"



menuWindow::menuWindow(QWidget*parent): QWidget(parent)  {

    QObject::connect(gradesButton, &QPushButton::clicked, this, [&](){
        emit gradesPressed();
        coordinator->showGradesWindow();
        hide();
    });
    QObject::connect(absenceButton, &QPushButton::clicked, this, [&](){
        emit absencePressed();
        abscWin->show();
        hide();

    });
    QObject::connect(scheduleButton, &QPushButton::clicked, this, [&](){
        emit schedulePressed();
        myWindow3->show();
        hide();

    });
    QObject::connect(settingsButton, &QPushButton::clicked, this, [&](){
        emit settingsPressed();
        popUpWindow->show();
        hide();

    });

    row1->addWidget(scheduleButton);
    row1->addWidget(gradesButton);
    row2->addWidget(absenceButton);
    auto bar = new menuBar();
    bar->menuBarStup(mainLayout);
    mainLayout->addLayout(row1);
    mainLayout->addLayout(row2);
    setLayout(mainLayout);
}



menuWindow::~menuWindow(){};
