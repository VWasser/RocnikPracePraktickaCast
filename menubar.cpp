#include "menubar.hpp"
#include "menuwindow.hpp"

menuBar::menuBar() {

}

void menuBar::menuBarStup(QBoxLayout *layout){

    layout->addWidget(quickAcces);


    //QMenuBar Actions
    QObject::connect(scheduleAction, &QAction::triggered, this, [&](){
         // TODO: Some window here is displaying here
        //myWindow3->show();
        hide();

    });
    QObject::connect(gradesAction, &QAction::triggered, this, [&](){
         // TODO: Some window here is displaying here
        //gradeWin->show();
        hide();

    });
    QObject::connect(absenceAction, &QAction::triggered, this, [&](){
         // TODO: Some window here is displaying here
        //abscWin->show();
        hide();

    });
    QObject::connect(settingsAction, &QAction::triggered, this, [&](){
         // TODO: Some window here is displaying here
        //popUpWindow->show();
        hide();

    });
    QObject::connect(czLanguageAction, &QAction::triggered, this, [&](){


    });
    QObject::connect(engLanguageAction, &QAction::triggered, this, [&](){

    });
    QObject::connect(logOutAction, &QAction::triggered, this, [&](){
        // TODO: show this window
        //myWindow->show();
        hide();

    });

    quickAcces->addMenu(functions);
    quickAcces->addMenu(options);

    functions->addAction(scheduleAction);
    functions->addAction(absenceAction);
    functions->addAction(gradesAction);
    functions->addAction(menuAction);


    languages->addAction(czLanguageAction);
    languages->addAction(engLanguageAction);

    options->addMenu(languages);
    options->addAction(settingsAction);
}

menuBar::~menuBar() {}
