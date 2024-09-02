#include "registerscreen.hpp"
#include "schedule.hpp"
#include "signinscreen.hpp"
#include <QApplication>
#include <QTranslator>

SignInScreen* myWindow;
registerscreen* myWindow2;
Schedule* myWindow3;

int main(int argc, char *argv[])
{
    QTranslator translator;
    translator.load(":/strings");

    QApplication myApp(argc, argv);
    myApp.installTranslator(&translator);

    myWindow = new SignInScreen();
    myWindow2 = new registerscreen();
    //myWindow3 = new Schedule();

    myWindow->show();
    // myWindow3->show();

    return myApp.exec();
}
