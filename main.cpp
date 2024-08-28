#include "registerscreen.hpp"
#include "schedule.hpp"
#include "signinscreen.hpp"
#include <QApplication>


SignInScreen* myWindow;
registerscreen* myWindow2;
schedule* myWindow3;



int main(int argc, char *argv[])
{
    QApplication myApp(argc, argv);
    myWindow = new SignInScreen();
    myWindow2 = new registerscreen();
    myWindow3 = new schedule();

    myWindow->show();
    myWindow3->show();

    return myApp.exec();
}
