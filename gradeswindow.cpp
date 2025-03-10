#include "gradeswindow.hpp"
#include "coordinator.hpp"

extern Coordinator *coordinator;

gradesWindow::gradesWindow(QWidget *parent): ScreenWidget(parent) {
    coordinator->implementMenuBar(mainLayout);
    setLayout(mainLayout);

}

gradesWindow::~gradesWindow(){}

void gradesWindow::configure(QSharedPointer<ShowBasicData>, QSharedPointer<ShowBasicData2>) {

}
