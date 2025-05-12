#include "menubar.hpp"
#include "coordinator.hpp"
#include "menuwindow.hpp"

extern Coordinator* coordinator;


menuBar::menuBar() {

}

void menuBar::menuBarStup(QBoxLayout *layout){

    layout->addWidget(quickAcces);

    //TODO: Actions dont hide the current window that the action was clicked from, i will solve it
    //QMenuBar Actions
    QObject::connect(scheduleAction, &QAction::triggered, this, [&](){
        coordinator->showSchedule();
         hide();

    });
    QObject::connect(gradesAction, &QAction::triggered, this, [&](){
        coordinator->showGradesWindow();
        hide();

    });
    QObject::connect(absenceAction, &QAction::triggered, this, [&](){
        coordinator->showAbsenceWindow();
        hide();

    });
    QObject::connect(settingsAction, &QAction::triggered, this, [&](){
        coordinator->showSettingsWindow();
        hide();

    });
    QObject::connect(czLanguageAction, &QAction::triggered, this, [&](){


    });
    QObject::connect(engLanguageAction, &QAction::triggered, this, [&](){

    });
    QObject::connect(logOutAction, &QAction::triggered, this, [&](){
        api->userAPI.logout();
    });

    quickAcces->addMenu(functions);
    quickAcces->addMenu(options);

    functions->addAction(scheduleAction);
    functions->addAction(absenceAction);
    functions->addAction(gradesAction);
    functions->addAction(menuAction);
    functions->addAction(logOutAction);

    languages->addAction(czLanguageAction);
    languages->addAction(engLanguageAction);

    options->addMenu(languages);
    options->addAction(settingsAction);
}

menuBar::~menuBar() {}
