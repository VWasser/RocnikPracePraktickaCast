#include "gradeswindow.hpp"
#include "coordinator.hpp"

GradesWindow::gradesWindow(QWidget*parent): ScreenWidget(parent) {
    setLayout(mainLayout);
    mainLayout->addWidget(addButton);

    QObject::connect(addButton, &QPushButton::clicked,this, [](){
        QPushButton
    });
    //for add function, I need to make a
    //dynamic creating of a new button for new grades
    //if already made, i will just add more to the array or smthing
}
GradesWindow::~gradesWindow() {}

