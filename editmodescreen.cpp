#include "editmodescreen.hpp"
#include "BackendlessQt/BackendlessAPI.hpp"
#include "schedule.hpp"

extern Schedule* myWindow3;

editModeScreen::editModeScreen(QWidget* parent): QWidget(parent) {
    QObject::connect(api, &BackendlessAPI::itemAdded, this, [&](){
        // Item is added
        close();
    });



    nameOfClass->setPlaceholderText(editModeScreen::tr("className"));
    classRow->setPlaceholderText(editModeScreen::tr("hour"));
    classCollumn->setPlaceholderText(editModeScreen::tr("day"));
    addButt->setText(editModeScreen::tr("add"));

    mainLayout->addWidget(nameOfClass);
    mainLayout->addLayout(rowsAndCollums);
    mainLayout->addWidget(addButt);
    rowsAndCollums->addWidget(classRow);
    rowsAndCollums->addWidget(classCollumn);
    setLayout(mainLayout);
    QObject::connect(addButt, &QPushButton::clicked, this, [&](){
        auto name = new StringPostParam(nameOfClass->text());
        bool isOK;
        auto row =  new IntPostParam(classRow->text().toInt(&isOK));
        auto collumn = new IntPostParam(classCollumn->text().toInt(&isOK));

        if(nameOfClass->text() == ""){
            close();
        }else{
            api->addItemToTable(
                "Schedules",
                {
                    {"lessonDescription", name},
                    {"dayOfWeek", row},
                    {"hourStart",collumn}
                }
            );
        }

        delete name;
        delete row;
        delete collumn;
    });


}

editModeScreen::~editModeScreen() {}
