#include "editmodescreen.hpp"

editModeScreen::editModeScreen(QWidget* parent): QWidget(parent) {

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
        nameOfClass->text();
        classRow->text();
        classCollumn->text();
        close();
    });
}

editModeScreen::~editModeScreen() {}
