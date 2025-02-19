#include "settingsWindow.hpp"
#include "schedule.hpp"
#include "coordinator.hpp"

extern Coordinator *coordinator;

settingsWindow::settingsWindow(QWidget* parent): QWidget(parent) {
    coordinator->implementMenuBar(mainLayout);
    setLayout(mainLayout);
}

settingsWindow::~settingsWindow() {}
