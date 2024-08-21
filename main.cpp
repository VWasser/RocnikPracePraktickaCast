#include "registerscreen.hpp"
#include "signinscreen.hpp"
#include <QApplication>

SignInScreen* myWindow;
registerscreen* myWindow2;



int main(int argc, char *argv[])
{
    QApplication myApp(argc, argv);
    myWindow = new SignInScreen();
    myWindow2 = new registerscreen();

    myWindow->show();


    return myApp.exec();
}
