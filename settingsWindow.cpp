#include "settingsWindow.hpp"
#include "schedule.hpp"
#include "coordinator.hpp"

extern Coordinator *coordinator;

settingsWindow::settingsWindow(QWidget* parent): ScreenWidget(parent) {
    coordinator->implementMenuBar(mainLayout);
    setLayout(mainLayout);
}

settingsWindow::~settingsWindow() {}

void settingsWindow::configure(QSharedPointer<ShowBasicData>, QSharedPointer<ShowBasicData2>) {

}
