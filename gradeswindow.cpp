#include "gradeswindow.hpp"
#include "coordinator.hpp"

extern Coordinator *coordinator;

gradesWindow::gradesWindow(QWidget *parent):QWidget(parent) {
    coordinator->implementMenuBar(mainLayout);
    setLayout(mainLayout);

}


gradesWindow::~gradesWindow(){}
