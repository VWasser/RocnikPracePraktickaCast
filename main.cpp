#include "registerscreen.hpp"
#include "signinscreen.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication myApp(argc, argv);

    SignInScreen myWindow;
    myWindow.show();

    registerscreen myWindow2;
    myWindow2.hide();

    return myApp.exec();
}
