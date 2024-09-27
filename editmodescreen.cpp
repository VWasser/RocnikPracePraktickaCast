#include "editmodescreen.hpp"
#include "BackendlessQt/BackendlessAPI.hpp"
#include "schedule.hpp"

editModeScreen::editModeScreen(QWidget* parent): QWidget(parent) {
    QObject::connect(api, &BackendlessAPI::itemAdded, this, [&](){
        // Item is added
    });

    nameOfClass->setPlaceholderText("Jméno hodiny");
    classRow->setPlaceholderText("Hodina");
    classCollumn->setPlaceholderText("Den");

    mainLayout->addWidget(nameOfClass);
    mainLayout->addLayout(rowsAndCollums);
    mainLayout->addWidget(addButt);
    rowsAndCollums->addWidget(classRow);
    rowsAndCollums->addWidget(classCollumn);
    setLayout(mainLayout);
    QObject::connect(addButt, &QPushButton::clicked, this, [&](){
        QString name = nameOfClass->text();
        QString row = classRow->text();
        QString collumn = classCollumn->text();


        api->addItemToTable(
            "Schedules",
            {
                {"lessonDescription", name},
                {"dayOfWeek", row},
                {"hourStart",collumn}
            }
            );
        close();
    });


}

editModeScreen::~editModeScreen() {}
