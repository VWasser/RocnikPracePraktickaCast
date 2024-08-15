#include "signinscreen.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication myApp(argc, argv);

    SignInScreen myWindow;
    myWindow.show();

    return myApp.exec();
}
