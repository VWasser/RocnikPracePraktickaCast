#include "menuwindow.hpp"
#include <QGridLayout>

menuWindow::menuWindow(QWidget*parent): QWidget(parent)  {

    mainLayout->addWidget(scheduleButton);
    QObject::connect(gradesButton, &QPushButton::clicked, this, [&](){
        myWindow3->show();
        hide();
    });
    QObject::connect(absenceButton, &QPushButton::clicked, this, [&](){
        abscWin->show();
    });
    QObject::connect(scheduleButton, &QPushButton::clicked, this, [&](){
        gradeWin->show();
    });
    QObject::connect(settingsButton, &QPushButton::clicked, this, [&](){
        popUpWindow->show();
    });

    mainLayout->addWidget(gradesButton);
    mainLayout->addWidget(scheduleButton);
    mainLayout->addWidget(absenceButton);
    mainLayout->addWidget(settingsButton);
    setLayout(mainLayout);

}


menuWindow::~menuWindow(){};

