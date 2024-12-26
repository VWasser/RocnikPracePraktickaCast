#include "absencewindow.hpp"

absenceWindow::absenceWindow(QWidget *parent): QWidget(parent) {
    QObject::connect(addAbsence, &QPushButton::clicked, this, [&](){
        addAbscPopUpWin->show();
        hide();
    });
    mainLayout->addLayout(popisky);
    mainLayout->addLayout(absenceDaily);
    mainLayout->addWidget(addAbsence);

    popisky->addWidget(date);
    popisky->addWidget(ok);
    popisky->addWidget(unsolved);
    popisky->addWidget(missed);
    popisky->addWidget(late);
    popisky->addWidget(school);

    setLayout(mainLayout);


}


absenceWindow::~absenceWindow(){}
