#include "menuwindow.hpp"
#include "schedule.hpp"
#include "signinscreen.hpp"
#include <QGridLayout>
#include <QMenuBar>
#include <QAction>


menuWindow::menuWindow(QWidget*parent): QWidget(parent)  {

    QObject::connect(gradesButton, &QPushButton::clicked, this, [&](){
        gradeWin->show();
        hide();
    });
    QObject::connect(absenceButton, &QPushButton::clicked, this, [&](){
        abscWin->show();
        hide();

    });
    QObject::connect(scheduleButton, &QPushButton::clicked, this, [&](){
        myWindow3->show();
        hide();

    });
    QObject::connect(settingsButton, &QPushButton::clicked, this, [&](){
        popUpWindow->show();
        hide();

    });

    row1->addWidget(scheduleButton);
    row1->addWidget(gradesButton);
    row2->addWidget(absenceButton);
    mainLayout->addWidget(quickAcces);
    mainLayout->addLayout(row1);
    mainLayout->addLayout(row2);

    menuBarStup();

    setLayout(mainLayout);
}

void menuWindow::menuBarStup(){

    //QMenuBar Actions
    QObject::connect(scheduleAction, &QAction::triggered, this, [&](){
        myWindow3->show();
        hide();

    });
    QObject::connect(gradesAction, &QAction::triggered, this, [&](){
        gradeWin->show();
        hide();

    });
    QObject::connect(absenceAction, &QAction::triggered, this, [&](){
        abscWin->show();
        hide();

    });
    QObject::connect(settingsAction, &QAction::triggered, this, [&](){
        //not yet made
        popUpWindow->show();
        hide();

    });
    QObject::connect(czLanguageAction, &QAction::triggered, this, [&](){


    });
    QObject::connect(engLanguageAction, &QAction::triggered, this, [&](){

    });
    QObject::connect(logOutAction, &QAction::triggered, this, [&](){
        myWindow->show();
        hide();

    });

    quickAcces->addMenu(functions);
    quickAcces->addMenu(options);

    functions->addAction(scheduleAction);
    functions->addAction(absenceAction);
    functions->addAction(gradesAction);
    functions->addAction(menuAction);


    languages->addAction(czLanguageAction);
    languages->addAction(engLanguageAction);

    options->addMenu(languages);
    options->addAction(settingsAction);
}

menuWindow::~menuWindow(){};
