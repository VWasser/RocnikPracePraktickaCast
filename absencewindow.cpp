#include "absencewindow.hpp"

absenceWindow::absenceWindow(QWidget *parent): QWidget(parent) {
    QObject::connect(addAbsence, &QPushButton::clicked, this, [&](){
        myWindow3->show();
        if(myWindow3->isVisible() == true){
            emit scheduleAbsenceOpened();
            hide();
        }
    });
    absenceLayout->setFixedSize(315, 600);

    absenceLayout->setRowCount(ammountOfDays);
    absenceLayout->setColumnCount(6);
    for(int i =0;i < 6;i++){
        absenceLayout->setColumnWidth(i,50);
    }
    addAbsence->setText(absenceWindow::tr("addAbsence"));

    absenceLayout->setHorizontalHeaderItem(0, date);
    absenceLayout->setHorizontalHeaderItem(1,ok);
    absenceLayout->setHorizontalHeaderItem(2,unsolved);
    absenceLayout->setHorizontalHeaderItem(3,missed);
    absenceLayout->setHorizontalHeaderItem(4,late);
    absenceLayout->setHorizontalHeaderItem(5,school);


    mainLayout->addWidget(addAbsence);
    mainLayout->addWidget(absenceLayout);
    setLayout(mainLayout);
}


absenceWindow::~absenceWindow(){}
